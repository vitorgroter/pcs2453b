#include <fstream>
#include <queue>

#include "job.h"
#include "common.h"
#include "operating_system.h"
#include "information_manager.h"
#include "file.h"

OperatingSystem::OperatingSystem(Scheduler * s, Clock * c, Processor * p, Memory * m, Disk * d) : scheduler(s) {
	processManager = new ProcessManager(scheduler, p);
	memoryManager = new MemoryManager(scheduler, m);
	informationManager = new InformationManager(scheduler, d, "filesystem.txt");
}

void OperatingSystem::jobArrival(Job * j) {
	std::queue <Tree <std::string> *> nodes;
	nodes.push(j->getSegmentNameTree());
	Tree <std::string> * node;

	while (!nodes.empty()) {
		node = nodes.front();
		nodes.pop();

		// allocates memory for every segment
		File * file = informationManager->getFile(node->data);
		memoryManager->loadSegment(node->data, file->getSize());

		for (auto child : node->children) {
			nodes.push(child);
		}
	}
	
}

File * OperatingSystem::getFile(std::string name) {
	return informationManager->getFile(name);
}

