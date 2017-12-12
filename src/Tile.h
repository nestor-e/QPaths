#ifndef _TILEH_
#define _TILEH_

#include <limits>
#include <string>

class Tile{
    private:
        double Q[4];
        double R[4];
        Tile* A[4];
        int roomId;
        int pos[2];
        int tNum;
        int distance;
        bool isReal;
    public:
        void init(int id, int num, int width);
        int next();
        std::string getRoomName();
        int getRoomId();
        void qLearn();
        bool isLearned();
        void setAdj(Tile* left, Tile* right, Tile* up, Tile* down);
        void initQ();
        void initR(int goal);
        static constexpr double GAMMA = 0.9;
        static constexpr double RMAX = 100.0;
        static constexpr double QNULL = - std::numeric_limits<double>::max();
};



#endif
