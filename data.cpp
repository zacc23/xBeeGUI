
#include "data.h"


/* Default Constructor */
data::data()
{
    /* Open Port */
    serialHandle = CreateFile(_T("\\\\.\\COM4"), GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    /* Set Port Settings */
    DCB serialParams = { 0 };
    serialParams.DCBlength = sizeof(serialParams);

    GetCommState(serialHandle, &serialParams);
    serialParams.BaudRate = 57600;
    serialParams.ByteSize = 8;
    serialParams.StopBits = ONESTOPBIT;
    serialParams.Parity = NOPARITY;
    SetCommState(serialHandle, &serialParams);

    /* Set Port Timeouts */
    COMMTIMEOUTS timeout = { 0 };
    timeout.ReadIntervalTimeout = 50;
    timeout.ReadTotalTimeoutConstant = 50;
    timeout.ReadTotalTimeoutMultiplier = 50;
    timeout.WriteTotalTimeoutConstant = 50;
    timeout.WriteTotalTimeoutMultiplier = 10;
    SetCommTimeouts(serialHandle, &timeout);



    ///* Create Console */                                                                                      // DebugA
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
}

void data::readData()
{
    /* Initialize Local Data Structures */
    BOOL bResult;
    BYTE bReadBuf[2048];

    /* Create Single Event */
    OVERLAPPED oRead = { 0 };
    oRead.hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

    /* Read File Call */
    bResult = ReadFile(serialHandle, bReadBuf, _countof(bReadBuf), NULL, &oRead);

    /* Error Handling */
    if (!bResult && GetLastError() != ERROR_IO_PENDING)
    {
        _tprintf_s(TEXT("Error Code - 01"));
        CloseHandle(serialHandle);
    }

    /* Setup Wait Call */
    HANDLE hEvents = oRead.hEvent;
    DWORD dwWaitRes = WaitForSingleObject(hEvents, INFINITE);

    /* Execute Once Read is Finished */
    switch (dwWaitRes - WAIT_OBJECT_0)
    {
    case 0:
        
        rawDataSize = oRead.InternalHigh;
        for (int i = 0; i < oRead.InternalHigh; ++i)
           rawData[i] = bReadBuf[i];
           //_tprintf_s(TEXT("%c"), bReadBuf[i]);
        break;

    default:
        _tprintf_s(TEXT("Error Code - 02"));
    }
}

/* Refresh Bolt Data */
void data::refreshBoltData()
{
    std::cout << '\n';

    /* Local Variables Needed to Parse Data */
    char START_CHAR = 0x7E;
    //char END_CHAR = 0x70;
    bool parseData = false;
    std::string hold = "";

    /* Enum To ID Data Element */
    enum ID { SOC, FPV, highTemp, lowTemp, highVoltage, lowVoltage, RPM, motorTemp, dcBusCurrent, motorTorque, motorCtrlTemp, auxVoltage, xAcc, yAcc, zAcc, xGyro, yGyro, zGyro, roll, pitch, END };
    ID dataID = SOC;

    /* Iterate Through Entire Raw Data Buffer */
    for (int k = 0; k < rawDataSize; k++)
    {
        ///* Identify End Bit and Terminate Data Parsing */
        //if (rawData[k] == END_CHAR)
        //    parseData = false;


        /* Parse Input Data into Respective Data Fields */
        if (parseData)
        {

            switch (dataID)
            {
            case SOC:
                if (rawData[k] == ',')
                {   
                    electricalData.SOC = stod(hold);
                    dataID = FPV;
                    std::cout << "\nSOC:" << hold << "  ";
                    hold.clear();
                }
                else
                {
                    hold += rawData[k];
                }
                break;
            case FPV:
                if (rawData[k] == ',')
                {
                    electricalData.FPV = stod(hold);
                    dataID = highTemp;
                    std::cout << "\nFPV:" << hold << "  ";
                    hold.clear();
                }
                else
                {
                    hold += rawData[k];
                }
                break;
            case highTemp:
                if (rawData[k] == ',')
                {
                    electricalData.highTemp = stod(hold);
                    dataID = lowTemp;
                    std::cout << "\nhighTemp:" << hold << "  ";
                    hold.clear();
                }
                else
                {
                    hold += rawData[k];
                }
                break;
            case lowTemp:
                if (rawData[k] == ',')
                {
                    electricalData.lowTemp = stod(hold);
                    dataID = highVoltage;
                    std::cout << "\nlowTemp:" << hold << "  ";
                    hold.clear();
                }
                else
                {
                    hold += rawData[k];
                }
                break;
            case highVoltage:
                if (rawData[k] == ',')
                {
                    electricalData.highVoltage = stod(hold);
                    dataID = lowVoltage;
                    std::cout << "\nhighVoltage:" << hold << "  ";
                    hold.clear();
                }
                else
                {
                    hold += rawData[k];
                }
                break;
            case lowVoltage:
                if (rawData[k] == ',')
                {
                    electricalData.lowVoltage = stod(hold);
                    dataID = RPM;
                    std::cout << "\nlowVoltage:" << hold << "  ";
                    hold.clear();
                }
                else
                {
                    hold += rawData[k];
                }
                break;
            case RPM:
                if (rawData[k] == ',')
                {
                    electricalData.RPM = stod(hold);
                    dataID = motorTemp;
                    std::cout << "\nRPM:" << hold << "  ";
                    hold.clear();
                }
                else
                {
                    hold += rawData[k];
                }
                break;
            case motorTemp:
                if (rawData[k] == ',')
                {
                    electricalData.motorTemp = stod(hold);
                    dataID = dcBusCurrent;
                    std::cout << "\nmotorTemp:" << hold << "  ";
                    hold.clear();
                }
                else
                {
                    hold += rawData[k];
                }
                break;
            case dcBusCurrent:
                if (rawData[k] == ',')
                {
                    electricalData.dcBusCurrent = stod(hold);
                    dataID = motorTorque;
                    std::cout << "\ndcBusCurrent:" << hold << "  ";
                    hold.clear();
                }
                else
                {
                    hold += rawData[k];
                }
                break;
            case motorTorque:
                if (rawData[k] == ',')
                {
                    physicalData.motorTorque = stod(hold);
                    dataID = motorCtrlTemp;
                    std::cout << "\nmotorTorque:" << hold << "  ";
                    hold.clear();
                }
                else
                {
                    hold += rawData[k];
                }
                break;
            case motorCtrlTemp:
                if (rawData[k] == ',')
                {
                    physicalData.motorCtrlTemp = stod(hold);
                    dataID = auxVoltage;
                    std::cout << "\nmotroCtrlTemp:" << hold << "  ";
                    hold.clear();
                }
                else
                {
                    hold += rawData[k];
                }
                break;
            case auxVoltage:
                if (rawData[k] == ',')
                {
                    electricalData.auxVoltage = stod(hold);
                    dataID = xAcc;
                    std::cout << "\nauxVoltage:" << hold << "  ";
                    hold.clear();
                }
                else
                {
                    hold += rawData[k];
                }
                break;
            case xAcc:
                if (rawData[k] == ',')
                {
                    physicalData.xAcc = stod(hold);
                    dataID = yAcc;
                    std::cout << "\nxAcc:" << hold << "  ";
                    hold.clear();
                }
                else
                {
                    hold += rawData[k];
                }
                break;
            case yAcc:
                if (rawData[k] == ',')
                {
                    physicalData.yAcc = stod(hold);
                    dataID = zAcc;
                    std::cout << "\nyAcc:" << hold << "  ";
                    hold.clear();
                }
                else
                {
                    hold += rawData[k];
                }
                break;
            case zAcc:
                if (rawData[k] == ',')
                {
                    physicalData.zAcc = stod(hold);
                    dataID = xGyro;
                    std::cout << "\nzAcc:" << hold << "  ";
                    hold.clear();
                }
                else
                {
                    hold += rawData[k];
                }
                break;
            case xGyro:
                if (rawData[k] == ',')
                {
                    physicalData.xGyro = stod(hold);
                    dataID = yGyro;
                    std::cout << "\nxGyro:" << hold << "  ";
                    hold.clear();
                }
                else
                {
                    hold += rawData[k];
                }
                break;
            case yGyro:
                if (rawData[k] == ',')
                {
                    physicalData.yGyro = stod(hold);
                    dataID = zGyro;
                    std::cout << "\nyGyro:" << hold << "  ";
                    hold.clear();
                }
                else
                {
                    hold += rawData[k];
                }
                break;
            case zGyro:
                if (rawData[k] == ',')
                {
                    physicalData.zGyro = stod(hold);
                    dataID = roll;
                    std::cout << "\nzGyro:" << hold << "  ";
                    hold.clear();
                }
                else
                {
                    hold += rawData[k];
                }
                break;
            case roll:
                if (rawData[k] == ',')
                {
                    physicalData.roll = stod(hold);
                    dataID = pitch;
                    std::cout << "\nroll:" << hold << "  ";
                    hold.clear();
                }
                else
                {
                    hold += rawData[k];
                }
                break;
            case pitch:
                if (!isdigit(rawData[k]))
                {
                    physicalData.pitch = stod(hold);
                    dataID = END;
                    std::cout << "\npitch:" << hold << "  ";
                    std::cout << "END OF THIS DATA TRANSMISSION\n\n";
                    hold.clear();
                }
                else
                {
                    hold += rawData[k];
                }
                break;
            case END:
                break;
            }
        }

        /* Identify Start Bit and Begin Data Parsing */
        if (rawData[k] == START_CHAR)
        {
            parseData = true;
            k += 16;
        }
    }
}


/* Default Destructor */
void data::deletePort()
{
    CloseHandle(serialHandle);
}