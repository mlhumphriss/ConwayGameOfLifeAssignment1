#include "randomBoardGenerator.h"
#include <iostream>
#include <cstdlib>
using namespace std;

void randomBoardGenerator::assignLife(bool** world1, bool** world2, bool** seedWorld, int x, int y) {
    srand((unsigned) time(NULL));
    int randX;
    int randY;

    do {
        randX = rand() % x;
        randY = rand() % y;
    } while (world1[randX][randY] == true);

    world1[randX][randY] = true;
    world2[randX][randY] = true;
    seedWorld[randX][randY] = true;




}



int randomBoardGenerator::createWorld(int xD, int yD, int lS) {
    bool** world1 = new bool*[xD];
    bool** world2 = new bool*[xD];
    bool** seedWorld = new bool*[xD];
    for (int i = 0; i < xD; i++) {
        world1[i] = new bool[yD];
        world2[i] = new bool[yD];
        seedWorld[i] = new bool[yD];

        for (int j = 0; j <yD; j++){
            world1[i][j] = false;
            world2[i][j] = false;
            seedWorld[i][j] = false;
        }
    }
    for (int k =0; k< lS; k++) {
        assignLife(world1, world2,seedWorld, xD, yD);
    }
    currentWorld = world1;
    nextWorld = world2;
    seed = seedWorld;
    return 0;
}





int randomBoardGenerator::inputSeedVariables() {

    cout<< "Input X Dimension size: "<< "\n";
    cin>> xDimension;
    cout<< "Input Y Dimension size: "<< "\n";
    cin>> yDimension;
    cout<< "Input Starting Alive cells: "<< "\n";
    cin>> startLife;
    createWorld(xDimension, yDimension, startLife);
    return 0;
}