#ifndef PATTERN_H
#define PATTERN_H



class Pattern {
public:
    int sequenceTotal;
    int sequence;
};

class Block : public Pattern {
public:
    int sequenceTotal = 2;
    int sequence;
    int truePattern[3][2] = { {1, 0}, {0, 1}, {1, 1} };
    int patternCheckArea[6]= {-2,-1,0,1,2,3};

};

class Beehive : public Pattern {
public:
    int sequenceTotal = 2;
    int sequence;
    int truePattern[5][2] = { {1, 1}, {-1, 1}, {1, 2}, {-1, 2}, {0,3} };
    int patternCheckAreaL[8]= {-2,-1,0,1,2,3,4,5};
    int patternCheckAreaW[7]= {-3,-2,-1,0,1,2,3};
};

class Blinker : public Pattern {
public:
    int sequenceTotal = 2;
    int sequence;
    int truePattern[2][2] = {{0,-1},{0,1}};
    int patternCheckAreaL[7]= {-3,-2,-1,0,1,2,3};
    int patternCheckAreaW[5]= {-2,-1,0,1,2};
};

class Toad : public Pattern {
public:
    int sequenceTotal = 2;
    int sequence;
    int truePattern1[5][2] = { {0,1}, {0, 2}, {-1, 1}, {-1, 2}, {-1,3} };
    //int truePattern2[5][2] = { {1, 0}, {-1, 1}, {0, 3}, {1, 3}, {2, 2} };
    int patternCheckAreaL[8]= {-2,-1, 0, 1,2,3,4,5};
    int patternCheckAreaW[8]= {-4,-3,-2,-1,0,1,2,3};
};

class Glider : public Pattern {
public:
    int sequenceTotal = 4;
    int sequence;
    int truePattern1[4][2] = { {0, 1}, {-1, 2}, {-1, 0}, {-2, 0} };
    int truePattern2[4][2] = { {0, 1}, {1, -1}, {3, 0}, {3, 1}};
};

class LWSS : public Pattern {
public:
    int sequenceTotal;
    int sequence;
};

#endif //PATTERN_H
