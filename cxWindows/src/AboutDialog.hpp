/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class AboutDialog : public Dialog
{
public:
    AboutDialog() = default;
	virtual ~AboutDialog() = default;

public:
    virtual INT_PTR onMessage(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) override;

public:
    INT_PTR onInitDialog(HWND hDlg, HWND hWndFocus, LPARAM lParam);
    INT_PTR onCommand(HWND hDlg, int id, HWND hWndCtl, UINT codeNotify);
};
