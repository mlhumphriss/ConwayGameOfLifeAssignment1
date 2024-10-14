#include "randomBoardGenerator.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;

void boardGenerator::assignLife(bool** world1, bool** world2, bool** seedWorld, int x, int y) {
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



int boardGenerator::createWorld(int xD, int yD, int lS) {
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
    world1Pointer = world1;
    world2Pointer = world2;
    seed = seedWorld;
    return 0;
}

int boardGenerator::inputSeed() {
    string filename;
    cout << "Input filename in form file.txt: "<<"\n";
    cin >> filename;
    ifstream infile(filename);
    infile>>xDimension;
    infile>>yDimension;
    bool** loadedWorld1 = new bool*[xDimension];
    bool** loadedWorld2 = new bool*[xDimension];
    for (int i = 0; i < xDimension; i++) {
        loadedWorld1[i] = new bool[yDimension];
        loadedWorld2[i] = new bool[yDimension];
        for (int j = 0; j <yDimension; j++) {
            infile>>loadedWorld1[i][j];
        }
    }
    world1Pointer = loadedWorld1;
    world2Pointer = loadedWorld2;

    return 0;

}



int boardGenerator::inputSeedVariables() {

    cout<< "Input X Dimension size: "<< "\n";
    cin>> xDimension;
    cout<< "Input Y Dimension size: "<< "\n";
    cin>> yDimension;
    cout<< "Input Starting Alive cells: "<< "\n";
    cin>> startLife;
    createWorld(xDimension, yDimension, startLife);
    return 0;
}