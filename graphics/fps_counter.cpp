#include "fps_counter.h"

// PRIVATE HELPER FUNCTIONS

// Recalculates the average FPS over the last NUM_FRAMES_SAMPLED frames
float FPSCounter::get_average() {

    float sum = 0;
    for(int i = 0; i < NUM_FRAMES_SAMPLED; i++) {
        sum += frame_times[i];
    }
    return 1 / (sum / NUM_FRAMES_SAMPLED);

}

// PUBLIC FUNCTIONS

FPSCounter::FPSCounter() {

    frame_counter = 0;
    update_timer = 0;
    fps = 0;

}

// Records the delta time for a frame (in seconds)
// Should be called by Graphics::present_renderer()
void FPSCounter::count(float delta) {

    frame_times[frame_counter] = delta;
    frame_counter = (frame_counter + 1) % NUM_FRAMES_SAMPLED;
    update_timer += delta;
    if(update_timer > UPDATE_DELAY) {
        update_timer = 0;
        fps = get_average();
    }

}

float FPSCounter::get_fps() {
    return fps;
}