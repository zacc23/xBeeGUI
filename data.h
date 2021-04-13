#ifndef _DATA_H_
#define _DATA_H_


/* Include wxWidgets Lib */
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#define ASIO_STANDALONE
#include "asio.hpp"

/* Struct to Organize and Track Electrical Bolt Data */
struct electricalDataStruct
{
    double SOC, FPV, highTemp, lowTemp, highVoltage, lowVoltage, RPM, motorTemp, dcBusCurrent, auxVoltage;
    std::vector<double> vx_SOC, vx_FPV, vx_highTemp, vx_lowTemp, vx_highVoltage, vx_lowVoltage, vx_RPM, vx_motorTemp, vx_dcBusCurrent, vx_auxVoltage;
    std::vector<double> vy_SOC, vy_FPV, vy_highTemp, vy_lowTemp, vy_highVoltage, vy_lowVoltage, vy_RPM, vy_motorTemp, vy_dcBusCurrent, vy_auxVoltage;
};

/* Struct to Organize and Track Physical Bolt Data */
struct physicalDataStruct
{
    double motorTorque, motorCtrlTemp, xAcc, yAcc, zAcc, xGyro, yGyro, zGyro, roll, pitch;
    std::vector<double> vx_motorTorque, vx_motorCtrlTemp, vx_xAcc, vx_yAcc, vx_zAcc, vx_xGyro, vx_yGyro, vx_zGyro, vx_roll, vx_pitch;
    std::vector<double> vy_motorTorque, vy_motorCtrlTemp, vy_xAcc, vy_yAcc, vy_zAcc, vy_xGyro, vy_yGyro, vy_zGyro, vy_roll, vy_pitch;
};


/* Main Data Class */
class data
{
public:

    /* Default Constructor */
	data();

    /* Function to Read Data from Serial Port */
    void readData();

    /* Refresh Bolt Data */
    void refreshBoltData();

    /* Default Destructor */
    void deletePort();

    /* Data Members */
    HANDLE serialHandle;
    char rawData[2048];
    int rawDataSize;

    /* Formated Data Members */
    electricalDataStruct electricalData;
    physicalDataStruct physicalData;
    double xValue;

};

#endif