/*
Created by lucka-me in 07/19/2018
*/

// PowerMonitor.cpp: 定义控制台应用程序的入口点。
//


#include "stdafx.h"
#include "IntelPowerGadgetControl.h"
#include <iostream>
using namespace std;

#ifdef UNICODE
#define fcout wcout
#else
#define fcout cout
#endif // UNICODE


int main() {
    IntelPowerGadgetControl ipgCtrl;
    if (!ipgCtrl.Initialize()) {
        fcout << "Error: " + ipgCtrl.GetLastError() << endl;
        return -1;
    }
    fcout << "Intel Power Gadget API initializing succeed." << endl;
    fcout << "================================================================================" << endl
        << "                                PowerMonitor-CLI                                " << endl
        << "                                0.1  by lucka-me                                " << endl
        << "--------------------------------------------------------------------------------" << endl
        << "                               System Information                               " << endl;
    // Set the pricision
    //   Ref: https://stackoverflow.com/questions/554063
    fcout.precision(2);
    int numNodes = 0;
    ipgCtrl.GetNumNodes(&numNodes);
    fcout << " The system equipped " << numNodes << " CPU(s)" << endl;
    for (int i = 0; i < numNodes; i++) {
        double nodeBaseFreq = -1.0;
        double nodeTDP = -1.0;
        int nodeMaxTemperature = -1;
        ipgCtrl.GetBaseFrequency(i, &nodeBaseFreq);
        ipgCtrl.GetTDP(i, &nodeTDP);
        ipgCtrl.GetMaxTemperature(i, &nodeMaxTemperature);
        fcout << "  - CPU " << i << ": @" << int(nodeBaseFreq) << " MHz | TDP: " << int(nodeTDP) << " W | Max Temp: " << nodeMaxTemperature << " ℃" << endl;
    }
    if (ipgCtrl.IsGTAvailable()) {
        fcout << " Intel Graphics is available" << endl;
    } else {
        fcout << " Intel Graphics is unavailable" << endl;
    }
    Sleep(5000);
    return 0;
}

