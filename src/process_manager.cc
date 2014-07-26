#include "process_manager.h"

#include <iostream>

ProcessManager::ProcessManager(Scheduler * s, Processor * p) : scheduler(s), processor(p) {
	multiprogramming = 1;
}

void ProcessManager::addJob(Job * job) {
	if (processingJobs.size() < multiprogramming) {
		std::cout << "Job processing" << std::endl;
	}
	else {
		std::cout << "Job waiting" << std::endl;
		waitingJobs.push_back(job);
	}
}

