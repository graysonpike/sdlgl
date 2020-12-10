#ifndef TIMER_H
#define TIMER_H


class Timer {

    unsigned int start_time;
    unsigned int duration;
    bool active = false;
    void update();

public:

    Timer();
    Timer(float duration);
    void reset();
    bool is_done();
    bool is_active();
    float remaining(); // fraction of time remaining
    float get_duration();

};

#endif