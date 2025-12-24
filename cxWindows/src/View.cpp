/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "pch.hpp"

#include "../res/resource.h"

#include "View.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
static const wchar_t View_WindowClassName[] = L"View";





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
LRESULT View::onMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_NCCREATE: return onNcCreate((LPCREATESTRUCT)lParam);
    case WM_NCDESTROY: return onNcDestroy();
    case WM_CREATE: return onCreate((LPCREATESTRUCT)lParam);
    case WM_DESTROY: return onDestroy();
    case WM_CLOSE: return onClose();
    case WM_PAINT: return onPaint((HDC)wParam);
    case WM_COMMAND: return onCommand(LOWORD(wParam), (HWND)lParam, HIWORD(wParam));
    case WM_DPICHANGED: return onDpiChanged(LOWORD(wParam), HIWORD(wParam), (RECT*)lParam);
    }

    return ::DefWindowProcW(hWnd, message, wParam, lParam);
}

LRESULT View::onNcCreate(LPCREATESTRUCT lpCreateStruct)
{
    OutputDebugStringW(L"View::onNcCreate() - begin\n");

    if (lpCreateStruct->lpszName)
    {
        SetWindowTextW(_hWnd, lpCreateStruct->lpszName);
    }

    OutputDebugStringW(L"View::onNcCreate() - end\n");

    return 1;
}

LRESULT View::onNcDestroy()
{
    OutputDebugStringW(L"View::onNcDestroy() - begin\n");


    OutputDebugStringW(L"View::onNcDestroy() - end\n");

    return 0;
}

LRESULT View::onCreate(LPCREATESTRUCT lpCreateStruct)
{
    OutputDebugStringW(L"View::onCreate() - begin\n");

    OutputDebugStringW(L"View::onCreate() - end\n");

    return 0;
}

LRESULT View::onDestroy()
{
    OutputDebugStringW(L"View::onDestroy() - begin\n");

    OutputDebugStringW(L"View::onDestroy() - end\n");

    return 0;
}

LRESULT View::onClose()
{
    OutputDebugStringW(L"View::onClose() - begin\n");

    DestroyWindow(_hWnd);

    OutputDebugStringW(L"View::onClose() - end\n");

    return 0;
}

LRESULT View::onPaint(HDC hBkDC)
{
    PAINTSTRUCT ps;

    HDC hdc = BeginPaint(_hWnd, &ps);

	draw(hdc, &ps.rcPaint);

    EndPaint(_hWnd, &ps);

    return 0;
}

LRESULT View::onCommand(int id, HWND hWndCtl, UINT codeNotify)
{
    UNREFERENCED_PARAMETER(hWndCtl);
    UNREFERENCED_PARAMETER(codeNotify);

    /*
    switch (id)
    {
    default:
        return ::DefWindowProcW(_hWnd, WM_COMMAND, id, reinterpret_cast<LPARAM>(hWndCtl));
    }
    */

    return 0;
}

LRESULT View::onDpiChanged(UINT dpiX, UINT dpiY, RECT* suggestedRect)
{
    OutputDebugStringW(L"View::onDpiChanged()\n");

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

//===========================================================================
void View::draw(HDC hdc, RECT* clipRect)
{
    FillRect(hdc, clipRect, (HBRUSH)(COLOR_WINDOW + 1));


    RECT rcClient;
    GetClientRect(_hWnd, &rcClient);


    DrawTextW(
        hdc,
        L"Hello, cxWindows!",
        -1,
        &rcClient,
        DT_CENTER | DT_VCENTER | DT_SINGLELINE
    );
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
bool initView(View& window, HINSTANCE hInstance, HWND hParentWnd)
{
    //-----------------------------------------------------------------------
    OutputDebugStringW(L"initView() - begin\n");


    //-----------------------------------------------------------------------
    window._hInstance = hInstance;


    //-----------------------------------------------------------------------
    DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
    HWND hWnd = CreateWindowExW(
        0,
        View_WindowClassName,
        nullptr,
        dwStyle,
        0, 0, 0, 0,
        hParentWnd, nullptr,
        hInstance,
        &window
    );
    if (!hWnd)
    {
        return false;
    }


    //-----------------------------------------------------------------------
    OutputDebugStringW(L"initView() - end\n");

    return true;
}






/////////////////////////////////////////////////////////////////////////////
//===========================================================================
bool initViewClass(HINSTANCE hInstance)
{
    ATOM atom;
    atom = registerWindowClass(hInstance, View_WindowClassName);
    if (0 == atom)
    {
        return false;
    }

    return true;
}

