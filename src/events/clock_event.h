#ifndef CLOCK_EVENT_H
#define CLOCK_EVENT_H

#include "../event.h"

class ClockEvent : public Event {
public:
	ClockEvent();
	~ClockEvent();
	void execute();

private:
};

#endif //CLOCK_EVENT_H

