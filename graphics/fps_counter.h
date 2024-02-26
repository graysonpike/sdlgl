#ifndef SDLGL_FPS_COUNTER_H
#define SDLGL_FPS_COUNTER_H

#define SDLGL_NUM_FRAMES_SAMPLED (10)
// Interval in seconds before updating FPS calculation
#define SDLGL_UPDATE_DELAY (0.25f)

class FPSCounter {
    float frame_times[NUM_FRAMES_SAMPLED];
    int frame_counter;
    float update_timer;
    float fps;

    float get_average();

   public:
    FPSCounter();
    void count(float delta);
    float get_fps() const;
};

#endif