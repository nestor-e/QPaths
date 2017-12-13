/*
    Edward Nestor
    CSCI 402: AI
    Final Project: Q Learning for path finding
    QPaths.h: Defines Room struct and primary shared data structures for storing Data
*/

#ifndef _QPATHSH_
#define _QPATHSH_
#include <string>
#include <vector>
#include "Tile.h"

typedef struct {
    std::string* name;
    Tile* origin;
} Room;

extern std::vector<Room> roomData;
extern std::vector<Tile> tiles;

#endif
