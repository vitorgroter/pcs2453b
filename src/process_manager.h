#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include <list>

class Job;
class Processor;
class Scheduler;

class ProcessManager {
public:
	ProcessManager(Scheduler * s, Processor * p);
	void addJob(Job * job);

	int multiprogramming;

private:
	Scheduler * scheduler;
	Processor * processor;

	std::list <Job *> processingJobs;
	std::list <Job *> waitingJobs;

	double timeSlice;
};

#endif // PROCESS_MANAGER_H
