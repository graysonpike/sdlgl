#ifndef UTILMATH_H
#define UTILMATH_H

#include <utility>


class Math {

public:
    
    // Rotate a vector starting straight up (0, -magnitude) clockwise.
    // Examples: rotate_vector(1, 0) => (0, -1) 
    //           rotate_vector(1, M_PI/2) => (1, 0) 
    //           rotate_vector(1, M_PI) => (0, 1) 
    static std::pair<int, int> rotate_vector(int magnitude, float angle);

    static std::pair<float, float> rotate_about_point(std::pair<float, float> center, std::pair<float, float> moved_point, float angle);
    
};

#endif