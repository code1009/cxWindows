/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "pch.hpp"

#include "../res/resource.h"

#include "AboutDialog.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
INT_PTR AboutDialog::onMessage(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG: return onInitDialog(hDlg, (HWND)wParam, lParam);
    case WM_COMMAND: return onCommand(hDlg, LOWORD(wParam), (HWND)lParam, HIWORD(wParam));
    }

    return (INT_PTR)FALSE;
}

INT_PTR AboutDialog::onInitDialog(HWND hDlg, HWND hWndFocus, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(hWndFocus);
    UNREFERENCED_PARAMETER(lParam);

    return (INT_PTR)TRUE;
}

INT_PTR AboutDialog::onCommand(HWND hDlg, int id, HWND hWndCtl, UINT codeNotify)
{
    UNREFERENCED_PARAMETER(hWndCtl);
    UNREFERENCED_PARAMETER(codeNotify);

    switch (id)
    {
    case IDOK:
    case IDCANCEL:
        EndDialog(hDlg, id);

        return (INT_PTR)TRUE;
    }

    return (INT_PTR)FALSE;
}
