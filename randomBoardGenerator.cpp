#include "randomBoardGenerator.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;

void boardGenerator::assignLife(bool** world1, bool** world2, int x, int y, int seed) {
    srand(seed);
    int randX;
    int randY;

    do {
        randX = rand() % x;
        randY = rand() % y;
    } while (world1[randX][randY] == true);

    world1[randX][randY] = true;
    world2[randX][randY] = true;
}

void boardGenerator::resetWorld(bool **world1, int x, int y, bool**world2, int seed, int sLife) {
    for (int i = 0; i < x; i++) {
        for (int j = 0; j <y; j++){
            world1[i][j] = false;
            world2[i][j] = false;
        }
    }
    for (int k =0; k< sLife; k++) {
        assignLife(world1, world2, x, y, seed);
    }
}

int createToad(bool** world1, int xD, int yD) {
    //int truePattern1[5][2] = { {0,1}, {0, 2}, {-1, 1}, {-1, 2}, {-1,3} };

    for (int k = 0; k< 6; k++) {
        if (xD > 8 and yD >8) {
            world1[2][2] = true;
            world1[3][2] = true;
            world1[4][2] = true;
            world1[3][3] = true;
            world1[4][3] = true;
            world1[5][3] = true;
        }

    }
    return 0;
}



int boardGenerator::createWorld(int xD, int yD, int lS, int s) {
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
    //createToad(world1, xD, yD);


    for (int k =0; k< lS; k++) {
        assignLife(world1, world2, xD, yD, s);
    }

    world1Pointer = world1;
    world2Pointer = world2;
    return 0;
}

int boardGenerator::inputSeedFile() {
    string filename;
    cout << "Input filename in form file.txt: "<<"\n";
    cin >> filename;
    ifstream infile(filename);
    infile>>xDimension;
    infile>>yDimension;
    infile>>seed;
    infile>>startLife;
    infile.close();
    createWorld(xDimension,yDimension,startLife, seed);
    return 0;

}



int boardGenerator::inputSeedVariables() {
    cout<< "Input X Dimension size: "<< "\n";
    cin>> xDimension;
    cout<< "Input Y Dimension size: "<< "\n";
    cin>> yDimension;
    cout<< "Input Starting Alive cells: "<< "\n";
    cin>> startLife;
    cout <<"Input Starting Seed Number: "<< "\n";
    cin>> seed;
    createWorld(xDimension, yDimension, startLife, seed);
    return 0;
}