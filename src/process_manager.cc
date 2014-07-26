#include "process_manager.h"
#include <iostream>

#include "job.h"
#include "scheduler.h"
#include "events/time_slice_event.h"
#include "events/job_finish_event.h"

ProcessManager::ProcessManager(Scheduler * s, Processor * p, 
							   OperatingSystem * os) :
							   scheduler(s), processor(p),
							   operatingSystem(os) {
	multiprogramming = 100;
	timeSliceDelay = 1.0;
}

void ProcessManager::addJob(Job * job) {
	std::cout << "Job \"" << job->getName() << "\" ";

	if (processingJobs.size() < multiprogramming) {
		std::cout << "added to the multiprogramming list." << std::endl;
		processingJobs.push_back(job);

		if (processingJobs.size() == 1) {

			if (job->getRemainingProcessingTime() > timeSliceDelay) {
				TimeSliceEvent * event = new TimeSliceEvent(this);
				scheduler->scheduleEvent(timeSliceDelay, event);
			}
		}
	}
	else {
		std::cout << "added to the processor waiting list." << std::endl;
		waitingJobs.push_back(job);
	}
}

void ProcessManager::timeSlice() {
	std::cout << "Switching from job \"";
	std::cout << (*processingJobs.begin())->getName() << "\" ";

	// moves the first job in the queue to the end of the queue
	(*processingJobs.begin())->increaseProcessingTime(timeSliceDelay);
	processingJobs.push_back(*processingJobs.begin());
	processingJobs.erase(processingJobs.begin());

	std::cout << "to job \"";
	std::cout << (*processingJobs.begin())->getName() << "\"." << std::endl;

	// starts processing on the (new) first job of the queue
	if ((*processingJobs.begin())->getRemainingProcessingTime() > timeSliceDelay) {
		TimeSliceEvent * event = new TimeSliceEvent(this);
		scheduler->scheduleEvent(timeSliceDelay, event);
	}
	else {
		JobFinishEvent * event = new JobFinishEvent((*processingJobs.begin()), operatingSystem);
		scheduler->scheduleEvent((*processingJobs.begin())->getRemainingProcessingTime(), event);
	}
}

void ProcessManager::jobFinish(Job * job) {
	if (job != *processingJobs.begin())
		throw std::runtime_error("Finished job isn't the job that was being processed.");

	// removes the first job from the multiprogramming queue,
	// since it has finished
	processingJobs.erase(processingJobs.begin());

	// starts processing on the (new) first job of the queue
	if (processingJobs.size() >= 1) {
		if ((*processingJobs.begin())->getRemainingProcessingTime() > timeSliceDelay) {
			TimeSliceEvent * event = new TimeSliceEvent(this);
			scheduler->scheduleEvent(timeSliceDelay, event);
		}
		else {
			JobFinishEvent * event = new JobFinishEvent((*processingJobs.begin()), operatingSystem);
			scheduler->scheduleEvent((*processingJobs.begin())->getRemainingProcessingTime(), event);
		}
	}

}

