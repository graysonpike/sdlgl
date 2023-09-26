#include "random.h"

bool Random::initialized = false;
std::mt19937 Random::rng;

void Random::init() {
    std::random_device rd;
    rng.seed(rd());
}

int Random::randint(int min, int max) {
    if (!initialized) {
        init();
        initialized = true;
    }
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

float Random::randfloat(float min, float max) {
    if (!initialized) {
        init();
        initialized = true;
    }
    std::uniform_real_distribution<float> dist(min, max);
    return dist(rng);
}
