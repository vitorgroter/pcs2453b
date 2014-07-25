#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "scheduler.h"

class Processor {
public:
	Processor(Scheduler * s);

private:
	Scheduler * scheduler;
};

#endif // PROCESSOR_H