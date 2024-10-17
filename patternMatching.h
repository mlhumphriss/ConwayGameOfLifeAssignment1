#ifndef PATTERNMATCHING_H
#define PATTERNMATCHING_H



class patternMatching {
public:
    bool patternSort(bool** current,bool** next,int xSize,int ySize,int startLife,int searchVariable);

    int originBlock[2];

private:
    static bool inBoundsCheck(int a, int mod, int max);
};



#endif //PATTERNMATCHING_H

