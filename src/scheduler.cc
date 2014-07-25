#include <iostream>
#include "scheduler.h"

Scheduler::Scheduler() {
	time = 0.0;
}

void Scheduler::scheduleEvent(double delay, Event * event) {
	events.insert(std::pair <double, Event *> (time + delay, event));
}

bool Scheduler::empty() {
	return events.empty();
}

void Scheduler::executeNextEvent() {
	time = events.begin()->first;
	Event * event = events.begin()->second;

	std::cout << time;
	std::cout << " ";
	std::cout << std::endl;
	event->execute();

	events.erase(events.begin());
	delete event;
}

double Scheduler::getTime() {
	return time;
}

Event::~Event() {

}

