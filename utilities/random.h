#ifndef RANDOM_H
#define RANDOM_H

#include <random>

class Random {
    static std::mt19937 rng;
    static bool initialized;

    static void init();

   public:
    // Inclusive of both min and max
    static int randint(int min, int max);
    static float randfloat(float min, float max);
};

#endif  // RANDOM_H
