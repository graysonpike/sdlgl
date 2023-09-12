#ifndef NOISE_H
#define NOISE_H

#include <array>

class PerlinNoise {
    static const int repeat = 256;
    static std::array<int, repeat * 2> permutation;
    static double fade(double x);
    static int inc(int x);
    static double lerp(double a, double b, double x);
    static double gradient(int hash, double x, double y);

   public:
    static void init();
    static double generate(double x, double y);
};

#endif