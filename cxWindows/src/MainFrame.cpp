/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "pch.hpp"

#include "../res/resource.h"

#include "View.hpp"

#include "MainFrame.hpp"

#include "AboutDialog.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
static const wchar_t MainFrame_WindowClassName[] = L"MainFrame";





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
LRESULT MainFrame::onMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE: return onCreate((LPCREATESTRUCT)lParam);
    case WM_DESTROY: return onDestroy();
    case WM_CLOSE: return onClose();
    case WM_PAINT: return onPaint((HDC)wParam);
    case WM_COMMAND: return onCommand(LOWORD(wParam), (HWND)lParam, HIWORD(wParam));
    case WM_DPICHANGED: return onDpiChanged(LOWORD(wParam), HIWORD(wParam), (RECT*)lParam);
	case WM_SIZE: return onSize((UINT)wParam, LOWORD(lParam), HIWORD(lParam));
    }

    return ::DefWindowProcW(hWnd, message, wParam, lParam);
}

LRESULT MainFrame::onCreate(LPCREATESTRUCT lpCreateStruct)
{
    OutputDebugStringW(L"MainFrame::onCreate() - begin\n");


    initViewClass(_hInstance);
    initView(_View, _hInstance, _hWnd);


    OutputDebugStringW(L"MainFrame::onCreate() - end\n");

    return 0;
}

LRESULT MainFrame::onDestroy()
{
    OutputDebugStringW(L"MainFrame::onDestroy() - begin\n");


    PostQuitMessage(0);


    OutputDebugStringW(L"MainFrame::onDestroy() - end\n");

    return 0;
}

LRESULT MainFrame::onClose()
{
    OutputDebugStringW(L"MainFrame::onClose() - begin\n");

	DestroyWindow(_hWnd);

    OutputDebugStringW(L"MainFrame::onClose() - end\n");

    return 0;
}

LRESULT MainFrame::onPaint(HDC hBkDC)
{
    PAINTSTRUCT ps;

    HDC hdc = BeginPaint(_hWnd, &ps);

    FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

    EndPaint(_hWnd, &ps);

    return 0;
}

LRESULT MainFrame::onCommand(int id, HWND hWndCtl, UINT codeNotify)
{
    UNREFERENCED_PARAMETER(hWndCtl);
    UNREFERENCED_PARAMETER(codeNotify);

    switch (id)
    {
    case IDM_ABOUT:
        AppAbout();
        break;

    case IDM_EXIT:
        DestroyWindow(_hWnd);
        break;

    default:
        return ::DefWindowProcW(_hWnd, WM_COMMAND, id, reinterpret_cast<LPARAM>(hWndCtl));
    }

    return 0;
}

LRESULT MainFrame::onDpiChanged(UINT dpiX, UINT dpiY, RECT* suggestedRect)
{
    //-----------------------------------------------------------------------
    OutputDebugStringW(L"MainFrame::onDpiChanged()\n");


    //-----------------------------------------------------------------------
    if (suggestedRect)
    {
        int width = suggestedRect->right - suggestedRect->left;
        int height = suggestedRect->bottom - suggestedRect->top;

        SetWindowPos(
            _hWnd,
            nullptr,
            suggestedRect->left, suggestedRect->top,
            width, height,
            SWP_NOZORDER | SWP_NOACTIVATE
        );
    }

    // TODO: 폰트/아이콘/레이아웃 등 DPI에 따른 리소스 재적용이 필요하면 여기서 수행
    return 0;
}

LRESULT MainFrame::onSize(UINT type, UINT width, UINT height)
{
    RECT rcClient;
	
    GetClientRect(_hWnd, &rcClient);

    if (_View._hWnd)
    {
        SetWindowPos(
            _View._hWnd,
            nullptr,
            0, 0,
            rcClient.right - rcClient.left,
            rcClient.bottom - rcClient.top,
            SWP_NOZORDER | SWP_NOACTIVATE
        );
    }

	return 0;
}

//===========================================================================
void MainFrame::AppAbout(void)
{
    AboutDialog aboutDialog;
    INT_PTR rv = showModalDialog(&aboutDialog, _hInstance, IDD_ABOUTBOX, _hWnd);
    if (IDCANCEL == rv)
    {
        MessageBoxW(_hWnd, L"IDCANCEL", L"확인", MB_OK);
    }
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
bool initMainFrame(MainFrame& window, HINSTANCE hInstance, int nCmdShow)
{
    //-----------------------------------------------------------------------
    OutputDebugStringW(L"initMainFrame() - begin\n");


    //-----------------------------------------------------------------------
	std::wstring title = getResourceString(IDS_APP_TITLE, hInstance);


    //-----------------------------------------------------------------------
    window._hInstance = hInstance;


    //-----------------------------------------------------------------------
    HWND hWnd = CreateWindowExW(
		0,
        MainFrame_WindowClassName,
        title.c_str(),
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

    //-----------------------------------------------------------------------
    OutputDebugStringW(L"initMainFrame() - end\n");

    return true;
}






/////////////////////////////////////////////////////////////////////////////
//===========================================================================
bool initMainFrameClass(HINSTANCE hInstance)
{
    ATOM atom;
    atom = registerWindowClass(hInstance, MainFrame_WindowClassName, IDR_MAINFRAME, IDI_APP, IDI_APP_SMALL);
	if (0 == atom)
    {
        return false;
    }

    return true;
}

