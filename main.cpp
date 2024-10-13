#include <iostream>
#include "randomBoardGenerator.h"
using namespace std;

bool cellState(bool** current, int x, int y) {
    int neighbourCount = 0;
    if (current[x-1][y+1] == true) {
        neighbourCount++;
    }
    if (current[x][y+1] == true) {
        neighbourCount++;
    }
    if (current[x+1][y+1] == true) {
        neighbourCount++;
    }
    if (current[x-1][y] == true) {
        neighbourCount++;
    }
    if (current[x+1][y] == true) {
        neighbourCount++;
    }
    if (current[x-1][y-1] == true) {
        neighbourCount++;
    }
    if (current[x][y-1] == true) {
        neighbourCount++;
    }
    if (current[x+1][y-1] == true) {
        neighbourCount++;
    }
    if (neighbourCount == 3) {
        return true;
    }
    if (neighbourCount == 2 and current[x][y] == true) {
        return true;
    }
    return false;
}

void displayBoard(bool** board, int x, int y) {
    for (int i=0; i< x; i++) {
        for (int j=0; j< y; j++) {
            if (board[i][j] == true) {
                cout << ".0";
            }
            else {
                cout << ". ";
            }
        }
        cout <<"."<< endl;
    }
}


int calculateNextFrame(bool** current, bool** next) {
    bool nextState;
    int xSize = sizeof(current)/sizeof(current[0]);
    int ySize = sizeof(current[0])/sizeof(current[0][0]);
    for (int i=0; i< xSize; i++) {
        for (int j=0; j< ySize; j++) {
            nextState = cellState(current,i, j);
            next[i][j] = nextState;
        }
    }
    displayBoard(next, xSize, ySize);
    return 0;
}




int main()
{   //Where stuff starts breaking, need ask for how fix this shit
    randomBoardGenerator::inputSeedVariables();
    calculateNextFrame(randomBoardGenerator::currentWorld, randomBoardGenerator::nextWorld);

    return 0;
}
