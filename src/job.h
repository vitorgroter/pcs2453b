#ifndef JOB_H
#define JOB_H

#include "operating_system.h"
#include "scheduler.h"
#include "common.h"

class Job {
public:
	Job(const char filename[]);
	
	inline double getArrivalTime() {
		return arrivalTime;
	}

	inline StringNode * getSegmentTree() {
		return segmentTree;
	}

private:
	double arrivalTime;
	int totalInputs;
	int totalOutputs;
	int totalFileAccesses;
	double totalProcessingTime;
	StringNode * segmentTree;
};

class JobArrivalEvent : public Event {
public:
	JobArrivalEvent(OperatingSystem * os, Job * j);
	~JobArrivalEvent();
	void execute();

private:
	OperatingSystem * operatingSystem;
	Job * job;
};

#endif // JOB_H

