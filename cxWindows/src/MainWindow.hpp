/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class MainWindow : public Window
{
public:
    MainWindow() = default;
    virtual ~MainWindow() = default;

public:
    LRESULT onMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
    LRESULT onDestroy(HWND hWnd);
    LRESULT onPaint(HWND hWnd);
    LRESULT onCommand(HWND hWnd, int id, HWND hWndCtl, UINT codeNotify);
    LRESULT onDpiChanged(HWND hWnd, WPARAM wParam, LPARAM lParam);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
bool initMainWindow(MainWindow& window, HINSTANCE hInstance, int nCmdShow);
bool initMainWindowClass(HINSTANCE hInstance);
