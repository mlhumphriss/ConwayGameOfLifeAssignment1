#include <iostream>
#include "randomBoardGenerator.h"
#include <fstream>
#include "patternMatching.h"


using namespace std;

int writeFile(int seed, int xSize, int ySize, int startLife) {
    cout<< "Name to save file as in format file.txt: "<<"\n";
    string name;
    cin >> name;
    ofstream saveFile;
    saveFile.open(name.c_str());
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

//Template used to see if alive cells are greater than max for that world size
template <typename T>
class ERNAliveComparison {
private:
    T ernMaxAlive;
public:
    ERNAliveComparison(T max) {ernMaxAlive = max;}
    T operator >(T cpr){return (ernMaxAlive > cpr ? true : false);}
};


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


int calculateNextFrame(bool** current, bool** next, int xSize, int ySize, bool view) {
    for (int i=0; i< xSize; i++) {
        for (int j=0; j< ySize; j++) {
            next[i][j] = cellState(current,i, j, xSize,ySize);
        }
    }
    if (view) {
        displayBoard(current, xSize, ySize);
    }
    return 0;
}

bool boardIteration(bool** world1, bool** world2, int xSize, int ySize, int iterations, int searchVariable, bool view, int startLife) {
    bool** current;
    bool** next;
    bool searchResult;
    patternMatching pat;
    pat.patternMatchData.searchType = searchVariable;

    for (int i=0;i< iterations; i++) {
        if (i%2 == 0) {
            current = world1;
            next = world2;
        }
        else {
            current = world2;
            next = world1;
        }
        calculateNextFrame(current, next, xSize, ySize, view);
        if (searchVariable != 0) {
            searchResult= pat.patternSort(current,next,xSize,ySize,searchVariable, i);
            if (searchResult == true) {return true;}
        }
    }
    return searchResult;
}

int postRunInterface(int seed, int x, int y, int startLife) {
    int selection;
    cout << "Enter 1 to save seed data to file, 2 to skip."<<"\n";
    cin >> selection;
    switch(selection) {
        case 1:
            writeFile(seed, x, y, startLife);
            break;
        case 2:
            cout << "Seed not saved."<<"\n";
            break;
    }
    return 0;
}



int experimentLooping(boardGenerator gen, int searchType, int ernVariable) {
    gen.inputSeedVariables();

    int initialLife = gen.startLife;
    int lowestERN[3] = {10000, 0, 0};
    ERNAliveComparison<int> max((gen.xDimension*gen.yDimension)/2);
    bool ernTest = false;
    int minSeedRuns = 3000;
    if (ernVariable == 1) {
        ernTest =true;
    }

    int iterations;
    cout<< "Number of iterations of game: "<<"\n";
    cin>> iterations;
    bool patternFound;
    while (patternFound == false) {
        patternFound = boardIteration(gen.world1Pointer, gen.world2Pointer, gen.xDimension, gen.yDimension, iterations, searchType, false, gen.startLife);
        if (patternFound == false) {

            if (ernTest == true and (max > gen.startLife)) {
                gen.startLife++;
            }
            else if (ernTest == true) {
                gen.startLife = initialLife;
                gen.seed++;
            }

            gen.seed++;
            cout << gen.seed<<"\n";
            gen.resetWorld(gen.world1Pointer, gen.xDimension, gen.yDimension, gen.world2Pointer, gen.seed, gen.startLife);
        }

        //else {
            if (ernTest == true and lowestERN[0] > (gen.xDimension+gen.yDimension+gen.startLife)) {
                lowestERN[0]= (gen.xDimension+gen.yDimension+gen.startLife);
                lowestERN[1]= gen.seed;
                lowestERN[2] = gen.startLife;
            }
            if (ernTest == true and gen.seed < minSeedRuns) {
                patternFound = false;
            }
        //}


    }
    int viewSelect;

    if(ernTest == true) {
        cout <<"Lowest ERN is "<<lowestERN[0]<<" found in seed "<< lowestERN[1]<<"\n";
    }
    else {
        cout << "Pattern Found in seed: "<< gen.seed<<"\n";
    }

    cout << "Press 1 to view, 2 to skip viewing: " << "\n";
    cin >> viewSelect;
    switch(viewSelect) {
        case 1:

            if (ernTest == true) {
                gen.resetWorld(gen.world1Pointer, gen.xDimension, gen.yDimension, gen.world2Pointer, lowestERN[1], lowestERN[2]);
            }
            else {
                gen.resetWorld(gen.world1Pointer, gen.xDimension, gen.yDimension, gen.world2Pointer, gen.seed, gen.startLife);
            }
            boardIteration(gen.world1Pointer, gen.world2Pointer, gen.xDimension, gen.yDimension, iterations, 0, true, gen.startLife);
            postRunInterface(gen.seed, gen.xDimension, gen.yDimension, gen.startLife);
            break;
        case 2:

            if (ernTest == true) {
                postRunInterface(lowestERN[1], gen.xDimension, gen.yDimension, lowestERN[2]);
            }
            else {
                postRunInterface(gen.seed, gen.xDimension, gen.yDimension, gen.startLife);
            }
            break;
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

    int ernSearch;
    cout << "Enter 1 for normal search, enter 2 for ERN test"<<"\n";
    cin >> ernSearch;
    if (ernSearch == 2) {
        experimentLooping(gen, searchType, 1);
    }
    else {
        experimentLooping(gen, searchType, 0);
    }


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
    bool view = false;
    int viewCheck;
    switch(boardGenType) {
        case 1:
            gen.inputSeedVariables();
            cout<< "Number of iterations of Game: "<<"\n";
            cin>> iterations;
            cout<< "Would Press 1 to view, 2 to not view: "<<"\n";
            cin>> viewCheck;
            if (viewCheck ==1) {
                view = true;
            }
            boardIteration(gen.world1Pointer, gen.world2Pointer, gen.xDimension, gen.yDimension, iterations, 0, view, gen.startLife);
            postRunInterface(gen.seed,gen.xDimension,gen.yDimension,gen.startLife);
            break;
        case 2:
            gen.inputSeedFile();
            cout<< "Number of iterations of game: "<<"\n";
            cin>> iterations;
            cout<< "Would Press 1 to view, 2 to not view: "<<"\n";
            cin>> viewCheck;
            if (viewCheck ==1) {
                view = true;
            }
            boardIteration(gen.world1Pointer, gen.world2Pointer, gen.xDimension, gen.yDimension, iterations, 0, view, gen.startLife);
            break;
        case 3:
            searchInterface(gen);
            break;
    }
    return 0;
}

int main(){
    interface();
    return 0;
}
