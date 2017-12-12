#include "DataBuilder.h"
#include "Tile.h"
#include "QPaths.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>

using namespace std;

bool fileExists(string path, string name){
    string f = path + "/" + name;
    return (bool) ifstream (f);
}


bool DataBuilder::load(char* metaName){
    if(init){
        return false;
    }

    string fullPath (metaName);
    string path;
    size_t split = fullPath.find_last_of("/");
    if(split == fullPath.npos){
        path = ".";
    } else {
        path = fullPath.substr(0, split);
    }

    ifstream mFile (fullPath);
    if(mFile){
        int row, col, rms;
        string n1, n2, n3, label;
        bool allGood = true;

        mFile >> label >> rms;
        if(label.compare("rooms:") != 0 || rms < 1){
            cerr << "Error parsing line 1" << endl;
            allGood = false;
        }

        mFile >> label >> n1;
        if(label.compare("room_list:") != 0 || !fileExists(path, n1)){
            cerr << "Error parsing line 2" << endl;
            allGood = false;
        }

        mFile >> label >> row;
        if(label.compare("grid_rows:") != 0 || row < 1){
            cerr << "Error parsing line 3" << endl;
            allGood = false;
        }

        mFile >> label >> col;
        if(label.compare("grid_cols:") != 0 || col < 1){
            cerr << "Error parsing line 4" << endl;
            allGood = false;
        }

        mFile >> label >> n2;
        if(label.compare("grid_id:") != 0 || !fileExists(path, n2)){
            cerr << "Error parsing line 5" << endl;
            allGood = false;
        }

        mFile >> label >> n3;
        if(label.compare("grid_con:") != 0 || !fileExists(path, n3)){
            cerr << "Error parsing line 6" << endl;
            allGood = false;
        }

        if(allGood){
            w = col;
            h = row;
            rCount = rms;
            rName = path + "/" + n1;
            aName = path + "/" + n3;
            tName = path + "/" + n2;
            init = true;
        } else {
            return false;
        }
    } else {
        cerr << "Could not find file: " << fullPath << endl;
        return false;
    }
    return getTiles() && getRooms();
}


bool DataBuilder::getRooms(){
    if(!init){
        return false;
    }
    roomData.reserve(rCount + 1);  //  Cant do this because no constructor
    int roomId, x, y;
    string roomName;
    ifstream f (rName);
    string line, temp;
    Room cur;
    while(getline(f, line)){
        stringstream ls (line);
        getline(ls, temp, ',');
        roomId = stoi(temp);
        getline(ls, roomName, ',');
        getline(ls, temp, ',');
        x = stoi(temp);
        getline(ls, temp);
        y = stoi(temp);

        assert(roomId > 0 && roomId <= rCount);
        assert(x < w && y < h);
        assert(tiles[y*w + x].getRoomId() == roomId);
        cur.name = roomName;
        cur.origin = &(tiles[y*w + x]);
        roomData[roomId] = cur;
    }
    return true;
}

bool DataBuilder::getTiles(){
    if(init){
        tiles.reserve(w * h);
        ifstream idFile (tName);
        string idLine;
        int tileCount = 0;
        while( getline(idFile, idLine) ){
            stringstream idStream (idLine);
            string idToken;
            while( getline(idStream, idToken, ',')){
                int rId = stoi(idToken);
                tiles[tileCount].init(rId, tileCount, w);
                tileCount++;
            }
        }
        idFile.close();
        ifstream adjFile (aName);
        string adjLine;
        tileCount = 0;
        while( getline(adjFile, adjLine) ){
            stringstream adjStream (adjLine);
            string adjToken;
            while( getline(adjStream, adjToken, ',')){
                if(adjToken.length() == 4){
                    Tile* left, right, up, down;
                    if(adjToken[0] == 'y'){
                        assert(tileCount % w != 0);
                        left = &(tiles[tileCount - 1]);
                    } else {
                        left = NULL;
                    }
                    if(adjToken[1] == 'y'){
                        assert(tileCount % w != w - 1);
                        left = &(tiles[tileCount + 1]);
                    } else {
                        left = NULL;
                    }
                    if(adjToken[2] == 'y'){
                        assert(tileCount - w >= 0);
                        left = &(tiles[tileCount - w]);
                    } else {
                        left = NULL;
                    }
                    if(adjToken[3] == 'y'){
                        assert(tileCount + w < w * h);
                        left = &(tiles[tileCount + w]);
                    } else {
                        left = NULL;
                    }
                } else {
                    tiles[tileCount].setAdj(NULL, NULL, NULL, NULL);
                }
                tileCount++;
            }
        }
        adjFile.close();
        return true;
    } else {
        return false;
    }
}

int DataBuilder::width() {
    return (init)?(w):(0);
}

int DataBuilder::height() {
    return (init)?(h):(0);
}
