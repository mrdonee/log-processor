//
//  Logman.hpp
//  Logman
//
//  Created by Mitchell Donahue on 8/1/18.
//  Copyright © 2018 Mitchell Donahue. All rights reserved.
//

#ifndef Logman_hpp
#define Logman_hpp

#include <stdio.h>
#include "Structs.hpp"
#include <vector>
#include <unordered_map>
#include <set>

class Logman {
    struct LogMsgTimeComp {
        bool operator()(const LogMsg* lhs, const LogMsg* rhs) const  {
            return lhs->getTimestamp() < rhs->getTimestamp();
        }
    };
public:
    unordered_map<string, vector<int>> wordsToEntryIds;
    vector<LogMsg> masterFiles;
    set<LogMsg*, LogMsgTimeComp> masterSortedByTime;
    vector<LogMsg*> excerptList;
};

#endif /* Logman_hpp */
