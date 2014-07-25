#ifndef JOB_ARRIVAL_EVENT_H
#define JOB_ARRIVAL_EVENT_H

#include "../scheduler.h"

class Job;
class OperatingSystem;

class JobArrivalEvent : public Event {
public:
	JobArrivalEvent(OperatingSystem * os, Job * j);
	~JobArrivalEvent();
	void execute();

private:
	OperatingSystem * operatingSystem;
	Job * job;
};

#endif //JOB_ARRIVAL_EVENT_H

