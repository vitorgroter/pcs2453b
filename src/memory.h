#ifndef MEMORY_H
#define MEMORY_H

#include "scheduler.h"

class Memory {
public:
	Memory(Scheduler * s);

	int getSize();

private:
	Scheduler * scheduler;
	int size;
};

#endif // MEMORY_H
