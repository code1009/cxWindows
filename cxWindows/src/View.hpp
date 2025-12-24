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
    LRESULT onNcCreate(LPCREATESTRUCT lpCreateStruct);
    LRESULT onNcDestroy();
    LRESULT onCreate(LPCREATESTRUCT lpCreateStruct);
    LRESULT onDestroy();
    LRESULT onClose();
    LRESULT onDpiChanged(UINT dpiX, UINT dpiY, RECT* suggestedRect);
    LRESULT onSize(UINT type, UINT width, UINT height);
	LRESULT onEraseBkgnd(HDC hdc);
    LRESULT onPaint(HDC hBkDC);
    LRESULT onCommand(int id, HWND hWndCtl, UINT codeNotify);

public:
	void draw(HDC hdc, RECT* clipRect);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
bool initView(View& window, HINSTANCE hInstance, HWND hParentWnd);
bool initViewClass(HINSTANCE hInstance);
