#include "track.h"

Track::Track() {}

Track::Track(const std::shared_ptr<Mix_Music>& track) { this->track = track; }