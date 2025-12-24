/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "pch.hpp"





/////////////////////////////////////////////////////////////////////////////
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
ATOM registerWindowClass(HINSTANCE hInstance, LPCWSTR className, WORD idMenu, WORD idIcon, WORD idIconSmall, UINT style)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = style;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = (idIcon==0) ? nullptr : LoadIconW(hInstance, MAKEINTRESOURCEW(idIcon));
    wcex.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = (idMenu==0) ? nullptr : MAKEINTRESOURCEW(idMenu);
    wcex.lpszClassName = className;
    wcex.hIconSm = (idIconSmall==0) ? nullptr : LoadIconW(wcex.hInstance, MAKEINTRESOURCEW(idIconSmall));

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
INT_PTR showModalDialog(Dialog* dialog, HINSTANCE hInstance, WORD idDialogTemplate, HWND hParentWindow)
{
    dialog->_hInstance = hInstance;
    INT_PTR rv = DialogBoxParamW(hInstance, MAKEINTRESOURCE(idDialogTemplate), hParentWindow, DialogProc, reinterpret_cast<LPARAM>(dialog));
	return rv;
}

std::wstring getResourceString(WORD id, HINSTANCE hInstance)
{
    //-----------------------------------------------------------------------
    LPWSTR ptr;
    LPWSTR* pptr;
    int rv;


    ptr = nullptr;
    pptr = &ptr;
    rv = ::LoadStringW(hInstance,
        id,
        (LPWSTR)pptr,
        0
    );


    std::wstring s;


    if (rv)
    {
        if (ptr)
        {
            s = ptr;
        }
    }

    return s;
}



