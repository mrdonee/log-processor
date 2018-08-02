//
//  Structs.hpp
//  Logman
//
//  Created by Mitchell Donahue on 8/1/18.
//  Copyright © 2018 Mitchell Donahue. All rights reserved.
//

#ifndef Structs_hpp
#define Structs_hpp

#include <stdio.h>
#include <string>
#include <algorithm>
using namespace std;

class LogMsg {
    string category;
    string msg;
    int entryId;
    int timestamp;
public:
    LogMsg(){}
    LogMsg(int t, string c, string m, int id) {
        timestamp = t;
        category = c;
        msg = m;
        entryId = id;
    }
    bool operator<(const LogMsg* msg) const {
        return timestamp < msg->timestamp;
    }
    int getTimestamp() const { return timestamp; }
    string getCategory() const { return category; }
    string getMsg() const { return msg; }
    int getEntryId() const { return entryId; }
};

#endif /* Structs_hpp */
