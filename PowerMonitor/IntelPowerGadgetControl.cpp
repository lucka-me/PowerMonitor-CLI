/*
Created by lucka-me in 07/19/2018
*/

#include "stdafx.h"
#include "IntelPowerGadgetControl.h"

#ifdef UNICODE
// Output TCHAR in Unicode
//   Ref: https://stackoverflow.com/questions/5165160/
#define fcout wcout
#else
#define fcout cout
#endif // UNICODE

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
        lastError = " Intel Power Gadget not found. Please install the application or check the user's path environment variable.";
        return false;
    }
#ifdef OUTPUT_PROCESS
    fcout << " Intel Power Gadget path: " << libDirStr << endl;
#endif // OUTPUT_PROCESS

    // Check if the version is 2.7+
    int libVer = int(_wtof(libVerStr) * 100);
    if (libVer < 270) {
        lastError = " Intel Power Gadget 2.7 or higher is required. Please update the application.";
        return false;
    }
#ifdef OUTPUT_PROCESS
    fcout << " Intel Power Gadget version: " << libVerStr << endl;
#endif // OUTPUT_PROCESS

#if _M_X64
    CString libLocation = CString(libDirStr) + "\\EnergyLib64.dll";
#else
    CString libLocation = CString(libVerStr) + "\\EnergyLib32.dll";
#endif

    // Load the library
    libModule = LoadLibrary(libLocation);
    if (libModule == NULL) {
        lastError = " Load library failed from " + libLocation;
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
        lastError = " Intal Power Gadget library initializing failed.";
        return false;
    }

    return true;
}

CString IntelPowerGadgetControl::GetLastError(void) {
    return lastError;
}

bool IntelPowerGadgetControl::ReadSample(void) {
    return pReadSample();
}

bool IntelPowerGadgetControl::GetNumNodes(int * nNodes) {
    return pGetNumNodes(nNodes);
}

bool IntelPowerGadgetControl::GetNumMsrs(int * nMsr) {
    return pGetNumMsrs(nMsr);
}

bool IntelPowerGadgetControl::GetMsrName(int iMsr, wchar_t * szName) {
    return pGetMsrName(iMsr, szName);
}

bool IntelPowerGadgetControl::GetMsrFunc(int iMsr, int * funcID) {
    return pGetMsrFunc(iMsr, funcID);
}

bool IntelPowerGadgetControl::GetPowerData(int iNode, int iMSR, double * result, int * nResult) {
    return pGetPowerData(iNode, iMSR, result, nResult);
}

bool IntelPowerGadgetControl::IsGTAvailable(void) {
    return pIsGTAvailable();
}

bool IntelPowerGadgetControl::GetGTFrequency(int * freq) {
    return pGetGTFrequency(freq);
}

bool IntelPowerGadgetControl::GetSysTime(SYSTEMTIME * pSysTime) {
    return pGetSysTime(pSysTime);
}

bool IntelPowerGadgetControl::GetTimeInterval(double * offset) {
    return pGetTimeInterval(offset);
}

bool IntelPowerGadgetControl::GetIAFrequency(int iNode, int * freqInMHz) {
    return pGetIAFrequency(iNode, freqInMHz);
}

bool IntelPowerGadgetControl::GetTDP(int iNode, double * TDP) {
    return pGetTDP(iNode, TDP);
}

bool IntelPowerGadgetControl::GetMaxTemperature(int iNode, int * degreeC) {
    return pGetMaxTemperature(iNode, degreeC);
}

bool IntelPowerGadgetControl::GetTemperature(int iNode, int * degreeC) {
    return pGetTemperature(iNode, degreeC);
}

bool IntelPowerGadgetControl::GetBaseFrequency(int iNode, double * baseFrequency) {
    return pGetBaseFrequency(iNode, baseFrequency);
}

bool IntelPowerGadgetControl::StartLog(wchar_t * szFileName) {
    return pStartLog(szFileName);
}

bool IntelPowerGadgetControl::StopLog(void) {
    return pStopLog();
}
