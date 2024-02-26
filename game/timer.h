#ifndef SDLGL_TIMER_H
#define SDLGL_TIMER_H

class Timer {
    unsigned int start_time;
    unsigned int duration;  // in milliseconds
    bool active = false;
    void update();

   public:
    Timer();
    Timer(float duration);
    void reset();
    void set_duration(float duration);
    bool is_done();
    bool is_active();
    float remaining();  // Fraction of time remaining
    float elapsed();    // Fraction of time elapsed
    float duration_remaining();
    float duration_elapsed();
    float get_duration();
};

#endif