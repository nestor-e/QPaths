/*
    Edward Nestor
    CSCI 402: AI
    Final Project: Q Learning for path finding
    DataBuilder.h: Defines DataBuilder object, which parses data files to fill in
    the shared data structures in QPaths.h
*/

#ifndef _DATABUILDERH_
#define _DATABUILDERH_
#include <vector>
#include <string>
#include "QPaths.h"

class DataBuilder {
    private:
        int w, h, rCount;
        bool init = false;
        std::string rName, aName, tName;
        bool getRooms();
        bool getTiles();
    public:
        bool load(char* metaName);
        int width();
        int height();
};
#endif
