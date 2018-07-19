/*
Created by lucka-me in 07/19/2018
*/

// PowerMonitor.cpp: 定义控制台应用程序的入口点。
//


#include "stdafx.h"
#include "IntelPowerGadgetControl.h"
#include <iostream>
#include <iomanip>
using namespace std;

#ifdef UNICODE
#define fcout wcout
#else
#define fcout cout
#endif // UNICODE


int main() {
    fcout << "================================================================================" << endl
        << "                                PowerMonitor-CLI                                " << endl
        << "                               0.1.1  by lucka-me                               " << endl
        << "--------------------------------------------------------------------------------" << endl
        << "                               System Information                               " << endl;
    IntelPowerGadgetControl ipgCtrl;
    if (!ipgCtrl.Initialize()) {
        fcout << "Error: " + ipgCtrl.GetLastError() << endl;
        return -1;
    }
    // Set the precision
    //   Ref: https://stackoverflow.com/questions/554063
    fcout.precision(2);
    int numNodes = 0;
    int numMSRs = 0;
    ipgCtrl.GetNumNodes(&numNodes);
    ipgCtrl.GetNumMsrs(&numMSRs);
    fcout << " The system equipped " << numNodes << " CPU(s), supports " << endl;
    for (int iNode = 0; iNode < numNodes; iNode++) {
        double nodeBaseFreq = -1.0;
        double nodeTDP = -1.0;
        int nodeMaxTemperature = -1;
        ipgCtrl.GetBaseFrequency(iNode, &nodeBaseFreq);
        ipgCtrl.GetTDP(iNode, &nodeTDP);
        ipgCtrl.GetMaxTemperature(iNode, &nodeMaxTemperature);
        fcout << "  - CPU " << iNode << ": @" << int(nodeBaseFreq) << " MHz | TDP: " << int(nodeTDP) << " W | Max Temp: " << nodeMaxTemperature << " C" << endl;
    }
    fcout << " The system supports " << numMSRs << " MSR(s)." << endl;
    int msrCPUIndex = 0;
    int msrProcessorIndex = 0;
    for (int iMSR = 0; iMSR < numMSRs; iMSR++) {
        wchar_t szName[MAX_PATH];
        ipgCtrl.GetMsrName(iMSR, szName);
        fcout << "  - MSR " << iMSR << ": " << szName << endl;
        if (wcsstr(szName, L"CPU")) {
            msrCPUIndex = iMSR;
        } else if (wcsstr(szName, L"Processor")) {
            msrProcessorIndex = iMSR;
        }
    }
    if (ipgCtrl.IsGTAvailable()) {
        fcout << " Intel Graphics is available" << endl;
    } else {
        fcout << " Intel Graphics is unavailable" << endl;
    }
    fcout << "--------------------------------------------------------------------------------" << endl
        << "                                  Monitor Data                                  " << endl;
    ipgCtrl.ReadSample();
    while (true) {

        Sleep(2000);

        if (ipgCtrl.ReadSample() == false)
            fcout << "Warning: MSR overflowed. You can safely discard this sample." << endl;

        fcout << " CPU    Frequency (Mhz)    Power (W)    Temperature (C)" << endl;
        for (int iNode = 0; iNode < numNodes; iNode++) {
            double nodeFreq = -1.0;
            double nodePower = -1.0;
            int nodeTemperature = -1;
            double result[3];
            int nResult;
            // CPU Freq
            ipgCtrl.GetPowerData(iNode, msrCPUIndex, result, &nResult);
            nodeFreq = result[0];
            // Processor Power
            ipgCtrl.GetPowerData(iNode, msrProcessorIndex, result, &nResult);
            nodePower = result[0];
            // Temprature
            ipgCtrl.GetTemperature(iNode, &nodeTemperature);
            fcout << " " << std::setw(3) << iNode 
                << setw(13) << int(nodeFreq) << "      "
                << setw(9) << nodePower << "    "
                << setw(15) << nodeTemperature << endl;
        }
        if (ipgCtrl.IsGTAvailable()) {
            int gtFreq;
            ipgCtrl.GetGTFrequency(&gtFreq);
            fcout << " Intel Graphics @" << gtFreq << "MHz" << endl;
        }
        fcout << "--------------------------------------------------------------------------------" << endl;
    }
    return 0;
}

