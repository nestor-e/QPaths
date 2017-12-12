#ifndef _QPATHSH_
#define _QPATHSH_
#include <string>
#include <vector>
#include "Tile.h"

typedef struct {
    std::string name;
    Tile* origin;
} Room;

extern std::vector<Room> roomData;
extern std::vector<Tile> tiles;

#endif
