#ifndef _QPATHSH_
#define _QPATHSH_
#include <string>
#include <vector>

typedef struct {
    std::string name;
    int origin;
} Room;

const double GAMMA = 0.9;
const double RMAX = 100.0;
const double QNULL = - std::numeric_limits<double>::max();

std::vector<Room> roomData;
std::vector<Tile> tiles;

#endif
