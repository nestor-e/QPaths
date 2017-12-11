#ifndef _TILEH_
#define _TILEH_

class Tile{
    private:
        double Q[4];
        double R[4];
        Tile* A[4];
        int roomId;
        int pos[2];
        int tNum;
        int distance;
    public:
        void init(int id, int num, int width);
        Tile* next();
        std::string getRoomName();
        void qLearn();
        bool isLearned();
        void setAdj(Tile* left, Tile* right, Tile* up, Tile* down);
        void initQ();
        void initR(int goal);
};


#endif
