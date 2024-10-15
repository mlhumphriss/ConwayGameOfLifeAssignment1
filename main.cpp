#include <iostream>
#include "randomBoardGenerator.h"
#include <fstream>

using namespace std;

int writeFile(int seed, int xSize, int ySize, int startLife) {
    cout<< "Name to save file as in format file.txt: "<<"\n";
    string name;
    cin >> name;
    ofstream saveFile(name);
    if (saveFile.is_open()) {
        cerr << "Failed to open file for writing.\n";
        return 1;
    }
    saveFile<< xSize<< " "<< ySize<<" "<<seed<<" "<<startLife << "\n";

    saveFile.close();
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
    //displayBoard(current, xSize, ySize);
    return 0;
}

bool boardIteration(bool** world1, bool** world2, int xSize, int ySize, int iterations, int searchVariable) {
    bool** current;
    bool** next;
    for (int i=0;i<iterations;i++) {
        if (i%2 == 0) {
            current = world1;
            next = world2;
        }
        else {
            current = world2;
            next = world1;
        }
        calculateNextFrame(current, next, xSize, ySize);
        if (searchVariable != 0) {
            //search pattern function call
            bool searchResult;
            return searchResult;
        }
    }
    return false;
}

int experimentLooping(boardGenerator gen, int searchType) {
    gen.inputSeedVariables();
    int iterations;
    cout<< "Number of iterations of game: "<<"\n";
    cin>> iterations;
    bool patternFound;
    while (patternFound == false) {
        patternFound = boardIteration(gen.world1Pointer, gen.world2Pointer, gen.xDimension, gen.yDimension, iterations, searchType);
        displayBoard(gen.world1Pointer, gen.xDimension, gen.yDimension);
        if (patternFound == false) {
            gen.seed++;
            gen.resetWorld(gen.world1Pointer, gen.xDimension, gen.yDimension);
            for (int k =0; k< gen.startLife; k++) {
                gen.assignLife(gen.world1Pointer, gen.world2Pointer, gen.xDimension, gen.yDimension, gen.seed);
            }
        }
    }
    return 0;
}


int searchInterface(boardGenerator gen){
    int searchType;
    cout << "To Search for Block enter 1"<<"\n";
    cout << "To Search for Beehive enter 2"<<"\n";
    cout << "To Search for Blinker enter 3"<<"\n";
    cout << "To Search for Toad enter 4"<<"\n";
    cout << "To Search for Glider enter 5"<<"\n";
    cout << "To Search for Light Weight SpaceShip enter 6"<<"\n";
    cin >> searchType;
    experimentLooping(gen, searchType);

    return 0;
}

int interface() {
    int boardGenType;
    cout << "To Run with a random seed enter 1"<<"\n";
    cout << "To Load a saved seed enter 2"<<"\n";
    cout << "To Run an experiment search enter 3"<<"\n";
    cin >> boardGenType;
    boardGenerator gen;
    int iterations;

    switch(boardGenType) {
        case 1:
            gen.inputSeedVariables();
            cout<< "Number of iterations of game: "<<"\n";
            cin>> iterations;
            boardIteration(gen.world1Pointer, gen.world2Pointer, gen.xDimension, gen.yDimension, iterations, 0);
            break;
        case 2:
            gen.inputSeedFile();
            cout<< "Number of iterations of game: "<<"\n";
            cin>> iterations;
            boardIteration(gen.world1Pointer, gen.world2Pointer, gen.xDimension, gen.yDimension, iterations, 0);
            break;
        case 3:
            searchInterface(gen);
            break;
    }

    return 0;
}

int main()
{   //temp to test other processes
    /*
    boardGenerator gen;
    gen.inputSeedVariables();
    boardIteration(gen.world1Pointer, gen.world2Pointer, gen.xDimension, gen.yDimension, 50, 0);
    */
    interface();
    return 0;
}
