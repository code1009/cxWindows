#pragma once





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





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);





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





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
INT_PTR CALLBACK DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
ATOM registerWindowClass(
    HINSTANCE hInstance,
    LPCWSTR className,
    WORD idMenu,
    WORD idIcon,
    WORD idIconSmall,
    UINT style = CS_HREDRAW | CS_VREDRAW
);

int messageLoop(HACCEL hAccelTable);





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
INT_PTR showModalDialog(Dialog* dialog, HINSTANCE hInstance, WORD idDialogTemplate, HWND hParentWindow = nullptr);




