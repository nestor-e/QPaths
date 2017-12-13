#include "Tile.h"
#include "QPaths.h"
#include <cmath>
#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <queue>
#include <sstream>

using namespace std;

void Tile::init(int id, int num, int width){
    roomId = id;
    tNum = num;
    stablePasses = 0;
    pos[0] = num % width;
    pos[1] = num / width;
    for(int i = 0; i < 4; i++){
        Q[i] = 0.0;
        R[i] = 0.0;
        A[i] = NULL;
    }
    distance = -1;
    isReal = roomId > 0;
}

int Tile::getRoomId(){ return roomId; }

int Tile::next(){
    if(! isReal ){
        return 0;
    }

    double maxValue = Q[0];
    int maxOccurances = 1;
    for(int i = 1; i < 4; i++){
        if(Q[i] > maxValue){
            maxValue = Q[i];
            maxOccurances = 1;
        }else if (Q[i] == maxValue){
            maxOccurances++;
        }
    }
    assert(maxValue > Tile::QNULL && maxOccurances > 0);
    int choice = rand() % maxOccurances;
    for(int i = 0; i < 4; i++){
        if(Q[i] == maxValue){
            if (choice == 0){
                return i;
            } else {
                choice--;
            }
        }
    }
    assert(false && "Failed to select any next tile, somthing gone terribly wrong");
    return 0;
}

bool Tile::isLearned(){
    return !isReal || stablePasses >= PASSES ;
}

Tile* Tile::nextTile(){
    if(isReal){
        return A[next()];
    } else {
        return NULL;
    }
}


void Tile::setAdj(Tile* left, Tile* right, Tile* up, Tile* down){
    if(isReal){
        assert(left != NULL || right != NULL || up != NULL || down != NULL);
        A[0] = left;
        A[1] = right;
        A[2] = up;
        A[3] = down;
    }
}

string* Tile::getRoomName(){
    if(!isReal){
        return NULL;
    } else {
        return roomData[roomId].name;
    }
}

Tile* Tile::qLearnRec(Tile* home, bool verbose){
    int action = next();
    Tile* nextState =  A[action];
    double oldQ = Q[action];

    //  Q Learning algorithim
    if(nextState == home){
        Q[action] = R[action];
    } else {
        Q[action] = R[action] + GAMMA * nextState->Q[nextState->next()];
    }

    //  Check for stability
    double stability = abs( (oldQ - Q[action])  / oldQ ) ;
    if(stability < STABILITY_THRESHOLD){
        stablePasses++;
    } else {
        stablePasses = 0;
    }

    //  Print summary if verbose
    if(verbose){
        cout << "Room " << tNum <<  ", " ;
        switch(action){
            case 0:
                cout << "Left, ";
                break;
            case 1:
                cout << "Right, ";
                break;
            case 2:
                cout << "Up, ";
                break;
            case 3:
                cout << "Down, ";
                break;
        }
        cout << "Q-Prior: " << oldQ << ", ";
        cout << "Q-Post: " << Q[action] << endl;
    }

    return nextState;
}


//  Q-Learn is kind of a recursive algorithim, doing this thing with returning
//  the pointer to the next Tile to avvoid creating tons of stack frames.
void Tile::qLearn(Tile* home, bool verbose){
    if(isReal){
        Tile* cur = this;
        while(cur != home){
            cur = cur->qLearnRec(home, verbose);
        }
    }
}

void Tile::initQ(){
    for(int i = 0; i < 4; i++){
        if( A[i] != NULL ){
            if(A[i]->distance < 0){
                Q[i] = 0;
            } else {
                Q[i] = Tile::RMAX * pow(Tile::GAMMA, (double) A[i]->distance);
            }
        } else {
            Q[i] = Tile::QNULL;
        }
    }
}

void Tile::initR(Tile* home){
    for(int i = 0; i < 4; i++){
        if(A[i] != NULL){
            if( A[i] == home){
                R[i] = Tile::RMAX;
            } else {
                R[i] = 0;
            }

        } else {
            R[i] = Tile::QNULL;
        }
    }
}



void Tile::calcDistances(Tile* home){
    assert(home != NULL);
    queue<Tile*> expand;
    for(int i = 0; i < tiles.size(); i++){
        tiles[i].distance = -1;
    }
    home->distance = 0;
    expand.push(home);
    while(! expand.empty() ){
        Tile* cur = expand.front();
        expand.pop();
        for(int i = 0; i < 4; i++){
            Tile* next = cur->A[i];
            if(next != NULL && next->isReal && next->distance < 0){
                next->distance = cur->distance + 1;
                expand.push(next);
            }
        }
    }
}

void Tile::calcTables(Tile*  home, bool useDistance){
    if(useDistance){
        calcDistances(home);
    }
    for(int i = 0; i < tiles.size(); i++){
        tiles[i].initR(home);
        tiles[i].initQ();
    }
}

Tile* Tile::selectUnstable(Tile* home){
    vector<int> s;
    int homeId = home->tNum;
    for(int i = 0; i < tiles.size(); i++){
        if( i != homeId && tiles[i].isReal && !(tiles[i].isLearned()) ){
            s.push_back(i);
        }
    }
    if(s.size() > 0){
        int sel = s[rand() % s.size()];
        return &(tiles[sel]);
    } else {
        return NULL;
    }
}

string Tile::getCoords(){
    stringstream s;
    s << "(" << pos[0] << "," << pos[1] << ")" ;
    return s.str();
}
