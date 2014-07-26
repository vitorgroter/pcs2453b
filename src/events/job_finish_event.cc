#include "job_finish_event.h"
#include "../operating_system.h"

JobFinishEvent::JobFinishEvent(Job * job, OperatingSystem * os) :
							   job(job),  operatingSystem(os) {

}

JobFinishEvent::~JobFinishEvent() {

}

void JobFinishEvent::execute() {
	operatingSystem->jobFinish(job);
}

