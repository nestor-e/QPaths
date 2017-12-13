/*
    Edward Nestor
    CSCI 402: AI
    Final Project: Q Learning for path finding
    QPaths.cpp: Contains main method as well as helper functions and shared data
    structures.
*/

#include <iostream>
#include <string>
#include <cctype>
#include <queue>
#include "DataBuilder.h"
#include "QPaths.h"

using namespace std;

//  Global shared data structure definitions
vector<Room> roomData;
vector<Tile> tiles;


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

Room* findRoom(string* name){
    if(name == NULL ){
        return NULL;
    }
    for(int i = 0; i < roomData.size(); i++){
        if( compareString( name, roomData[i].name) ){
            return &(roomData[i]);
        }
    }
    return NULL;
}

bool parseArgs(int argc, char* argv[], bool* useInit, bool* verboseMode){
    if(argc != 4){
        cerr << "Usage " << argv[0] << " {path to data} {initialize Q y/n} {use verbose printing y/n}" << endl;
        return false;
    }
    *useInit = argv[2][0] == 'y' || argv[2][0] == 'Y';
    *verboseMode = argv[3][0] == 'y' || argv[3][0] == 'Y';
    return true;
}


vector<Tile*> getPath(Tile* target, Tile* home){
    vector<Tile*> path;
    Tile* cur =  target;
    path.push_back(cur);
    while( cur != home ){
        cur = cur->nextTile();
        path.push_back(cur);
    }
    return path;
}

int main(int argc, char* argv[]){
    bool initQfromDistance, verbosePrinting;
    string homeName ("441");
    string quitText ("quit");
    string listText ("list");
    string promptText ("Target/Command: ");

    if ( parseArgs(argc, argv, &initQfromDistance, &verbosePrinting) ){

        //  Set up roomData and tiles data structures
        DataBuilder db;
        if( !db.load(argv[1]) ){
            return EXIT_FAILURE;
        }

        Room* home = findRoom(&homeName);

        if(home == NULL ){
            cerr << "Unable to locate home room: " << homeName << endl;
            return EXIT_FAILURE;
        }
        Tile* homeTile = home->origin;
        if(homeTile == NULL ){
            cerr << "Home room " << homeName << " has no associated tile"<< endl;
            return EXIT_FAILURE;
        }

        Tile::calcTables(homeTile, initQfromDistance);


        // Learning
        int epochCount = 0;
        Tile* startPoint = Tile::selectUnstable(homeTile);
        while( startPoint != NULL ){
            epochCount++;
            if(verbosePrinting){
                cout << "Begining training pass " << epochCount << endl;
                startPoint->qLearn(homeTile, verbosePrinting);
                startPoint = Tile::selectUnstable(homeTile);
                cout << endl ;
            } else {
                startPoint->qLearn(homeTile, verbosePrinting);
                startPoint = Tile::selectUnstable(homeTile);
            }
        }

        // Read-Eval-Print
        string cmd;
        cout << promptText;
        while(cin >> cmd){
            if( compareString(&cmd, &quitText) ){
                break;
            } else if( compareString(&cmd, &listText) ){
                for(int i = 1; i < roomData.size(); i++){
                    cout << *(roomData[i].name) << endl;
                }
            } else {
                Room* target = findRoom(&cmd);
                if(target == NULL){
                    cout << "Room " << cmd << " not recognied." << endl;
                } else {
                    vector<Tile*> path = getPath( target->origin, homeTile);
                    for(int i = path.size() - 1; i >= 0; i--){
                        cout << *(path[i]->getRoomName()) << ":" << path[i]->getCoords() << " --> ";
                    }
                    for(int i = 1; i < path.size() - 1; i++){
                        cout << *(path[i]->getRoomName()) << ":" << path[i]->getCoords() << " --> ";
                    }
                    cout << *(path[path.size() - 1]->getRoomName()) << ":" << path[path.size() - 1]->getCoords() << endl;
                }
            }
            cout << promptText;
        }

        cout << endl;
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}
