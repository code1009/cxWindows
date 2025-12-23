/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "pch.hpp"

#include "../res/resource.h"

#include "MainWindow.hpp"
#include "AboutDialog.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
LRESULT MainWindow::onMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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

LRESULT MainWindow::onDestroy(HWND hWnd)
{
    UNREFERENCED_PARAMETER(hWnd);

    PostQuitMessage(0);

    return 0;
}

LRESULT MainWindow::onPaint(HWND hWnd)
{
    PAINTSTRUCT ps;

    HDC hdc = BeginPaint(hWnd, &ps);

    EndPaint(hWnd, &ps);

    return 0;
}

LRESULT MainWindow::onCommand(HWND hWnd, int id, HWND hWndCtl, UINT codeNotify)
{
    UNREFERENCED_PARAMETER(hWndCtl);
    UNREFERENCED_PARAMETER(codeNotify);

    switch (id)
    {
    case IDM_ABOUT:
        AppAbout();
        break;

    case IDM_EXIT:
        DestroyWindow(hWnd);
        break;

    default:
        return ::DefWindowProcW(hWnd, WM_COMMAND, id, reinterpret_cast<LPARAM>(hWndCtl));
    }

    return 0;
}

LRESULT MainWindow::onDpiChanged(HWND hWnd, WPARAM wParam, LPARAM lParam)
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

//===========================================================================
void MainWindow::AppAbout(void)
{
    AboutDialog aboutDialog;
    INT_PTR rv = showModalDialog(&aboutDialog, _hInstance, IDD_ABOUTBOX, _hWnd);
    if (IDCANCEL == rv)
    {
        MessageBoxW(_hWnd, L"Dialog canceled.", L"확인", MB_OK);
    }
}





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
bool initMainWindowClass(HINSTANCE hInstance)
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

