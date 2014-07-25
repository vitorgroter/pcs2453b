#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <map>

class Event {
public:
	virtual void execute() = 0;
	virtual ~Event();
};

class Scheduler {
public:
	Scheduler();
	void scheduleEvent(double delay, Event * event);
	bool empty();
	void executeNextEvent();
	double getTime();

private:
	std::multimap <double, Event *> events;
	double time;
};

#endif // SCHEDULER_H
