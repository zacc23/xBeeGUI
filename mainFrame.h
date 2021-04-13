
#ifndef _MAINFRAME_H_
#define _MAINFRAME_H_

/* Include wxWidgets Lib */
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

/* Additional Include(s) */
#include "subFrame.h"
#include "data.h"

/* Data Transmission Includes */
#include <windows.h>
#include <tchar.h>


class mainFrame : public wxFrame
{
public:

    /* Default Constructor */
    mainFrame();

    /* Set Up Timer for Data Update */
    void TimerCall(wxTimerEvent& event);

    /* Function to Refresh Plots */
    void refreshDataPlots();

    /* Class Data Members*/
    data BoltData;
    electricalDataFrame* p_electricalDataFrame;
    physicalDataFrame* p_physicalDataFrame;
    wxTimer* m_timer;

    /* Event Table */
    wxDECLARE_EVENT_TABLE();
};




#endif
