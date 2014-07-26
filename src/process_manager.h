#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include <list>

class Job;
class OperatingSystem;
class Processor;
class Scheduler;

class ProcessManager {
public:
	ProcessManager(Scheduler * s, Processor * p, OperatingSystem * os);
	void addJob(Job * job);
	void timeSlice();

	int multiprogramming;

	void jobFinish(Job * job);

private:
	Scheduler * scheduler;
	Processor * processor;
	OperatingSystem * operatingSystem;

	std::list <Job *> processingJobs;
	std::list <Job *> waitingJobs;

	double timeSliceDelay;
};

#endif // PROCESS_MANAGER_H
