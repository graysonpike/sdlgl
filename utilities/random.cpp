#include <stdlib.h>
#include <time.h>
#include "random.h"


bool Random::initialized = false;


void Random::init() {
    srand((unsigned)time(NULL));
}


int Random::randint(int min, int max) {

    if (!initialized) {
        init();
        initialized = true;
    }
    return rand() % (max - min + 1) + min;
    
}
