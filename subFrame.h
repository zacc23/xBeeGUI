
#ifndef _SUBFRAME_H_
#define _SUBFRAME_H_

/* Include wxWidgets Lib */
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

/* Additional Include(s) */
#include "mathplot.h"

/* Custom Vector Class */
class customFXYVector : public mpFXYVector  
{
public:
    customFXYVector(wxString name);
    void AddData(float xVal, float yVal, std::vector<double>& xVector, std::vector<double>& yVector);
};

/* Data Plot Class */
class dataPlot : public mpWindow
{
public:
    dataPlot(wxWindow* parent, wxWindowID id,
        const wxPoint& pos,
        const wxSize& size,
        long flags,
        wxString units,
        wxString title);
};


class electricalDataFrame : public wxFrame
{
public:
    /* Default Constructor */
    electricalDataFrame(const wxString& title, const wxPoint& pos, const wxSize size);

    /* Class Data Members */
    mpWindow* plot0, * plot1, * plot2, * plot3, * plot4, * plot5, * plot6, * plot7, * plot8, * plot9;
    mpFXYVector* layer0, * layer1, * layer2, * layer3, * layer4, * layer5, * layer6, * layer7, * layer8, * layer9;
    wxBoxSizer* leftSizer;
    wxBoxSizer* rightSizer;
};


class physicalDataFrame : public wxFrame
{
public:
    /* Default Constructor */
    physicalDataFrame(const wxString& title, const wxPoint& pos, const wxSize size);

    /* Class Data Members */
    mpWindow* plot0, * plot1, * plot2, * plot3, * plot4, * plot5, * plot6, * plot7, * plot8, * plot9;
    mpFXYVector* layer0, * layer1, * layer2, * layer3, * layer4, * layer5, * layer6, * layer7, * layer8, * layer9;
    wxBoxSizer* leftSizer;
    wxBoxSizer* rightSizer;
};


#endif