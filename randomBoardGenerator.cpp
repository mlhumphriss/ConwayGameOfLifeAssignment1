#include "randomBoardGenerator.h"
#include <iostream>
#include <cstdlib>
using namespace std;

void assignLife(bool** world1, bool** world2, int x, int y) {
    srand((unsigned) time(NULL));
    int randX;
    int randY;

    do {
        randX = rand() % x;
        randY = rand() % y;
    } while (world1[randX][randY] == true);

    world1[randX][randY] = true;
    world2[randX][randY] = true;




}



int createWorld(int xD, int yD, int lS) {
    bool** world1 = new bool*[xD];
    bool** world2 = new bool*[xD];
    for (int i = 0; i < xD; i++) {
        world1[i] = new bool[yD];
        world2[i] = new bool[yD];

        for (int j = 0; j <yD; j++){
            world1[i][j] = false;
            world2[i][j] = false;
        }
    }
    for (int k =0; k< lS; k++) {
        assignLife(world1, world2, xD, yD);
    }
    return 0;
}





int inputSeedVariables() {
    int xDimension;
    int yDimension;
    int startLife;
    cout<< "Input X Dimension size: "<< "\n";
    cin>> xDimension;
    cout<< "Input Y Dimension size: "<< "\n";
    cin>> yDimension;
    cout<< "Input Starting Alive cells: "<< "\n";
    cin>> startLife;
    createWorld(xDimension, yDimension, startLife);
    return 0;
}