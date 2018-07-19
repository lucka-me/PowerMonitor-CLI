/*
Created by lucka-me in 07/19/2018
*/

#include "stdafx.h"
#include "IntelPowerGadgetControl.h"


IntelPowerGadgetControl::IntelPowerGadgetControl() {
}


IntelPowerGadgetControl::~IntelPowerGadgetControl() {
    if (libModule != NULL)
        FreeLibrary(libModule);
}

bool IntelPowerGadgetControl::Initialize(void) {

    // Get the library location
    // Check if IPG is available
    TCHAR libDirStr[MAX_PATH];
    TCHAR libVerStr[MAX_PATH];
    GetEnvironmentVariable(L"IPG_Dir", libDirStr, MAX_PATH);
    GetEnvironmentVariable(L"IPG_Ver", libVerStr, MAX_PATH);
    if (libDirStr == NULL || wcslen(libDirStr) == 0 || libVerStr == NULL || wcslen(libVerStr) == 0) {
        lastError = "Intel Power Gadget not found. Please install the application or check the user's path environment variable.";
        return false;
    }
    // Check if the version is 2.7+
    int libVer = int(_wtof(libVerStr) * 100);
    if (libVer < 270) {
        lastError = "Intel Power Gadget 2.7 or higher is required. Please update the application.";
        return false;
    }
#if _M_X64
    CString libLocation = CString(libDirStr) + "\\EnergyLib64.dll";
#else
    CString libLocation = CString(libVerStr) + "\\EnergyLib32.dll";
#endif

    // Load the library
    libModule = LoadLibrary(libLocation);
    if (libModule == NULL) {
        lastError = "Load library failed from " + libLocation;
        return false;
    }

    // Setup the method pointers
    pInitialize        = (IPGInitialize)        GetProcAddress(libModule, "IntelEnergyLibInitialize");
    pReadSample        = (IPGReadSample)        GetProcAddress(libModule, "ReadSample");
    pGetNumNodes       = (IPGGetNumNodes)       GetProcAddress(libModule, "GetNumNodes");
    pGetNumMsrs        = (IPGGetNumMsrs)        GetProcAddress(libModule, "GetNumMsrs");
    pGetMsrName        = (IPGGetMsrName)        GetProcAddress(libModule, "GetMsrName");
    pGetMsrFunc        = (IPGGetMsrFunc)        GetProcAddress(libModule, "GetMsrFunc");
    pGetPowerData      = (IPGGetPowerData)      GetProcAddress(libModule, "GetPowerData");
    pIsGTAvailable     = (IPGIsGTAvailable)     GetProcAddress(libModule, "IsGTAvailable");
    pGetGTFrequency    = (IPGGetGTFrequency)    GetProcAddress(libModule, "GetGTFrequency");
    pGetSysTime        = (IPGGetSysTime)        GetProcAddress(libModule, "GetSysTime");
    pGetTimeInterval   = (IPGGetTimeInterval)   GetProcAddress(libModule, "GetTimeInterval");
    pGetIAFrequency    = (IPGGetIAFrequency)    GetProcAddress(libModule, "GetIAFrequency");
    pGetTDP            = (IPGGetTDP)            GetProcAddress(libModule, "GetTDP");
    pGetMaxTemperature = (IPGGetMaxTemperature) GetProcAddress(libModule, "GetMaxTemperature");
    pGetTemperature    = (IPGGetTemperature)    GetProcAddress(libModule, "GetTemperature");
    pGetBaseFrequency  = (IPGGetBaseFrequency)  GetProcAddress(libModule, "GetBaseFrequency");
    pStartLog          = (IPGStartLog)          GetProcAddress(libModule, "StartLog");
    pStopLog           = (IPGStopLog)           GetProcAddress(libModule, "StopLog");

    // Initialize the library
    if (!pInitialize()) {
        lastError = "Intal Power Gadget library initializing failed.";
        return false;
    }

    return true;
}

CString IntelPowerGadgetControl::GetLastError(void) {
    return lastError;
}
