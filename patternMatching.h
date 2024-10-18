#ifndef PATTERNMATCHING_H
#define PATTERNMATCHING_H



class patternMatching {
public:
    bool patternSort(bool** current,bool** next,int xSize,int ySize,int searchVariable, int iteration);

    int originBlock[2];

    struct {int searchType; int fX; int fY; int fI; bool firstFound;} patternMatchData;

    bool blockSearch(bool** world, int x, int y, int xMax, int yMax, int iteration);

private:
    bool inBoundsCheck(int a, int mod, int max);

    bool patternSwitch (int searchVariable, bool** world, int xMax, int yMax, int x, int y, int iteration);
};



#endif //PATTERNMATCHING_H

