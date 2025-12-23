/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "framework.hpp"
#include "main.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class Window
{
public:
    HINSTANCE _hInstance = nullptr;
    HWND _hWnd = nullptr;

public:
    Window() = default;
    virtual ~Window() = default;

public:
    virtual LRESULT onMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;
};

//===========================================================================
LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    //-----------------------------------------------------------------------
    if (WM_NCCREATE == message)
    {
        auto userData = reinterpret_cast<CREATESTRUCTW*>(lParam)->lpCreateParams;
        if (userData)
        {
            (reinterpret_cast<Window*>(userData))->_hWnd = hwnd;
            ::SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(userData));
        }
    }


    //-----------------------------------------------------------------------
    auto window = reinterpret_cast<Window*>(::GetWindowLongPtrW(hwnd, GWLP_USERDATA));
    if (window)
    {
        auto lResult = window->onMessage(hwnd, message, wParam, lParam);
        if (WM_NCDESTROY == message)
        {
            ::SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(nullptr));
        }

        return lResult;
    }

    return ::DefWindowProcW(hwnd, message, wParam, lParam);
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class Dialog
{
public:
    HINSTANCE _hInstance = nullptr;
    HWND _hDlg = nullptr;

public:
    Dialog() = default;
    virtual ~Dialog() = default;

public:
    virtual INT_PTR onMessage(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) = 0;
};

//===========================================================================
INT_PTR CALLBACK DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    //-----------------------------------------------------------------------
    if (WM_INITDIALOG == message)
    {
        auto userData = reinterpret_cast<Dialog*>(lParam);
        if (userData)
        {
            (reinterpret_cast<Dialog*>(userData))->_hDlg = hDlg;
            ::SetWindowLongPtrW(hDlg, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(userData));
        }
    }


    //-----------------------------------------------------------------------
    auto dialog = reinterpret_cast<Dialog*>(::GetWindowLongPtrW(hDlg, GWLP_USERDATA));
    if (dialog)
    {
        auto lResult = dialog->onMessage(hDlg, message, wParam, lParam);
        if (WM_NCDESTROY == message)
        {
            ::SetWindowLongPtrW(hDlg, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(nullptr));
        }

        return static_cast<INT_PTR>(lResult);
    }

    return FALSE;
}






/////////////////////////////////////////////////////////////////////////////
//===========================================================================
ATOM registerWindowClass(HINSTANCE hInstance, LPCWSTR className, WORD idMenu, WORD idIcon, WORD idIconSmall, UINT style = CS_HREDRAW | CS_VREDRAW)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = style;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIconW(hInstance, MAKEINTRESOURCEW(idIcon));
    wcex.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(idMenu);
    wcex.lpszClassName = className;
    wcex.hIconSm = LoadIconW(wcex.hInstance, MAKEINTRESOURCEW(idIconSmall));

    return RegisterClassExW(&wcex);
}

int messageLoop(HACCEL hAccelTable)
{
    MSG msg;

    while (GetMessageW(&msg, nullptr, 0, 0))
    {
        if (!TranslateAcceleratorW(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }

    return (int)msg.wParam;
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class AboutDialog : public Dialog
{
public:
    AboutDialog() = default;
	virtual ~AboutDialog() = default;

public:
    INT_PTR onMessage(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
        case WM_INITDIALOG: return onInitDialog(hDlg, (HWND)wParam, lParam);
        case WM_COMMAND: return onCommand(hDlg, LOWORD(wParam), (HWND)lParam, HIWORD(wParam));
        }

        return (INT_PTR)FALSE;
    }

public:
    INT_PTR onInitDialog(HWND hDlg, HWND hWndFocus, LPARAM lParam)
    {
        UNREFERENCED_PARAMETER(hWndFocus);
        UNREFERENCED_PARAMETER(lParam);

        return (INT_PTR)TRUE;
    }

    INT_PTR onCommand(HWND hDlg, int id, HWND hWndCtl, UINT codeNotify)
    {
        UNREFERENCED_PARAMETER(hWndCtl);
        UNREFERENCED_PARAMETER(codeNotify);

        switch (id)
        {
        case IDOK:
        case IDCANCEL:
            EndDialog(hDlg, id);

            return (INT_PTR)TRUE;
        }

        return (INT_PTR)FALSE;
    }
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class MainWindow : public Window
{
public:
    MainWindow() = default;
    virtual ~MainWindow() = default;

public:
    LRESULT onMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
        case WM_DESTROY: return onDestroy(hWnd);
        case WM_PAINT: return onPaint(hWnd);
        case WM_COMMAND: return onCommand(hWnd, LOWORD(wParam), (HWND)lParam, HIWORD(wParam));
        case WM_DPICHANGED: return onDpiChanged(hWnd, wParam, lParam);
        }

        return ::DefWindowProcW(hWnd, message, wParam, lParam);
    }

public:
    LRESULT onDestroy(HWND hWnd)
    {
        UNREFERENCED_PARAMETER(hWnd);

        PostQuitMessage(0);

        return 0;
    }

    LRESULT onPaint(HWND hWnd)
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        EndPaint(hWnd, &ps);

        return 0;
    }

    LRESULT onCommand(HWND hWnd, int id, HWND hWndCtl, UINT codeNotify)
    {
        UNREFERENCED_PARAMETER(hWndCtl);
        UNREFERENCED_PARAMETER(codeNotify);

        switch (id)
        {
        case IDM_ABOUT:
            {
                AboutDialog aboutDialog;
                aboutDialog._hInstance = _hInstance;
                INT_PTR rv = DialogBoxParamW(_hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, DialogProc, reinterpret_cast<LPARAM>(&aboutDialog));
                if (IDCANCEL == rv)
                {
                    MessageBoxW(hWnd, L"Dialog canceled.", L"확인", MB_OK);
                }
            }
            break;

        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;

        default:
            return ::DefWindowProcW(hWnd, WM_COMMAND, id, reinterpret_cast<LPARAM>(hWndCtl));
        }

        return 0;
    }

    LRESULT onDpiChanged(HWND hWnd, WPARAM wParam, LPARAM lParam)
    {
        UINT dpiX = LOWORD(wParam);
        UINT dpiY = HIWORD(wParam);

        // 내부 DPI 갱신 (X 기준 사용)
        //_dpi = dpiX;

        // lParam은 RECT* (권장 새 위치/크기)
        if (lParam)
        {
            RECT* suggestedRect = reinterpret_cast<RECT*>(lParam);
            int width = suggestedRect->right - suggestedRect->left;
            int height = suggestedRect->bottom - suggestedRect->top;

            SetWindowPos(
                hWnd, 
                nullptr, 
                suggestedRect->left, suggestedRect->top, 
                width, height, 
                SWP_NOZORDER | SWP_NOACTIVATE
            );
        }

        // TODO: 폰트/아이콘/레이아웃 등 DPI에 따른 리소스 재적용이 필요하면 여기서 수행
        return 0;
    }
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
bool initMainWindow(MainWindow& window, HINSTANCE hInstance, int nCmdShow)
{
    //-----------------------------------------------------------------------
    const size_t MaxWindowClassName = 100;
    WCHAR szWindowClass[MaxWindowClassName];

    LoadStringW(hInstance, IDC_MAIN, szWindowClass, MaxWindowClassName);


    //-----------------------------------------------------------------------
    const size_t MaxWindowName = 100;
    WCHAR szWindowName[MaxWindowName];

    LoadStringW(hInstance, IDS_APP_TITLE, szWindowName, MaxWindowName);


    //-----------------------------------------------------------------------
    window._hInstance = hInstance;


    //-----------------------------------------------------------------------
    HWND hWnd = CreateWindowExW(
		0,
        szWindowClass,
        szWindowName,
        WS_OVERLAPPEDWINDOW,
        0, 0, CW_USEDEFAULT, CW_USEDEFAULT, 
        nullptr, nullptr, 
        hInstance, 
        &window
    );
    if (!hWnd)
    {
        return false;
    }


    //-----------------------------------------------------------------------
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return true;
}






/////////////////////////////////////////////////////////////////////////////
//===========================================================================
bool initWindowClass(HINSTANCE hInstance)
{
    //-----------------------------------------------------------------------
    const size_t MaxWindowClassName = 100;
    WCHAR szWindowClass[MaxWindowClassName];

    LoadStringW(hInstance, IDC_MAIN, szWindowClass, MaxWindowClassName);


    //-----------------------------------------------------------------------
    ATOM atom;
    atom = registerWindowClass(hInstance, szWindowClass, IDC_MAIN, IDI_APP, IDI_APP_SMALL);
	if (0 == atom)
    {
        return false;
    }

    return true;
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
int windowsEntryPoint(HINSTANCE hInstance, int nCmdShow)
{
    //-----------------------------------------------------------------------
    bool rv;


    //-----------------------------------------------------------------------
    rv = initWindowClass(hInstance);
    if (!rv)
    {
        return -1;
    }


    //-----------------------------------------------------------------------
    MainWindow mainWindow;
    rv = initMainWindow(mainWindow, hInstance, nCmdShow);
    if (!rv)
    {
        return -1;
    }


    //-----------------------------------------------------------------------
    HACCEL hAccelTable = LoadAcceleratorsW(hInstance, MAKEINTRESOURCEW(IDC_MAIN));

    return messageLoop(hAccelTable);
}




/////////////////////////////////////////////////////////////////////////////
//===========================================================================
int APIENTRY wWinMain
(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nCmdShow
)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    return windowsEntryPoint(hInstance, nCmdShow);
}




