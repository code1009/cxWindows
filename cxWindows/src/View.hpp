/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class View : public Window
{
public:
    View() = default;
    virtual ~View() = default;

public:
    virtual LRESULT onMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

public:
    LRESULT onCreate(LPCREATESTRUCT lpCreateStruct);
    LRESULT onDestroy();
    LRESULT onClose();
    LRESULT onPaint(HDC hBkDC);
    LRESULT onCommand(int id, HWND hWndCtl, UINT codeNotify);
    LRESULT onDpiChanged(UINT dpiX, UINT dpiY, RECT* suggestedRect);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
bool initView(View& window, HINSTANCE hInstance, HWND hParentWnd);
bool initViewClass(HINSTANCE hInstance);
