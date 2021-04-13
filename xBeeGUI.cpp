
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "xBeeGUI.h"

/* Overwrite main() Function Call */
wxIMPLEMENT_APP(xBeeGUI);

/* Initialize the GUI */
bool xBeeGUI::OnInit()
{
    mainFrame* p_mainFrame = new mainFrame();
    p_mainFrame->Show(true);
	return true;
}






