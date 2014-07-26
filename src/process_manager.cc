#include "process_manager.h"

#include <iostream>

ProcessManager::ProcessManager(Scheduler * s, Processor * p) : scheduler(s), processor(p) {

}

void ProcessManager::addJob(Job * job) {
	std::cout << "oh shit" << std::endl;
	jobs.push_back(job);
}

