
#include "subFrame.h"


/* Default Constructor to Overwrite wxFXYVector Class */
customFXYVector::customFXYVector(wxString name)
{
    wxPen vectorpen(*wxBLUE, 2, wxPENSTYLE_SOLID);
    SetContinuity(true);
    SetPen(vectorpen);
    SetDrawOutsideMargins(false);
}

/* Function Which Allows Continuous Update of Data Plots */
void mpFXYVector::AddData(float xVal, float yVal, std::vector<double>& xVector, std::vector<double>& yVector)
{
    /* Data Vectors Must Be the Same Size in Order to Plot */
    if (xVector.size() != yVector.size()) {
        wxLogError(_("wxMathPlot Error - X and Y Vectors Are Diffrent Lengths"));
        return;
    }

    /* Push New Data Values to End of Vector */
    xVector.push_back(xVal);
    yVector.push_back(yVal);

    /* If Vector Gets too Large Only Plot past 25s */
    if (xVector.size() > 50)
    {
        xVector.erase(xVector.begin());
        yVector.erase(yVector.begin());
    }

    /* Write New Vectors to Class Data Structure */
    m_xs = xVector;
    m_ys = yVector;

    /* Update The Bounding Box Values */
    if (xVector.size() > 0)
    {
        m_minX = xVector[0];
        m_maxX = xVector[0];
        m_minY = yVector[0];
        m_maxY = yVector[0];

        std::vector<double>::const_iterator  it;

        for (it = xVector.begin(); it != xVector.end(); it++)
        {
            if (*it < m_minX) m_minX = *it;
            if (*it > m_maxX) m_maxX = *it;
        }
        for (it = yVector.begin(); it != yVector.end(); it++)
        {
            if (*it < m_minY) m_minY = *it;
            if (*it > m_maxY) m_maxY = *it;
        }
        m_minX -= 0.5f;
        m_minY -= 0.5f;
        m_maxX += 0.5f;
        m_maxY += 0.5f;
    }
    else
    {
        m_minX = -1;
        m_maxX = 1;
        m_minY = -1;
        m_maxY = 1;
    }
}


/* Default Constructor to Overwrite mpWindow Class */
dataPlot::dataPlot(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long flags, wxString units, wxString title) : mpWindow(parent, id, wxDefaultPosition, wxDefaultSize, flags)
{
    mpScaleX* xaxis = new mpScaleX(wxT(""), 0x02, false, 0x01);
    mpScaleY* yaxis = new mpScaleY(units, 0x02, true);
    wxFont graphFont(9, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    xaxis->SetFont(graphFont);
    yaxis->SetFont(graphFont);
    xaxis->SetDrawOutsideMargins(false);
    yaxis->SetDrawOutsideMargins(false);

    SetMargins(20, 40, 40, 80);
    AddLayer(xaxis);
    AddLayer(yaxis);
    AddLayer(new mpText(title, 30, 5));
}


/* Default Constructor for Electrical Data Frame Class */
electricalDataFrame::electricalDataFrame(const wxString& title, const wxPoint& pos, const wxSize size) : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    /* Data Vector Initialization */
    layer0 = new customFXYVector(wxT("SOC"));
    layer1 = new customFXYVector(wxT("FPV"));
    layer2 = new customFXYVector(wxT("highTemp"));
    layer3 = new customFXYVector(wxT("lowTemp"));
    layer4 = new customFXYVector(wxT("highVoltage"));
    layer5 = new customFXYVector(wxT("lowVoltage"));
    layer6 = new customFXYVector(wxT("RPM"));
    layer7 = new customFXYVector(wxT("motorTemp"));
    layer8 = new customFXYVector(wxT("dcBusCurrent"));
    layer9 = new customFXYVector(wxT("auxVoltage"));

    /* Data Plot Initializeation */
    plot0 = new dataPlot(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER, wxT("Volts"), wxT("SOC"));
    plot1 = new dataPlot(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER, wxT("Volts"), wxT("FPV"));
    plot2 = new dataPlot(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER, wxT("Celsius"), wxT("highTemp"));
    plot3 = new dataPlot(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER, wxT("Celsius"), wxT("lowTemp"));
    plot4 = new dataPlot(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER, wxT("Volts"), wxT("highVoltage"));
    plot5 = new dataPlot(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER, wxT("Volts"), wxT("lowVoltage"));
    plot6 = new dataPlot(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER, wxT("RPM"), wxT("RPM"));
    plot7 = new dataPlot(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER, wxT("Celsius"), wxT("motorTemp"));
    plot8 = new dataPlot(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER, wxT("Amps"), wxT("dcBusCurrent"));
    plot9 = new dataPlot(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER, wxT("Volts"), wxT("auxVoltage"));

    /* Add Vectors to Respective Plots */
    plot0->AddLayer(layer0);
    plot1->AddLayer(layer1);
    plot2->AddLayer(layer2);
    plot3->AddLayer(layer3);
    plot4->AddLayer(layer4);
    plot5->AddLayer(layer5);
    plot6->AddLayer(layer6);
    plot7->AddLayer(layer7);
    plot8->AddLayer(layer8);
    plot9->AddLayer(layer9);

    /* Sizer to Hold Plots */
    wxBoxSizer* mainsizer = new wxBoxSizer(wxHORIZONTAL);
    leftSizer = new wxBoxSizer(wxVERTICAL);
    rightSizer = new wxBoxSizer(wxVERTICAL);

    /* Format Plot Space 5x2 */
    leftSizer->Add(plot0, 1, wxEXPAND);
    leftSizer->Add(plot1, 1, wxEXPAND);
    leftSizer->Add(plot2, 1, wxEXPAND);
    leftSizer->Add(plot3, 1, wxEXPAND);
    leftSizer->Add(plot4, 1, wxEXPAND);

    rightSizer->Add(plot5, 1, wxEXPAND);
    rightSizer->Add(plot6, 1, wxEXPAND);
    rightSizer->Add(plot7, 1, wxEXPAND);
    rightSizer->Add(plot8, 1, wxEXPAND);
    rightSizer->Add(plot9, 1, wxEXPAND);

    mainsizer->Add(leftSizer, 1, wxEXPAND);
    mainsizer->Add(rightSizer, 1, wxEXPAND);

    /* Display Plot Sizers */
    SetAutoLayout(TRUE);
    SetSizer(mainsizer);
}


/* Default Constructor for Physical Data Frame Class */
physicalDataFrame::physicalDataFrame(const wxString& title, const wxPoint& pos, const wxSize size) : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    /* Data Vector Initialization */
    layer0 = new customFXYVector(wxT("motorTorque"));
    layer1 = new customFXYVector(wxT("motorCtrlTemp"));
    layer2 = new customFXYVector(wxT("xAcc"));
    layer3 = new customFXYVector(wxT("yAcc"));
    layer4 = new customFXYVector(wxT("zAcc"));
    layer5 = new customFXYVector(wxT("xGyro"));
    layer6 = new customFXYVector(wxT("yGyro"));
    layer7 = new customFXYVector(wxT("zGyro"));
    layer8 = new customFXYVector(wxT("roll"));
    layer9 = new customFXYVector(wxT("pitch"));

    /* Data Plot Initializeation */
    plot0 = new dataPlot(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER, wxT("[units]"), wxT("motorTorque"));
    plot1 = new dataPlot(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER, wxT("Celsius"), wxT("motorCtrlTemp"));
    plot2 = new dataPlot(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER, wxT("[units]"), wxT("xAcc"));
    plot3 = new dataPlot(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER, wxT("[units]"), wxT("yAcc"));
    plot4 = new dataPlot(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER, wxT("[units]"), wxT("zAcc"));
    plot5 = new dataPlot(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER, wxT("[units]"), wxT("xGyro"));
    plot6 = new dataPlot(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER, wxT("[units]"), wxT("yGyro"));
    plot7 = new dataPlot(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER, wxT("[units]"), wxT("zGyro"));
    plot8 = new dataPlot(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER, wxT("[units]"), wxT("roll"));
    plot9 = new dataPlot(this, -1, wxPoint(0, 0), wxSize(100, 100), wxSUNKEN_BORDER, wxT("[units]"), wxT("pitch"));

    /* Add Vectors to Respective Plots */
    plot0->AddLayer(layer0);
    plot1->AddLayer(layer1);
    plot2->AddLayer(layer2);
    plot3->AddLayer(layer3);
    plot4->AddLayer(layer4);
    plot5->AddLayer(layer5);
    plot6->AddLayer(layer6);
    plot7->AddLayer(layer7);
    plot8->AddLayer(layer8);
    plot9->AddLayer(layer9);

    /* Sizer to Hold Plots */
    wxBoxSizer* mainsizer = new wxBoxSizer(wxHORIZONTAL);
    leftSizer = new wxBoxSizer(wxVERTICAL);
    rightSizer = new wxBoxSizer(wxVERTICAL);

    /* Format Plot Space 5x2 */
    leftSizer->Add(plot0, 1, wxEXPAND);
    leftSizer->Add(plot1, 1, wxEXPAND);
    leftSizer->Add(plot2, 1, wxEXPAND);
    leftSizer->Add(plot3, 1, wxEXPAND);
    leftSizer->Add(plot4, 1, wxEXPAND);

    rightSizer->Add(plot5, 1, wxEXPAND);
    rightSizer->Add(plot6, 1, wxEXPAND);
    rightSizer->Add(plot7, 1, wxEXPAND);
    rightSizer->Add(plot8, 1, wxEXPAND);
    rightSizer->Add(plot9, 1, wxEXPAND);

    mainsizer->Add(leftSizer, 1, wxEXPAND);
    mainsizer->Add(rightSizer, 1, wxEXPAND);

    /* Display Plot Sizers */
    SetAutoLayout(TRUE);
    SetSizer(mainsizer);
}