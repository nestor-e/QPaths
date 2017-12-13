/*
    Edward Nestor
    CSCI 402: AI
    Final Project: Q Learning for path finding
    Tile.h: Defines Tile object, contains logic for Q Learning and path finding
    as well as managing the relations between tiles
*/

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
        int stablePasses;
        bool isReal;
        int next();
        void initQ();
        void initR(Tile* home);
        Tile* qLearnRec(Tile* home, bool verbose);
        static void calcDistances(Tile* home);

    public:
        void init(int id, int num, int width);
        Tile* nextTile();
        std::string* getRoomName();
        int getRoomId();
        std::string getCoords();
        void qLearn(Tile* home, bool verbose);
        bool isLearned();
        void setAdj(Tile* left, Tile* right, Tile* up, Tile* down);
        static void calcTables(Tile* home, bool useDistance);
        static bool systemStable();
        static Tile* selectUnstable(Tile* home);
        static constexpr double GAMMA = 0.9;
        static constexpr double RMAX = 100.0;
        static constexpr double QNULL = - std::numeric_limits<double>::max();
        static constexpr int PASSES = 3;
        static constexpr double STABILITY_THRESHOLD = 0.05;
};

#endif
