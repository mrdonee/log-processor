//
//  Utils.h
//  Logman
//
//  Created by Mitchell Donahue on 8/2/18.
//  Copyright © 2018 Mitchell Donahue. All rights reserved.
//

#ifndef Utils_h
#define Utils_h

void getTimeInt(string &s);

string getTimeStr(int i);

void printRecentTime(set<LogMsg*>::iterator start, set<LogMsg*>::iterator end);


#endif /* Utils_h */
