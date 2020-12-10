#include <utility>
#include <math.h>

#include "./math.h"


std::pair<int, int> Math::rotate_vector(int magnitude, float angle) {

    int x = magnitude * sin(angle);
    int y = -magnitude * cos(angle);
    return std::pair<int, int>(x, y);
    
}