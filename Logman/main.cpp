//
//  main.cpp
//  Logman
//
//  Created by Mitchell Donahue on 8/1/18.
//  Copyright © 2018 Mitchell Donahue. All rights reserved.
//

#include "Logman.hpp"
#include "Structs.hpp"
#include "Utils.hpp"
#include <iostream>
#include <strings.h>
using namespace std;

int main(int argc, const char * argv[]) {
    Logman master;
    LogMsg* moveMsg;
    set<LogMsg*>::iterator lowerBound, upperBound, tmpBound;
    char cmd;
    string args;
    master.processInput("Untitled.txt");
    cout << "% ";
    while (cin >> cmd) {
        switch (cmd) {
            case 't':
                cin >> args;
                master.setItrs(lowerBound, upperBound);
                cout << distance(lowerBound, upperBound) << endl;
                break;
            case 'c':
                cout << cmd << endl;
                break;
            case 'k':
                cout << cmd << endl;
                break;
            case 'i':
                cin >> args;
                master.excerptList.push_back(&master.masterFiles[stoi(args)]);
                break;
            case 'r':
                // TODO: must be sorted according to time sort
                tmpBound = lowerBound;
                while (tmpBound != upperBound) {
                    master.excerptList.push_back(*tmpBound);
                    tmpBound++;
                }
                cout << cmd << endl;
                break;
            case 'd':
                cin >> args;
                master.excerptList.erase(master.excerptList.begin() + stoi(args));
                break;
            case 'b':
                cin >> args;
                moveMsg = master.excerptList[stoi(args)];
                master.excerptList.erase(master.excerptList.begin() + stoi(args));
                master.excerptList.insert(master.excerptList.begin(), moveMsg);
                break;
            case 'e':
                cin >> args;
                master.excerptList.push_back(master.excerptList[stoi(args)]);
                master.excerptList.erase(master.excerptList.begin() + stoi(args));
                break;
            case 's':
                // maybe sort when a command comes in that needs list to be sorted
                sort(master.excerptList.begin(), master.excerptList.end(), LogMsgTimeComp());
                break;
            case 'l':
                master.excerptList.resize(0);
                break;
            case 'g':
                printRecentTime(lowerBound, upperBound);
                break;
            case 'p':
                for (int i = 0; i < master.excerptList.size(); i++) {
                    cout << master.excerptList[i]->getTimestamp() << endl;
                }
                break;
            case 'q':
                return 0;
            default:
                break;
        }
        cout << "% ";
    }
    return 0;
};
