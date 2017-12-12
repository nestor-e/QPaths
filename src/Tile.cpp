#include "Tile.h"
#include <cmath>
#include <cassert>
#include <string>

using namespace std;


void Tile::init(int id, int num, int width){
    roomId = id;
    tNum = num;
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

void Tile::setAdj(Tile* left, Tile* right, Tile* up, Tile* down){
    if(isReal){
        assert(left != NULL || right != NULL || up != NULL || down != NULL);
        A[0] = left;
        A[1] = right;
        A[2] = up;
        A[3] = down;
    }
}

string Tile::getRoomName(){
    return NULL;
    /*if(roomId < 1 || roomId >= roomData.size){
        return string ("Unkown");
    } else {
        return roomData[roomId].name;
    }*/
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

void Tile::initR(int goal){
    for(int i = 0; i < 4; i++){
        if(A[i] != NULL){
            if( A[i]->tNum == goal){
                R[i] = Tile::RMAX;
            } else {
                R[i] = 0;
            }

        } else {
            R[i] = Tile::QNULL;
        }
    }
}
