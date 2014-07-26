#ifndef JOB_FINISH_EVENT_H
#define JOB_FINISH_EVENT_H

#include "../event.h"

class Job;
class OperatingSystem;

class JobFinishEvent : public Event {
public:
	JobFinishEvent(Job * job, OperatingSystem * os);
	~JobFinishEvent();
	void execute();

private:
	Job * job;
	OperatingSystem * operatingSystem;
};

#endif //JOB_FINISH_EVENT_H

