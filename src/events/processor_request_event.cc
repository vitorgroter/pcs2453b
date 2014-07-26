#include "processor_request_event.h"

#include "../operating_system.h"

ProcessorRequestEvent::ProcessorRequestEvent(Job * job, OperatingSystem * os) :
											 job(job), operatingSystem(os)
{

}

ProcessorRequestEvent::~ProcessorRequestEvent() {
	
}

void ProcessorRequestEvent::execute() {
	operatingSystem->processorRequest(job);
}

