#include "scheduler.h"
#include "operating_system.h"
#include "job.h"
#include "events/job_arrival_event.h"

int main() {
	Scheduler scheduler;
	OperatingSystem os(&scheduler);


	Job j1("job1.txt");
	Job j2("job2.txt");

	JobArrivalEvent * ja1 = new JobArrivalEvent(&os, &j1);
	JobArrivalEvent * ja2 = new JobArrivalEvent(&os, &j2);


	scheduler.scheduleEvent(j1.getArrivalTime(), ja1);
	scheduler.scheduleEvent(j2.getArrivalTime(), ja2);

	while (!scheduler.empty()) {
		scheduler.executeNextEvent();
	}

	return 0;
}

