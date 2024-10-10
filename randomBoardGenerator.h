#ifndef RANDOMBOARDGENERATOR_H
#define RANDOMBOARDGENERATOR_H



class randomBoardGenerator {
public:
    int inputSeedVariables();
    bool** currentWorld;
    bool** nextWorld;

private:
    void assignLife(bool** world1, bool** world2, int x, int y);

    int createWorld(int xD, int yD, int lS);

    int xDimension;
    int yDimension;
    int startLife;
};



#endif //RANDOMBOARDGENERATOR_H
