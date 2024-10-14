#include <iostream>
#include "randomBoardGenerator.h"
#include <fstream>

using namespace std;

int writeFile(bool** seed, int xSize, int ySize) {
    cout<< "Name to save file as in format file.txt: "<<"\n";
    string name;
    cin >> name;
    ofstream saveFile(name);
    if (saveFile.is_open()) {
        cerr << "Failed to open file for writing.\n";
        return 1;
    }
    saveFile<< xSize<< " "<< ySize<<" ";
    for (int i =0; i<xSize; i++) {
        for (int j =0; j<ySize; i++) {
            saveFile<< seed[i][j] << " ";
        }
    }
    saveFile.close();
    return 0;

}
int inputSeed() {
    string filename;
    cout << "Input filename in form file.txt: "<<"\n";
    cin >> filename;
    ifstream infile(filename);
    int xSize;
    int ySize;
    infile>>xSize;
    infile>>ySize;
    bool** loadedWorld = new bool*[xSize];
    for (int i = 0; i < xSize; i++) {
        loadedWorld[i] = new bool[ySize];
        for (int j = 0; j <ySize; j++) {
            infile>>loadedWorld[i][j];
        }
    }
    return 0;

}



bool cellState(bool** current, int x, int y, int maxX, int maxY) {
    int neighbourCount = 0;
    if (x>0) {
        if (y>0) {
            if (current[x-1][y-1] == true) {
                neighbourCount++;
            }
        }
        if (current[x-1][y] == true) {
            neighbourCount++;
        }
        if (y<maxY-1) {
            if (current[x-1][y+1] == true) {
                neighbourCount++;
            }
        }
    }
    if (x<maxX-1) {
        if (y>0) {
            if (current[x+1][y-1] == true) {
                neighbourCount++;
            }
        }
        if (current[x+1][y] == true) {
            neighbourCount++;
        }
        if (y<maxY-1) {
            if (current[x+1][y+1] == true) {
                neighbourCount++;
            }
        }
    }
    if (y>0) {
        if (current[x][y-1] == true) {
            neighbourCount++;
        }
    }
    if (y<maxY-1) {
        if (current[x][y+1] == true) {
            neighbourCount++;
        }
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
                cout << ".O";
            }
            else {
                cout << ". ";
            }
        }
        cout <<"."<< "\n";
    }
    cout<<"\n";
}


int calculateNextFrame(bool** current, bool** next, int xSize, int ySize) {
    for (int i=0; i< xSize; i++) {
        for (int j=0; j< ySize; j++) {
            next[i][j] = cellState(current,i, j, xSize,ySize);
        }
    }
    displayBoard(current, xSize, ySize);
    displayBoard(next, xSize, ySize);
    return 0;
}


//hate my life

int main()
{   //temp to test other processes
    randomBoardGenerator gen;
    gen.inputSeedVariables();
    calculateNextFrame(gen.world1Pointer, gen.world2Pointer, gen.xDimension, gen.yDimension);

    return 0;
}
