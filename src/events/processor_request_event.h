#ifndef PROCESSOR_REQUEST_EVENT_H
#define PROCESSOR_REQUEST EVENT_H

#include "../event.h"

class Job;
class OperatingSystem;

class ProcessorRequestEvent : public Event {
public:
	ProcessorRequestEvent(Job * job, OperatingSystem * operatingSystem);
	~ProcessorRequestEvent();
	void execute();
private:
	Job * job;
	OperatingSystem * operatingSystem;
};

#endif // PROCESSOR_REQUEST_EVENT_H

