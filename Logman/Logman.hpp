//
//  Logman.hpp
//  Logman
//
//  Created by Mitchell Donahue on 8/1/18.
//  Copyright © 2018 Mitchell Donahue. All rights reserved.
//

#ifndef Logman_hpp
#define Logman_hpp

#include "Structs.hpp"
#include <set>
#include <stdio.h>
#include <unordered_map>
#include <vector>

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
    
    void processInput(const string &filename);
    
    void setItrs(set<LogMsg*>::iterator &lowerBound, set<LogMsg*>::iterator &upperBound, string &timeArg);
};

#endif /* Logman_hpp */
