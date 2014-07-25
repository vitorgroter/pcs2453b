#ifndef CLOCK_H
#define CLOCK_H

#include "scheduler.h"

class Clock {
public:
	Clock(Scheduler * s);

private:
	Scheduler * scheduler;
};

#endif // CLOCK_H

