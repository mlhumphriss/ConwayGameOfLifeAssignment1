#ifndef RANDOMBOARDGENERATOR_H
#define RANDOMBOARDGENERATOR_H



class randomBoardGenerator {
public:
    int inputSeedVariables();
    bool** currentWorld;
    bool** nextWorld;
    bool** seed;
    int xDimension;
    int yDimension;

private:
    void assignLife(bool** world1, bool** world2, bool** seedWorld, int x, int y);

    int createWorld(int xD, int yD, int lS);


    int startLife;
};



#endif //RANDOMBOARDGENERATOR_H
