#include <fstream>
#include <queue>

#include "job.h"
#include "common.h"
#include "operating_system.h"
#include "information_manager.h"
#include "file.h"

OperatingSystem::OperatingSystem(Scheduler * s, Processor * p, Memory * m, Disk * d) : scheduler(s) {
	processManager = new ProcessManager(scheduler, p);
	memoryManager = new MemoryManager(scheduler, m, this);
	informationManager = new InformationManager(scheduler, d, "filesystem.txt");
}

void OperatingSystem::jobArrival(Job * j) {
	std::queue <Tree <std::string> *> nameNodes;
	std::queue <Tree <Segment *> *> segmentNodes;

	nameNodes.push(j->getSegmentNameTree());
	segmentNodes.push(j->getSegmentTree());

	Tree <std::string> * nameNode;
	Tree <Segment *> * segmentNode;

	while (!nameNodes.empty()) {
		nameNode = nameNodes.front();
		nameNodes.pop();
		segmentNode = segmentNodes.front();
		segmentNodes.pop();

		// allocates memory for every segment
		File * file = informationManager->getFile(nameNode->data);
		memoryManager->loadSegment(nameNode->data, file->getSize(), &(segmentNode->data), j);

		for (auto child : nameNode->children) {
			nameNodes.push(child);
		}
		for (auto child : segmentNode->children) {
			segmentNodes.push(child);
		}
	}
	
}

File * OperatingSystem::getFile(std::string name) {
	return informationManager->getFile(name);
}

void OperatingSystem::processorRequest(Job * j) {
	processManager->addJob(j);
}

