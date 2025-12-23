/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "pch.hpp"

#include "../res/resource.h"

#include "MainWindow.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
int windowEntryPoint(HINSTANCE hInstance, int nCmdShow)
{
    //-----------------------------------------------------------------------
    bool rv;


    //-----------------------------------------------------------------------
    rv = initMainWindowClass(hInstance);
    if (!rv)
    {
        return -1;
    }


    //-----------------------------------------------------------------------
    MainWindow mainWindow;
    rv = initMainWindow(mainWindow, hInstance, nCmdShow);
    if (!rv)
    {
        return -1;
    }


    //-----------------------------------------------------------------------
    HACCEL hAccelTable = LoadAcceleratorsW(hInstance, MAKEINTRESOURCEW(IDC_MAIN));

    return messageLoop(hAccelTable);
}




/////////////////////////////////////////////////////////////////////////////
//===========================================================================
int APIENTRY wWinMain
(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nCmdShow
)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    return windowEntryPoint(hInstance, nCmdShow);
}




