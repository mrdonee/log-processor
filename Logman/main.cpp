//
//  main.cpp
//  Logman
//
//  Created by Mitchell Donahue on 8/1/18.
//  Copyright © 2018 Mitchell Donahue. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include "Structs.hpp"
#include "Logman.hpp"
#include <strings.h>
using namespace std;

struct LogMsgTimeComp {
    bool operator()(const LogMsg* lhs, const LogMsg* rhs) const  {
        if (lhs->getTimestamp() < rhs->getTimestamp()) {
            return true;
        } else if (lhs->getTimestamp() > rhs->getTimestamp()) {
            return false;
        }
        int categoryCompRes = strcasecmp(&lhs->getCategory()[0], &rhs->getCategory()[0]);
        if (categoryCompRes < 0) {
            return true;
        } else if (categoryCompRes > 0) {
            return false;
        }
        return lhs->getEntryId() < rhs->getEntryId();
    }
};

void getTimeInt(string &s) {
    s.erase(remove(s.begin(), s.end(), ':'), s.end());
}

string getTimeStr(int i) {
    string timeStr = to_string(i);
    timeStr = string(10 - timeStr.length(), '0').append(timeStr);
    timeStr.insert(2, ":");
    timeStr.insert(5, ":");
    timeStr.insert(8, ":");
    timeStr.insert(11, ":");
    return timeStr;
}

void processInput(Logman &master) {
    string line;
    ifstream myfile ("Untitled.txt");
    int entryIdCtr = 0;
    if (myfile.is_open()) {
        while (getline(myfile,line)) {
            string t = line.substr(0, line.find('|'));
            getTimeInt(t);
            int time = stoi(t);
            line = line.substr(line.find('|') + 1, line.length());
            string c = line.substr(0, line.find('|'));
            string m = line.substr(line.find('|') + 1, line.length());
            master.masterFiles.push_back(LogMsg(time, c, m, entryIdCtr++));
        }
        myfile.close();
    } else {
        cout << "Unable to open file" << endl;
        exit(1);
    }
    for (int i = 0; i < master.masterFiles.size(); i++) {
        master.masterSortedByTime.insert(&master.masterFiles[i]);
    }
    cout << entryIdCtr << " entries loaded\n";
}

void printRecentTime(set<LogMsg*>::iterator start, set<LogMsg*>::iterator end) {
    while (start != end) {
        string timeStr = getTimeStr((*start)->getTimestamp());
        cout << timeStr << "|" << (*start)->getCategory() << "|" << (*start)->getMsg() << endl;
        start++;
    }
}

int main(int argc, const char * argv[]) {
    Logman master;
    LogMsg tmpMsg;
    LogMsg* moveMsg;
    set<LogMsg*>::iterator lowerBound, upperBound, tmpBound;
    char cmd;
    string args;
    processInput(master);
    cout << "% ";
    while (cin >> cmd) {
        switch (cmd) {
            case 't':
                cin >> args;
                tmpMsg = LogMsg(425215536, "", "", 0);
                lowerBound = master.masterSortedByTime.lower_bound(&tmpMsg);
                tmpMsg = LogMsg(702101300 - 1, "", "", 0);
                upperBound = master.masterSortedByTime.upper_bound(&tmpMsg);
                cout << distance(lowerBound, upperBound) << endl;
                break;
            case 'c':
                cout << cmd << endl;
                break;
            case 'k':
                cout << cmd << endl;
                break;
            case 'i':
                //numbers greateer than 10
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
                //make this applicable to all iterators
                printRecentTime(lowerBound, upperBound);
                break;
            case 'p':
                for(int i = 0; i < master.excerptList.size(); i++) {
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
