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
            getTimeInt(t);
            int time = stoi(t);
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

void Logman::setItrs(set<LogMsg*>::iterator &lwr, set<LogMsg*>::iterator &upr) {
    LogMsg tmpMsg;
    tmpMsg = LogMsg(425215536, "", "", 0);
    lwr = masterSortedByTime.lower_bound(&tmpMsg);
    tmpMsg = LogMsg(702101300 - 1, "", "", 0);
    upr = masterSortedByTime.upper_bound(&tmpMsg);
}
