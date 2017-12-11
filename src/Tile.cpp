#include "Tile.h"
#include <cmath>
#include <string>

using namespace std;


void Tile::init(int id, int num, int width){
    roomId = id;
    tNum = num;
    pos[0] = num % width;
    pos[1] = num / width;
    Q = {0, 0, 0, 0};
    R = {0, 0, 0, 0};
    A = {NULL, NULL, NULL, NULL};
    distance = -1;
}

Tile* next(){
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
    assert(maxValue > QNULL && maxOccurances > 0);
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
    assert(left != NULL || right != NULL || up != NULL || down != NULL);
    A = {left, right, up, down};
}

string Tile::getRoomName(){
    if(roomId < 1 || roomId >= roomData.size){
        return string ("Unkown");
    } else {
        return roomData[roomId].name;
    }
}

void Tile::initQ(){
    for(int i = 0; i < 4; i++){
        if( A[i] != NULL ){
            if(*(A[i]).distance < 0){
                Q[i] = 0;
            } else {
                Q[i] = QMAX * pow(GAMMA, (double) *(A[i]).distance);
            }
        } else {
            Q[i] = QNULL;
        }
    }
}

void Tile::initR(int goal){
    for(int i = 0; i < 4; i++){
        if(A[i] != NULL){
            if( *(A[i]).tNum == goal){
                R[i] = QMAX;
            } else {
                R[i] = 0;
            }
    } else {
        R[i] = QNULL;
    }
}
