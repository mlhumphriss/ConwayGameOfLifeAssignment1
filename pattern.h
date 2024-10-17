#ifndef PATTERN_H
#define PATTERN_H



class Pattern {
public:
    int truePattern[][];
};

class Block : public Pattern {
public:
    int truePattern[3][2] = { {1, 0}, {0, 1}, {1, 1} };
};

class Beehive : public Pattern {
public:
    int truePattern[5][2] = { {1, 1}, {1, -1}, {2, 1}, {2, -1}, {3,0} };
};

class Blinker : public Pattern {
public:
    int truePattern[2][2] = {{1,0},{-1,0}};
};

class Toad : public Pattern {
public:
    int truePattern1[5][2] = { {1, 0}, {2, 0}, {1, 1}, {2, 1}, {3,1} };
    int truePattern2[5][2] = { {0, 1}, {1, -1}, {3, 0}, {3, 1}, {2, 2} };
};

class Glider : public Pattern {

};

class LWSS : public Pattern {

};

#endif //PATTERN_H
