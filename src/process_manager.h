#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include "scheduler.h"
#include "processor.h"

class ProcessManager {
public:
	ProcessManager(Scheduler * s, Processor * p);

private:
	Scheduler * scheduler;
	Processor * processor;
};

#endif // PROCESS_MANAGER_H