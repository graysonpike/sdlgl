#ifndef TIMER_H
#define TIMER_H

class Timer {

	unsigned int start_time;
	unsigned int duration;

public:

	Timer(float duration);
	void reset();
	bool is_done();

};

#endif