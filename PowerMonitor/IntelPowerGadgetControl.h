/*
Created by lucka-me in 07/19/2018
*/

#pragma once
// Using CString in non-MFC
//   Ref: https://msdn.microsoft.com/en-us/library/ms174288.aspx
#include <atlstr.h>

using namespace std;

class IntelPowerGadgetControl {

    // Methods
public:
    IntelPowerGadgetControl();
    ~IntelPowerGadgetControl();

    bool Initialize(void);
    CString GetLastError(void);

    // Method pointers for IPG API
private:
    typedef bool(*IPGInitialize)        ();
    typedef bool(*IPGReadSample)        ();
    typedef bool(*IPGGetNumNodes)       (int *nNodes);
    typedef bool(*IPGGetNumMsrs)        (int *nMsr);
    typedef bool(*IPGGetMsrName)        (int iMsr, wchar_t *szName);
    typedef bool(*IPGGetMsrFunc)        (int iMsr, int *funcID);
    typedef bool(*IPGGetPowerData)      (int iNode, int iMSR, double *result, int *nResult);
    typedef bool(*IPGIsGTAvailable)     ();
    typedef bool(*IPGGetGTFrequency)    (int *freq);
    typedef bool(*IPGGetSysTime)        (SYSTEMTIME *pSysTime);
    typedef bool(*IPGGetTimeInterval)   (double *offset);
    typedef bool(*IPGGetIAFrequency)    (int iNode, int *freqInMHz);
    typedef bool(*IPGGetTDP)            (int iNode, double *TDP);
    typedef bool(*IPGGetMaxTemperature) (int iNode, int *degreeC);
    typedef bool(*IPGGetTemperature)    (int iNode, int *degreeC);
    typedef bool(*IPGGetBaseFrequency)  (int iNode, double *baseFrequency);
    typedef bool(*IPGStartLog)          (wchar_t *szFileName);
    typedef bool(*IPGStopLog)           ();

    IPGInitialize        pInitialize;
    IPGReadSample        pReadSample;
    IPGGetNumNodes       pGetNumNodes;
    IPGGetNumMsrs        pGetNumMsrs;
    IPGGetMsrName        pGetMsrName;
    IPGGetMsrFunc        pGetMsrFunc;
    IPGGetPowerData      pGetPowerData;
    IPGIsGTAvailable     pIsGTAvailable;
    IPGGetGTFrequency    pGetGTFrequency;
    IPGGetSysTime        pGetSysTime;
    IPGGetTimeInterval   pGetTimeInterval;
    IPGGetIAFrequency    pGetIAFrequency;
    IPGGetTDP            pGetTDP;
    IPGGetMaxTemperature pGetMaxTemperature;
    IPGGetTemperature    pGetTemperature;
    IPGGetBaseFrequency  pGetBaseFrequency;
    IPGStartLog          pStartLog;
    IPGStopLog           pStopLog;

    // Attributes
private:
    HMODULE libModule = NULL;
    CString lastError = "";
};

