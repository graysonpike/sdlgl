#include <utility>
#include <math.h>

#include "./math.h"


std::pair<int, int> Math::rotate_vector(int magnitude, float angle) {

    int x = magnitude * sin(angle);
    int y = -magnitude * cos(angle);
    return std::pair<int, int>(x, y);
    
}


std::pair<float, float> Math::rotate_about_point(std::pair<float, float> center, std::pair<float, float> moved_point, float angle) {
        
    // Normalize to origin before rotation
    moved_point.first -= center.first;
    moved_point.second -= center.second;

    // Rotate
    std::pair<float, float> new_point;
    new_point.first = (moved_point.first * cos(angle)) - (moved_point.second * sin(angle));
    new_point.second = (moved_point.second * cos(angle)) + (moved_point.first * sin(angle));

    // Denormalize after rotation
    new_point.first += center.first;
    new_point.second += center.second;

    return new_point;

}
