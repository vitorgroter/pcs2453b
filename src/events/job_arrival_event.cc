#include "job_arrival_event.h"
#include "../operating_system.h"

JobArrivalEvent::JobArrivalEvent(OperatingSystem * os, Job * j) : operatingSystem(os), job(j) {

}

JobArrivalEvent::~JobArrivalEvent() {

}

void JobArrivalEvent::execute() {
	operatingSystem->jobArrival(job);
}

