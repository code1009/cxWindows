/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class MainFrame : public Window
{
public:
    View _View;

public:
    MainFrame() = default;
    virtual ~MainFrame() = default;

public:
    virtual LRESULT onMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

public:
    LRESULT onCreate(LPCREATESTRUCT lpCreateStruct);
    LRESULT onDestroy();
    LRESULT onClose();
    LRESULT onPaint(HDC hBkDC);
    LRESULT onCommand(int id, HWND hWndCtl, UINT codeNotify);
    LRESULT onDpiChanged(UINT dpiX, UINT dpiY, RECT* suggestedRect);
	LRESULT onSize(UINT type, UINT width, UINT height);

public:
    void AppAbout(void);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
bool initMainFrame(MainFrame& window, HINSTANCE hInstance, int nCmdShow);
bool initMainFrameClass(HINSTANCE hInstance);
