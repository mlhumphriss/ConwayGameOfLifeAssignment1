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
        cout<<"maybe found"<<"\n";

        if (patternMatchData.firstFound == true and iteration == patternMatchData.fI) {
            cout <<"found sure"<<"\n";
            return true;
        }
        if (patternMatchData.firstFound == true and iteration != patternMatchData.fI) {return false;}
        else {
            patternMatchData.firstFound = true;
            patternMatchData.fX = x;
            patternMatchData.fY = y;
            patternMatchData.fI = iteration + block.sequenceTotal;
            return false;
        }

    }
    return false;
}

bool patternMatching::beehiveSearch(bool** world, int x, int y, int xMax, int yMax, int iteration, int orientation) {
    int patternX;
    int patternY;
    if (world[x][y] != true) {return false;}
    if (orientation == 0) {patternX = 1; patternY = 0;}
    else{patternX = 0; patternY = 1;}
    Beehive hive;
    int correctCells=1;
    int aliveCells=0;
    if (orientation == 0) {
        for (int i=0; i<4; i++) {
            for (int j=-1; j<2; j++) {
                for (int k=0; k<5; k++) {
                    if (i==hive.truePattern[k][patternX] and j==hive.truePattern[k][patternY]) {
                        if(inBoundsCheck(x,i,xMax) and inBoundsCheck(y,j,yMax)) {
                            if (world[x+i][y+j] == true){correctCells++;}
                        }
                    }
                }
            }
        }
    }
    else {
        for (int i=-1; i<2; i++) {
            for (int j=-3; j<1; j++) {
                for (int k=0; k<5; k++) {
                    if (i==hive.truePattern[k][patternX] and j==hive.truePattern[k][patternY]) {
                        if(inBoundsCheck(x,i,xMax) and inBoundsCheck(y,j,yMax)) {
                            if (world[x+i][y+j] == true){correctCells++;}
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < patternX+7; i++) {
        for (int j = 0; j < patternY+7; j++) {
            if (patternX ==1) {
                if(inBoundsCheck(x,hive.patternCheckAreaL[i],xMax) and inBoundsCheck(y,hive.patternCheckAreaW[j],yMax)) {
                    if (world[x+hive.patternCheckAreaL[i]][y+hive.patternCheckAreaW[j]] == true) {aliveCells++;}
                }
            } else {
                if(inBoundsCheck(x,hive.patternCheckAreaW[i],xMax) and inBoundsCheck(y,hive.patternCheckAreaL[j],yMax)) {
                    if (world[x+hive.patternCheckAreaW[i]][y+hive.patternCheckAreaL[j]] == true) {aliveCells++;}
                }
            }
        }
    }
    if (correctCells == 6 and aliveCells == correctCells) {
        cout<<"maybe found"<<"\n";

        if (patternMatchData.firstFound == true and iteration == patternMatchData.fI) {
            cout <<"found sure"<<"\n";
            return true;
        }
        if (patternMatchData.firstFound == true and iteration != patternMatchData.fI) {return false;}
        else {
            patternMatchData.firstFound = true;
            patternMatchData.fX = x;
            patternMatchData.fY = y;
            patternMatchData.fI = iteration + hive.sequenceTotal;
            patternMatchData.orientation = orientation;
            return false;
        }

    }


    return false;
}

bool patternMatching::blinkerSearch(bool **world, int x, int y, int xMax, int yMax, int iteration, int orientation) {
    int patternX;
    int patternY;
    if (world[x][y] != true) {return false;}
    if (orientation == 0) {patternX = 1; patternY = 0;}
    else{patternX = 0; patternY = 1;}
    Blinker blink;
    int correctCells=1;
    int aliveCells=0;
    if (orientation == 0) {
        for (int i=-1; i<2; i++) {
            for (int k=0; k<2; k++) {
                if (i==blink.truePattern[k][patternX] and 0==blink.truePattern[k][patternY]) {
                    if(inBoundsCheck(x,i,xMax)) {
                        if (world[x+i][y] == true){correctCells++;}
                    }
                }
            }
        }
        patternX++;
    }
    else {
        for (int j=-1; j<2; j++) {
            for (int k=0; k<2; k++) {
                if (0==blink.truePattern[k][patternX] and j==blink.truePattern[k][patternY]) {
                    if(inBoundsCheck(y,j,yMax)) {
                        if (world[x][y+j] == true){correctCells++;}
                    }
                }
            }
        }
        patternY++;

    }

    for (int i = 0; i < patternX+5; i++) {
        for (int j = 0; j < patternY+5; j++) {
            if (patternX ==2) {
                if(inBoundsCheck(x,blink.patternCheckAreaL[i],xMax) and inBoundsCheck(y,blink.patternCheckAreaW[j],yMax)) {
                    if (world[x+blink.patternCheckAreaL[i]][y+blink.patternCheckAreaW[j]] == true) {aliveCells++;}
                }
            } else {
                if(inBoundsCheck(x,blink.patternCheckAreaW[i],xMax) and inBoundsCheck(y,blink.patternCheckAreaL[j],yMax)) {
                    if (world[x+blink.patternCheckAreaW[i]][y+blink.patternCheckAreaL[j]] == true) {aliveCells++;}
                }
            }
        }
    }
    if (correctCells == 3 and aliveCells == correctCells) {
        cout<<"maybe found"<<"\n";

        if (patternMatchData.firstFound == true and iteration == patternMatchData.fI) {
            cout <<"found sure"<<"\n";
            return true;
        }
        if (patternMatchData.firstFound == true and iteration != patternMatchData.fI) {return false;}
        else {
            patternMatchData.firstFound = true;
            patternMatchData.fX = x;
            patternMatchData.fY = y;
            patternMatchData.fI = iteration + blink.sequenceTotal;
            patternMatchData.orientation = orientation;
            return false;
        }

    }


    return false;
}

bool patternMatching::toadSearch(bool** world, int x, int y, int xMax, int yMax, int iteration, int orientation) {
    int patternX;
    int patternY;
    if (world[x][y] != true) {return false;}
    if (orientation == 0) {patternX = 1; patternY = 0;}
    else{patternX = 0; patternY = 1;}
    Toad toad;
    int correctCells=1;
    int aliveCells=0;

//int truePattern1[5][2] = { {0,1}, {0, 2}, {-1, 1}, {-1, 2}, {-1,3} };
    /*
    if (orientation == 0) {
        for (int i=0; i<4; i++) {
            for (int j=-1; j<1; j++) {
                for (int k=0; k<5; k++) {
                    if (i==toad.truePattern1[k][patternX] and j==toad.truePattern1[k][patternY]) {
                        if(inBoundsCheck(x,i,xMax) and inBoundsCheck(y,j,yMax)) {
                            if (world[x+i][y+j] == true){correctCells++;}
                        }
                    }
                }
            }
        }
    }
    else {
        for (int i=-1; i<1; i++) {
            for (int j=0; j<4; j++) {
                for (int k=0; k<5; k++) {
                    if (i==toad.truePattern1[k][patternX] and j==toad.truePattern1[k][patternY]) {
                        if(inBoundsCheck(x,(-1*i),xMax) and inBoundsCheck(y,j,yMax)) {
                            if (world[x+(-1)*i][y+j] == true){correctCells++;}
                        }
                    }
                }
            }
        }
    }*/
    bool found = false;
    int meshX;
    int meshY;
    int patternFinal1[5][2] = {{1,0},{2,0},{1,-1},{2,-1}, {3,-1}};
    int patternFinal2[5][2] = {{0,1},{0,2},{1,1},{1,2}, {1,3}};
    int patternFinal3[5][2] = {{1,0},{2,0},{1,1},{2,1}, {3,1}};
    int patternFinal4[5][2] = {{0,1},{0,2},{-1,1},{-1,2}, {-1,3}};

    if (found == false) {
        for (int k = 0; k<5; k++) {
            if(inBoundsCheck(x,patternFinal1[k][0],xMax)and inBoundsCheck(y,patternFinal1[k][1],yMax)) {
                if (world[x+patternFinal1[k][0]][y+patternFinal1[k][1]]==true){correctCells++;}
            }

        }
        if (correctCells == 6) {
            found=true;
            meshX = x -2;
            meshY = y - 4;
            for (int i = 0; i<8; i++) {
                for (int j = 0; j<8; j++) {
                    if(inBoundsCheck(meshX,i,xMax)and inBoundsCheck(meshY,j,yMax)) {
                        if (world[meshX+i][meshY+j]==true){aliveCells++;}
                    }
                }
            }



        }
        else{correctCells = 1;}
    }
    if (found == false) {
        for (int k = 0; k<5; k++) {
            if(inBoundsCheck(x,patternFinal2[k][0],xMax)and inBoundsCheck(y,patternFinal2[k][1],yMax)) {
                if (world[x+patternFinal2[k][0]][y+patternFinal2[k][1]]==true){correctCells++;}
            }

        }
        if (correctCells == 6) {
            found=true;
            meshX = x -3;
            meshY = y - 2;
            for (int i = 0; i<8; i++) {
                for (int j = 0; j<8; j++) {
                    if(inBoundsCheck(meshX,i,xMax)and inBoundsCheck(meshY,j,yMax)) {
                        if (world[meshX+i][meshY+j]==true){aliveCells++;}
                    }
                }
            }
        }
        else{correctCells = 1;}
    }
    if (found == false) {
        for (int k = 0; k<5; k++) {
            if(inBoundsCheck(x,patternFinal3[k][0],xMax)and inBoundsCheck(y,patternFinal3[k][1],yMax)) {
                if (world[x+patternFinal3[k][0]][y+patternFinal3[k][1]]==true){correctCells++;}
            }

        }
        if (correctCells == 6) {
            found=true;
            meshX = x -2;
            meshY = y - 3;
            for (int i = 0; i<8; i++) {
                for (int j = 0; j<8; j++) {
                    if(inBoundsCheck(meshX,i,xMax)and inBoundsCheck(meshY,j,yMax)) {
                        if (world[meshX+i][meshY+j]==true){aliveCells++;}
                    }
                }
            }
        }
        else{correctCells = 1;}
    }
    if (found == false) {
        for (int k = 0; k<5; k++) {
            if(inBoundsCheck(x,patternFinal4[k][0],xMax)and inBoundsCheck(y,patternFinal4[k][1],yMax)) {
                if (world[x+patternFinal4[k][0]][y+patternFinal4[k][1]]==true){correctCells++;}
            }

        }
        if (correctCells == 6) {
            found=true;
            meshX = x -4;
            meshY = y - 2;
            for (int i = 0; i<8; i++) {
                for (int j = 0; j<8; j++) {
                    if(inBoundsCheck(meshX,i,xMax)and inBoundsCheck(meshY,j,yMax)) {
                        if (world[meshX+i][meshY+j]==true){aliveCells++;}
                    }
                }
            }
        }
        else{correctCells = 1;}
    }





    /*
    int adjustors[4][2]={{-1,-1},{0,-1},{-1,0},{1,1}};
    int truePattern1[5][2] = { {1,0}, {2, 0}, {1, -1}, {2, -1}, {3,-1} };
    for (int k=0; k<4; k++) {
        for (int l=0; l<5; l++) {
            if(inBoundsCheck(x,(adjustors[k][0]*truePattern1[l][0]),xMax) and inBoundsCheck(y,(adjustors[k][1]*truePattern1[l][1]),yMax)) {
                if (world[x+(adjustors[k][0]*truePattern1[l][0])][y+(adjustors[k][1]*truePattern1[l][1])] == true) {correctCells++;}
            }
        }
        if (correctCells == 6){break;}
        else {correctCells = 1;}
    }
    for (int k=0; k<4; k++) {
        for (int l=0; l<5; l++) {
            if(inBoundsCheck(x,(adjustors[k][1]*truePattern1[l][1]),xMax) and inBoundsCheck(y,(adjustors[k][0]*truePattern1[l][0]),yMax)) {
                if (world[x+(adjustors[k][1]*truePattern1[l][1])][y+(adjustors[k][0]*truePattern1[l][0])] == true) {correctCells++;}
            }
        }
        if (correctCells == 6){break;}
        else {correctCells = 1;}
    }




    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (patternX ==1) {
                if(inBoundsCheck(x,toad.patternCheckAreaL[i],xMax) and inBoundsCheck(y,toad.patternCheckAreaW[j],yMax)) {
                    if (world[x+toad.patternCheckAreaL[i]][y+toad.patternCheckAreaW[j]] == true) {aliveCells++;}
                }
            } else {
                if(inBoundsCheck(x,toad.patternCheckAreaW[i],xMax) and inBoundsCheck(y,toad.patternCheckAreaL[j],yMax)) {
                    if (world[x+toad.patternCheckAreaW[i]][y+toad.patternCheckAreaL[j]] == true) {aliveCells++;}
                }
            }
        }
    }*/
    if (correctCells == 6 and aliveCells == correctCells) {
        cout<<"maybe found"<<"\n";

        if (patternMatchData.firstFound == true and iteration == patternMatchData.fI) {
            cout <<"found sure"<<"\n";
            return true;
        }
        if (patternMatchData.firstFound == true and iteration != patternMatchData.fI) {return false;}
        else {
            patternMatchData.firstFound = true;
            patternMatchData.fX = x;
            patternMatchData.fY = y;
            patternMatchData.fI = iteration + toad.sequenceTotal;
            patternMatchData.orientation = orientation;
            return false;
        }

    }

    return false;
}

bool gliderSearch(bool** world, int x, int y, int xMax, int yMax, int iteration) {
    return false;
}

bool lwssSearch(bool** world, int x, int y, int xMax, int yMax, int iteration) {
    return false;
}



bool patternMatching::patternSwitch (int searchVariable, bool** world, int xMax, int yMax, int x, int y, int iteration) {
    bool searchResult = false;
    switch (searchVariable) {
        case 1:
            searchResult = blockSearch(world, x, y, xMax, yMax, iteration);
        break;
        case 2:
            if (beehiveSearch(world, x, y, xMax, yMax, iteration, 0) or beehiveSearch(world, x, y, xMax, yMax, iteration, 1)) {
                searchResult = true;
            }
        break;
        case 3:
            if (blinkerSearch(world, x, y, xMax, yMax, iteration, 0) or blinkerSearch(world, x, y, xMax, yMax, iteration, 1)) {
                searchResult = true;
            }
        break;
        case 4:
            if (toadSearch(world, x, y, xMax, yMax, iteration, 0) or toadSearch(world, x, y, xMax, yMax, iteration, 1)) {
                searchResult = true;
            }
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


