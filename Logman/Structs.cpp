//
//  Structs.cpp
//  Logman
//
//  Created by Mitchell Donahue on 8/2/18.
//  Copyright © 2018 Mitchell Donahue. All rights reserved.
//

#include "Structs.hpp"
#include <stdio.h>

bool LogMsgTimeComp::operator()(const LogMsg* lhs, const LogMsg* rhs) const  {
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
