#include "patternMatching.h"
#include <algorithm>
#include <bits/fs_fwd.h>
#include <bits/ranges_algo.h>
#include "pattern.h"
#include <iostream>

using namespace std;

bool patternMatching::inBoundsCheck(int a, int mod, int max) {
    int checkBoundNum = a + mod;

    if((checkBoundNum>=0)and(checkBoundNum < max)){return true;}
    return false;
}

bool patternMatching::blockSearch(bool** world, int x, int y, int xMax, int yMax, int iteration) {
    if (world[x][y] != true) {return false;}
    Block block;
    int correctCells=1;
    int aliveCells=0;
    bool found=false;
    for (int i=0; i<2; i++) {
        for (int j=0; j<2; j++) {
            for (int k=0; k<3; k++) {
                if (i==block.truePattern[k][0] and j==block.truePattern[k][1]) {
                    if(inBoundsCheck(x,i,xMax) and inBoundsCheck(y,j,yMax)) {
                        if (world[x+i][y+j] == true){correctCells++;}
                    }
                }
            }
        }
    }
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if(inBoundsCheck(x,block.patternCheckArea[i],xMax) and inBoundsCheck(y,block.patternCheckArea[j],yMax)) {
                if (world[x+block.patternCheckArea[i]][y+block.patternCheckArea[j]] == true) {aliveCells++;}
            }
        }
    }
    if (correctCells == 4 and aliveCells == correctCells) {
        cout<<"found"<<"\n";
        found = true;
        return true;
    }


    /*int correctNeeded = 36;
    //cout<<"pattern looked at"<<"\n";
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if(inBoundsCheck(x,block.patternCheckArea[i],xMax) and inBoundsCheck(y,block.patternCheckArea[j],yMax)) {
                if (world[x+block.patternCheckArea[i]][y+block.patternCheckArea[j]] == false) {correctCells++;} //segmentation fault possible
                else if (i==0 and j==0){correctCells++;}
                else {
                    for (int k=0; k<3; k++) {
                        if (block.patternCheckArea[i]==block.truePattern[k][0] and block.patternCheckArea[j]==block.truePattern[k][1]) {
                            if (world[x+block.patternCheckArea[i]][y+block.patternCheckArea[j]] == true){correctCells++;}
                        }
                    }
                }

            }
            else if((block.patternCheckArea[i]<0 or block.patternCheckArea[i]>1) or (block.patternCheckArea[j]<0 or block.patternCheckArea[j]>1)) {correctNeeded--;}
        }
    }
    if (correctCells == correctNeeded) {
        return true;*/
        /*
        if (patternMatchData.firstFound == true and iteration == patternMatchData.fI) {
            cout <<"found"<<"\n";
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
        */
    //}
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
    bool confirmFound = false;
    if (iteration !=0 and iteration == patternMatchData.fI) {
        confirmFound = patternSwitch(searchVariable, current, xSize, ySize, patternMatchData.fX, patternMatchData.fY, iteration);
        if (confirmFound == true) {return true;}
    }

    for (int i = 0; i < xSize; i++) {
        for (int j = 0; j < ySize; j++) {
            bool cellCheck = current[i][j];
            if (cellCheck == true) {
                confirmFound = patternSwitch(searchVariable, current, xSize, ySize, i, j, iteration);
                if (confirmFound == true) {return true;}
            }
        }
    }
    return false;
}


