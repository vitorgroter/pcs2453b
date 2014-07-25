#include "scheduler.h"
#include "clock.h"
#include "processor.h"
#include "memory.h"
#include "disk.h"
#include "operating_system.h"
#include "job.h"
#include "events/job_arrival_event.h"

int main() {
	Scheduler scheduler;
	Clock clock(&scheduler);
	Processor cpu(&scheduler);
	Memory mem(&scheduler);
	Disk disk(&scheduler);
	OperatingSystem os(&scheduler, &clock, &cpu, &mem, &disk);


	Job j("job1.txt");
	JobArrivalEvent * ja = new JobArrivalEvent(&os, &j);

	scheduler.scheduleEvent(j.getArrivalTime(), ja);

	while (!scheduler.empty()) {
		scheduler.executeNextEvent();
	}

	return 0;
}

