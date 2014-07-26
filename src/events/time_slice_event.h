#ifndef TIME_SLICE_EVENT_H
#define TIME_SLICE_EVENT_H

#include "../event.h"

class ProcessManager;

class TimeSliceEvent : public Event {
public:
	TimeSliceEvent(ProcessManager * processManager);
	~TimeSliceEvent();
	void execute();

private:
	ProcessManager * processManager;
};

#endif // TIME_SLICE_EVENT_H

