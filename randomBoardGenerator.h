#ifndef RANDOMBOARDGENERATOR_H
#define RANDOMBOARDGENERATOR_H



class boardGenerator {
public:
    int inputSeedVariables();
    int inputSeedFile();
    bool** world1Pointer;
    bool** world2Pointer;
    int seed;
    int xDimension;
    int yDimension;
    int startLife;
    void assignLife(bool** world1, bool** world2, int x, int y, int seed);
    void resetWorld(bool**world, int x,int y);

private:

    int createWorld(int xD, int yD, int lS, int s);
};



#endif //RANDOMBOARDGENERATOR_H
