#ifndef _DATABUILDERH_
#define _DATABUILDERH_
#include <vector>
#include <string>

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
