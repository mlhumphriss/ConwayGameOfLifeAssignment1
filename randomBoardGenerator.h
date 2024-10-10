#ifndef RANDOMBOARDGENERATOR_H
#define RANDOMBOARDGENERATOR_H



class randomBoardGenerator {

    void assignLife(bool** world1, bool** world2, int x, int y);

    int createWorld(int xD, int yD, int lS);

    int inputSeedVariables();
};



#endif //RANDOMBOARDGENERATOR_H
