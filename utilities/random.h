#ifndef RANDOM_H
#define RANDOM_H


class Random {

    static void init();
    static bool initialized;

public:

    // Inclusive of both min and max
    static int randint(int min, int max);

};

#endif