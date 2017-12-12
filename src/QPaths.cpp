#include <iostream>
#include <string>
#include <cctype>
#include <queue>
#include "DataBuilder.h"
#include "QPaths.h"

using namespace std;


std::vector<Room> roomData;
std::vector<Tile> tiles;
/*

bool compareString(string* s1, string* s2){
    if(s1 == NULL || s2 == NULL || s1->length() != s2->length()){
        return false;
    } else {
        for(int i = 0; i < s1->length(); i++){
            char c1 = tolower(s1->at(i));
            char c2 = tolower(s2->at(i));
            if(c1 != c2){
                return false;
            }
        }
        return true;
    }

}


int roomIdByName(string* name){
    if(name == NULL ){|| rooms == NULL){
        return -1;
    }
    int loc = -1;
    for(int i = 1; i < rooms->size(); i++){
        if(compareString( name, &(rooms->at(i).name)) ){
            loc =  i;
            break;
        }
    }
    return loc;
}

*/
bool parseArgs(int argc, char* argv[]){
    if(argc != 2){
        cerr << "Usage ./QLearnPathFinder {path to data}" << endl;
        return false;
    }
}
/*
vector<int> getPath(Mtrx* q, int cur, int end){
    vector<int> path;
    path.push_back(cur);
    while( cur != end ){
        cout << cur << endl;
        int next = tileMaxQ(q, cur);
        switch(next){
            case 0:
                cur = left(cur);
                break;
            case 1:
                cur = right(cur);
                break;
            case 2:
                cur = up(cur);
                break;
            case 3:
                cur = down(cur);
                break;
            default:
                return path;
        }
        path.push_back(cur);
    }
    return path;
}

*/

int main(int argc, char* argv[]){
    if ( parseArgs(argc, argv) ){
        DataBuilder db;
        if( !db.load(argv[1]) ){
            return EXIT_FAILURE;
        }

        //rooms = db.getRooms();
        //db.getTiles();
        //string home ("440");
        //int homeId = roomIdByName(&home);
        //int homeTile = rooms->at(homeId).origin;

        // Learning

        // Read-Eval-Print
    /*    string cmd;
        cout << "Target: ";
        while(cin >> cmd){
            int targetId = roomIdByName(&cmd);
            if(targetId < 0){
                cout << "Room " << cmd << " not recognied." << endl;
            } else {
                vector<int> path = getPath(q, targetId, homeId);
                for(int i = path.size() - 1; i >= 0; i--){
                    cout << rooms->at(path[i]).name << " (" << path[i] << ")" << endl;
                }
                for(int i = 1; i < path.size(); i++){
                    cout << rooms->at(path[i]).name << " (" << path[i] << ")" << endl;
                }
            }
            cout << "Target: ";
        } */
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}
