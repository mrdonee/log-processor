//
//  Logman.cpp
//  Logman
//
//  Created by Mitchell Donahue on 8/1/18.
//  Copyright © 2018 Mitchell Donahue. All rights reserved.
//

#include "Logman.hpp"
#include "Utils.hpp"
#include <fstream>
#include <iostream>

void Logman::processInput(const string &filename) {
    string line;
    ifstream myfile (filename);
    int entryIdCtr = 0;
    if (myfile.is_open()) {
        while (getline(myfile,line)) {
            string t = line.substr(0, line.find('|'));
            int time = getTimeInt(t);
            line = line.substr(line.find('|') + 1, line.length());
            string c = line.substr(0, line.find('|'));
            string m = line.substr(line.find('|') + 1, line.length());
            masterFiles.push_back(LogMsg(time, c, m, entryIdCtr++));
        }
        myfile.close();
    } else {
        cout << "Unable to open file" << endl;
        exit(1);
    }
    for (int i = 0; i < masterFiles.size(); i++) {
        masterSortedByTime.insert(&masterFiles[i]);
    }
    cout << entryIdCtr << " entries loaded\n";
}

void Logman::setItrs(set<LogMsg*>::iterator &lwr, set<LogMsg*>::iterator &upr, string &timeArg) {
    LogMsg tmpMsg;
    string t1Str = timeArg.substr(0, timeArg.find('|'));
    int t1 = getTimeInt(t1Str);
    timeArg = timeArg.substr(timeArg.find('|') + 1, timeArg.length());
    int t2 = getTimeInt(timeArg);
    tmpMsg = LogMsg(t1, "", "", 0);
    lwr = masterSortedByTime.lower_bound(&tmpMsg);
    tmpMsg = LogMsg(t2 - 1, "", "", 0);
    upr = masterSortedByTime.upper_bound(&tmpMsg);
}
