/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "pch.hpp"

#include "../res/resource.h"

#include "View.hpp"
#include "MainFrame.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
int windowEntryPoint(HINSTANCE hInstance, int nCmdShow)
{
    //-----------------------------------------------------------------------
    bool rv;


    //-----------------------------------------------------------------------
    rv = initMainFrameClass(hInstance);
    if (!rv)
    {
        return -1;
    }


    //-----------------------------------------------------------------------
    MainFrame MainFrame;
    rv = initMainFrame(MainFrame, hInstance, nCmdShow);
    if (!rv)
    {
        return -1;
    }


    //-----------------------------------------------------------------------
    HACCEL hAccelTable = LoadAcceleratorsW(hInstance, MAKEINTRESOURCEW(IDR_MAINFRAME));

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

    int rv;

    OutputDebugStringW(L"wWinMain(): begin\n");
    rv = windowEntryPoint(hInstance, nCmdShow);
    OutputDebugStringW(L"wWinMain(): end\n");

	return rv;
}




