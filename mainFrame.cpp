
#include "mainFrame.h"


/* Define Event Table for Timer Function */
enum {ID_Timer = 0x64};
wxBEGIN_EVENT_TABLE(mainFrame, wxFrame)
EVT_TIMER(ID_Timer, mainFrame::TimerCall)
wxEND_EVENT_TABLE()


/* Default Constructor for Main Frame */
mainFrame::mainFrame()
{
    p_electricalDataFrame = new electricalDataFrame("Electrical Data", wxDefaultPosition, wxDefaultSize);
    p_physicalDataFrame = new physicalDataFrame("Physical Data", wxDefaultPosition, wxDefaultSize);

    p_electricalDataFrame->Show(true);
    p_physicalDataFrame->Show(true);

    m_timer = new wxTimer(this, ID_Timer);
    m_timer->Start(500);
}


/* Function Call for Timer */
void mainFrame::TimerCall(wxTimerEvent& event)
{
    //for (int p = 0; p < 100; p++)
    //    BoltData.readData();

    /* Read New Bolt Data */
    BoltData.readData();

    /* Refresh Bolt Data Buffers */
    BoltData.refreshBoltData();

    /* Refersh mathplot Plots with New Bolt Data */
    refreshDataPlots();

    //wxLogMessage(wxFormatString(BoltData.rawData));
    //wxLogMessage(wxFormatString("Fuck this is Bad"));

}


/* Function Call for Timer */
void mainFrame::refreshDataPlots()
{
    /* Update X Axis Value */
    BoltData.xValue += 0.5;
    
    /* Update Data Vectors */
    p_electricalDataFrame->layer0->AddData(BoltData.xValue, BoltData.electricalData.SOC, BoltData.electricalData.vx_SOC, BoltData.electricalData.vy_SOC);
    p_electricalDataFrame->layer1->AddData(BoltData.xValue, BoltData.electricalData.FPV,             BoltData.electricalData.vx_FPV,             BoltData.electricalData.vy_FPV);
    p_electricalDataFrame->layer2->AddData(BoltData.xValue, BoltData.electricalData.highTemp,        BoltData.electricalData.vx_highTemp,        BoltData.electricalData.vy_highTemp);
    p_electricalDataFrame->layer3->AddData(BoltData.xValue, BoltData.electricalData.lowTemp,         BoltData.electricalData.vx_lowTemp,         BoltData.electricalData.vy_lowTemp);
    p_electricalDataFrame->layer4->AddData(BoltData.xValue, BoltData.electricalData.highVoltage,     BoltData.electricalData.vx_highVoltage,     BoltData.electricalData.vy_highVoltage);
    p_electricalDataFrame->layer5->AddData(BoltData.xValue, BoltData.electricalData.lowVoltage,      BoltData.electricalData.vx_lowVoltage,      BoltData.electricalData.vy_lowVoltage);
    p_electricalDataFrame->layer6->AddData(BoltData.xValue, BoltData.electricalData.RPM,             BoltData.electricalData.vx_RPM,             BoltData.electricalData.vy_RPM);
    p_electricalDataFrame->layer7->AddData(BoltData.xValue, BoltData.electricalData.motorTemp,       BoltData.electricalData.vx_motorTemp,       BoltData.electricalData.vy_motorTemp);
    p_electricalDataFrame->layer8->AddData(BoltData.xValue, BoltData.electricalData.dcBusCurrent,    BoltData.electricalData.vx_dcBusCurrent,    BoltData.electricalData.vy_dcBusCurrent);
    p_electricalDataFrame->layer9->AddData(BoltData.xValue, BoltData.electricalData.auxVoltage,      BoltData.electricalData.vx_auxVoltage,      BoltData.electricalData.vy_auxVoltage);

    p_physicalDataFrame->layer0->AddData(BoltData.xValue, BoltData.physicalData.motorTorque,     BoltData.physicalData.vx_motorTorque,   BoltData.physicalData.vy_motorTorque);
    p_physicalDataFrame->layer1->AddData(BoltData.xValue, BoltData.physicalData.motorCtrlTemp,   BoltData.physicalData.vx_motorCtrlTemp, BoltData.physicalData.vy_motorCtrlTemp);
    p_physicalDataFrame->layer2->AddData(BoltData.xValue, BoltData.physicalData.xAcc,            BoltData.physicalData.vx_xAcc,          BoltData.physicalData.vy_xAcc);
    p_physicalDataFrame->layer3->AddData(BoltData.xValue, BoltData.physicalData.yAcc,            BoltData.physicalData.vx_yAcc,          BoltData.physicalData.vy_yAcc);
    p_physicalDataFrame->layer4->AddData(BoltData.xValue, BoltData.physicalData.zAcc,            BoltData.physicalData.vx_zAcc,          BoltData.physicalData.vy_zAcc);
    p_physicalDataFrame->layer5->AddData(BoltData.xValue, BoltData.physicalData.xGyro,           BoltData.physicalData.vx_xGyro,         BoltData.physicalData.vy_xGyro);
    p_physicalDataFrame->layer6->AddData(BoltData.xValue, BoltData.physicalData.yGyro,           BoltData.physicalData.vx_yGyro,         BoltData.physicalData.vy_yGyro);
    p_physicalDataFrame->layer7->AddData(BoltData.xValue, BoltData.physicalData.zGyro,           BoltData.physicalData.vx_zGyro,         BoltData.physicalData.vy_zGyro);
    p_physicalDataFrame->layer8->AddData(BoltData.xValue, BoltData.physicalData.roll,            BoltData.physicalData.vx_roll,          BoltData.physicalData.vy_roll);
    p_physicalDataFrame->layer9->AddData(BoltData.xValue, BoltData.physicalData.pitch,           BoltData.physicalData.vx_pitch,         BoltData.physicalData.vy_pitch);

    /* Update Plots */
    p_electricalDataFrame->plot0->Fit();
    p_electricalDataFrame->plot1->Fit();
    p_electricalDataFrame->plot2->Fit();
    p_electricalDataFrame->plot3->Fit();
    p_electricalDataFrame->plot4->Fit();
    p_electricalDataFrame->plot5->Fit();
    p_electricalDataFrame->plot6->Fit();
    p_electricalDataFrame->plot7->Fit();
    p_electricalDataFrame->plot8->Fit();
    p_electricalDataFrame->plot9->Fit();

    p_physicalDataFrame->plot0->Fit();
    p_physicalDataFrame->plot1->Fit();
    p_physicalDataFrame->plot2->Fit();
    p_physicalDataFrame->plot3->Fit();
    p_physicalDataFrame->plot4->Fit();
    p_physicalDataFrame->plot5->Fit();
    p_physicalDataFrame->plot6->Fit();
    p_physicalDataFrame->plot7->Fit();
    p_physicalDataFrame->plot8->Fit();
    p_physicalDataFrame->plot9->Fit();
}