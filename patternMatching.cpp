#include "patternMatching.h"
#include <algorithm>
#include <bits/fs_fwd.h>
#include <bits/ranges_algo.h>
#include "pattern.h"
#include <iostream>

using namespace std;

bool patternMatching::inBoundsCheck(int a, int mod, int max) {
    if((a+mod >= 0)or(a+mod < max)){return true;}
    return false;
}

bool patternMatching::blockSearch(bool** world, int x, int y, int xMax, int yMax, int iteration) {
    if (world[x][y] != true) {return false;}
    Block block;
    int correctCells=0;
    int correctNeeded = 36;

    for (int i = block.patternCheckArea[0]; i < block.patternCheckArea[1]; i++) {
        for (int j = block.patternCheckArea[0]; j < block.patternCheckArea[1]; j++) {
            if(inBoundsCheck(x,i,xMax) and inBoundsCheck(y,j,yMax)) {
                if (world[x+i][y+j] == false) {correctCells++;}
                else if (i==0 and j==0){correctCells++;}
                else {
                    for (int k=0; k<3; k++) {
                        if (i==block.truePattern[k][0] and j==block.truePattern[k][1]) {
                            if (world[x+i][y+j] == true){correctCells++;}
                        }
                    }
                }

            }
            else if((i<0 or i>1) or (j<0 or j>1)) {correctNeeded--;}
        }
    }
    if (correctCells == correctNeeded) {
        if (patternMatchData.firstFound == true and iteration == patternMatchData.fI) {
            //cout <<"found"<<"\n";
            return true;
        }
        if (patternMatchData.firstFound == true and iteration != patternMatchData.fI) {return false;}
        else {
            patternMatchData.firstFound = true;
            patternMatchData.fX = x;
            patternMatchData.fY = y;
            patternMatchData.fI = iteration + 2;
            return false;
        }
    }
    return false;
}

bool beehiveSearch(bool** world, int x, int y, int xMax, int yMax, int iteration) {
    return false;
}

bool blinkerSearch(bool** world, int x, int y, int xMax, int yMax, int iteration) {
    return false;
}

bool toadSearch(bool** world, int x, int y, int xMax, int yMax, int iteration) {
    return false;
}

bool gliderSearch(bool** world, int x, int y, int xMax, int yMax, int iteration) {
    return false;
}

bool lwssSearch(bool** world, int x, int y, int xMax, int yMax, int iteration) {
    return false;
}



bool patternMatching::patternSwitch (int searchVariable, bool** world, int xMax, int yMax, int x, int y, int iteration) {
    bool searchResult;
    switch (searchVariable) {
        case 1:
            searchResult = blockSearch(world, x, y, xMax, yMax, iteration);
        break;
        case 2:
            searchResult = beehiveSearch(world, x, y, xMax, yMax, iteration);
        break;
        case 3:
            searchResult = blinkerSearch(world, x, y, xMax, yMax, iteration);
        break;
        case 4:
            searchResult = toadSearch(world, x, y, xMax, yMax, iteration);
        break;
        case 5:
            searchResult = gliderSearch(world, x, y, xMax, yMax, iteration);
        break;
        case 6:
            searchResult = gliderSearch(world, x, y, xMax, yMax, iteration);
        break;

    }
    return searchResult;
}


bool patternMatching::patternSort(bool **current, bool **next, int xSize, int ySize, int searchVariable, int iteration) {
    bool confirmFound;
    if (iteration !=0 and iteration == patternMatchData.fI) {
        confirmFound = patternSwitch(searchVariable, current, xSize, ySize, patternMatchData.fX, patternMatchData.fY, iteration);
        if (confirmFound == true) {return true;}
    }

    for (int i = 0; i < xSize; i++) {
        for (int j = 0; j < ySize; j++) {
            bool cellCheck = current[i][j];
            if (cellCheck == true) {
                patternSwitch(searchVariable, current, xSize, ySize, i, j, iteration);
            }
        }
    }
    return false;
}


