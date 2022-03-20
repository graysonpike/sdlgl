#include <utility>
#include <math.h>

#include "./math.h"


std::pair<int, int> Math::rotate_vector(int magnitude, float angle) {

    int x = magnitude * sin(angle);
    int y = -magnitude * cos(angle);
    return std::pair<int, int>(x, y);
    
}


std::pair<float, float> Math::rotate_vector(float magnitude, float angle) {

    float x = magnitude * sin(angle);
    float y = -magnitude * cos(angle);
    return std::pair<float, float>(x, y);
    
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


float Math::magnitude(std::pair<float, float> vector) {
    return sqrt(vector.first * vector.first + vector.second * vector.second);
}


std::pair<float, float> Math::add_vectors(std::pair<float, float> a, std::pair<float, float> b) {
    return std::pair<float, float>(a.first + b.first, a.second + b.second);
}


std::pair<float, float> Math::scale_vector(std::pair<float, float> v, float factor) {
    return std::pair<float, float>(v.first * factor, v.second * factor);
}


float Math::clamp(float x, float min, float max) {
    if (x < min) {
        return min;
    }
    if (x > max) {
        return max;
    }
    return x;
}
