#ifndef _DATABUILDERH_
#define _DATABUILDERH_
#include <vector>
#include <string>
#include "QPathsData.h"

class DataBuilder {
    private:
        int w, h, rCount;
        bool init = false;
        std::string rName, aName, tName;
    public:
        bool load(char* metaName);
        std::vector<Room>* getRooms();
        std::vector<Tile>* getTiles();
        int width();
        int height();
};
#endif
