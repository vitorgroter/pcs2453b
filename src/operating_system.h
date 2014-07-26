#ifndef OPERATING_SYSTEM_H
#define OPERATING_SYSTEM_H

#include "scheduler.h"
#include "processor.h"
#include "memory.h"
#include "disk.h"
#include "process_manager.h"
#include "memory_manager.h"
#include "information_manager.h"

class Job;

class OperatingSystem {
public:
	OperatingSystem(Scheduler * s, Processor * p, Memory * m, Disk * d);
	File * getFile(std::string name);

	void jobArrival(Job * j);
	void jobFinish(Job * j);
	void processorRequest(Job * j);
private:
	Scheduler * scheduler;

	ProcessManager * processManager;
	MemoryManager * memoryManager;
	InformationManager * informationManager;
};

#endif // OPERATING_SYSTEM_H
