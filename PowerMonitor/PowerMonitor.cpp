/*
Created by lucka-me in 07/19/2018
*/

// PowerMonitor.cpp: 定义控制台应用程序的入口点。
//


#include "stdafx.h"
#include "IntelPowerGadgetControl.h"
#include <iostream>
using namespace std;

int main() {
    IntelPowerGadgetControl ipgCtrl;
    if (!ipgCtrl.Initialize()) {
        cout << "Error: " + ipgCtrl.GetLastError() << endl;
    } else {
        cout << "Intel Power Gadget API initializing succeed." << endl;
    }
    Sleep(5000);
    return 0;
}

