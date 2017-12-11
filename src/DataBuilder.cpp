#include "DataBuilder.h"
#include <fstream>
#include <iostream>
#include <sstream>

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
    return true;
}

vector<Room>* DataBuilder::getRooms(){
    if(!init){
        return NULL;
    }
    vector<Room>* rooms = new vector<Room>();
    Room cur;
    rooms->push_back(cur);
    int id, x, y;
    ifstream f (rName);
    string line, temp;
    while(getline(f, line)){
        stringstream ls (line);
        getline(ls, temp, ',');
        id = stoi(temp);
        getline(ls, temp, ',');
        cur.name = temp;
        getline(ls, temp, ',');
        x = stoi(temp);
        getline(ls, temp);
        y = stoi(temp);
        cur.origin = y * w + x;
        rooms->push_back(cur);
    }
    return rooms;
}

vector<Tile>* DataBuilder::getTiles(){
    if(!init){
        return NULL;
    }
    Tile cur;
    vector<Tile>* tiles = new vector<Tile>();
    ifstream idFile (tName);
    ifstream adjFile (aName);
    string idLine, adjLine;
    while( getline(idFile, idLine) && getline(adjFile, adjLine) ){
        stringstream idStream (idLine);
        stringstream adjStream (adjLine);
        string idToken, adjToken;
        while( getline(idStream, idToken, ',') && getline(adjStream, adjToken, ',')){
            cur.rId = stoi(idToken);
            if(adjToken.length() == 4){
                for(int i = 0; i < 4; i++){
                    cur.adj[i] = adjToken[i] == 'y';
                for(int i = 0; i < 4; i++){
                    cur.adj[i] = false;
                }
            }
            tiles->push_back(cur);
        }
    }
    return tiles;
}

int DataBuilder::width() {
    return (init)?(w):(0);
}

int DataBuilder::height() {
    return (init)?(h):(0);
}
