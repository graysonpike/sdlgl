#include "noise.h"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <random>

std::array<int, PerlinNoise::repeat* 2> PerlinNoise::permutation = {0};

void PerlinNoise::init() {
    // Note: Could be an issue that we are shuffling entire (512) array
    for (unsigned int i = 0; i < repeat * 2; i++) {
        permutation[i] = i % repeat;
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(permutation.begin(), permutation.end(),
            std::default_random_engine(seed));
}

double PerlinNoise::fade(double x) {
    return x * x * x * (x * (x * 6 - 15) + 10);
}

int PerlinNoise::inc(int x) {
    x++;
    x %= repeat;
    return x;
}

double PerlinNoise::lerp(double a, double b, double x) {
    return a + x * (b - a);
}

double PerlinNoise::gradient(int hash, double x, double y) {
    switch (hash & 3) {
        case 0:
            return x + y;
        case 1:
            return -x + y;
        case 2:
            return x - y;
        case 3:
            return -x - y;
        default:
            return 0;
    }
}

double PerlinNoise::generate(double x, double y) {
    x = std::fmod(x, repeat);
    y = std::fmod(y, repeat);
    int xi = (int)x & 255;
    int yi = (int)y & 255;
    double xf = x - (int)x;
    double yf = y - (int)y;
    double u = fade(xf);
    double v = fade(yf);

    int aa, ab, ba, bb;
    aa = permutation[permutation[xi] + yi];
    ab = permutation[permutation[inc(xi)] + yi];
    ba = permutation[permutation[xi] + inc(yi)];
    bb = permutation[permutation[inc(xi)] + inc(yi)];

    double x1, x2, y1;
    x1 = lerp(gradient(aa, xf, yf), gradient(ab, xf - 1, yf), u);
    x2 = lerp(gradient(ba, xf, yf - 1), gradient(bb, xf - 1, yf - 1), u);
    y1 = lerp(x1, x2, v);

    return (y1 + 1) / 2;  // bind range to [0, 1]
}
