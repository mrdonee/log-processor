//
//  Utils.cpp
//  Logman
//
//  Created by Mitchell Donahue on 8/2/18.
//  Copyright © 2018 Mitchell Donahue. All rights reserved.
//

#include "Structs.hpp"
#include <iostream>
#include <set>
#include <stdio.h>
using namespace std;

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

//make this applicable to all iterators
void printRecentTime(set<LogMsg*>::iterator start, set<LogMsg*>::iterator end) {
    while (start != end) {
        string timeStr = getTimeStr((*start)->getTimestamp());
        cout << timeStr << "|" << (*start)->getCategory() << "|" << (*start)->getMsg() << endl;
        start++;
    }
}
