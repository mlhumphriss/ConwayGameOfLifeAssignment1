#include "patternMatching.h"
using namespace std;

bool patternMatching::inBoundsCheck(int a, int mod, int max) {
    if((a+mod >= 0)or(a+mod < max)){return true;}
    return false;
}
