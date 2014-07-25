#include <fstream>
#include <queue>

#include "job.h"
#include "common.h"
#include "operating_system.h"

OperatingSystem::OperatingSystem(Scheduler * s, Clock * c, Processor * p, Memory * m, Disk * d) : scheduler(s) {
	processManager = new ProcessManager(scheduler, p);
	memoryManager = new MemoryManager(scheduler, this, m);
	informationManager = new InformationManager(scheduler, d, "filesystem.txt");
}

void OperatingSystem::jobArrival(Job * j) {
	std::queue <StringNode *> nodes;
	nodes.push(j->getSegmentTree());
	StringNode * node;

	while (!nodes.empty()) {
		node = nodes.front();
		nodes.pop();

		memoryManager->loadSegment(node->str.c_str());

		for (auto child : node->children) {
			nodes.push(child);
		}
	}
	
}

File * OperatingSystem::getFile(std::string name) {
	return informationManager->getFile(name);
}

