#include <iostream>
#include <fstream>
#include <queue>

#include "job.h"
#include "common.h"
#include "operating_system.h"
#include "information_manager.h"
#include "file.h"

OperatingSystem::OperatingSystem(Scheduler * s) : scheduler(s) {
	processManager = new ProcessManager(scheduler, this);
	memoryManager = new MemoryManager(scheduler, this);
	informationManager = new InformationManager(scheduler, "filesystem.txt");
}

void OperatingSystem::jobArrival(Job * j) {
	std::cout << "Job \"" << j->getName();
	std::cout << " just arrived to the system." << std::endl;

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

void OperatingSystem::jobFinish(Job * j) {
	std::cout << "Job \"" << j->getName();
	std::cout << "\" finished." << std::endl;

	// releases all the job segments
	std::queue <Tree <Segment *> *> segmentNodes;
	segmentNodes.push(j->getSegmentTree());
	while (!segmentNodes.empty()) {
		Tree <Segment *> * segmentNode = segmentNodes.front();
		segmentNodes.pop();
		memoryManager->releaseSegment(segmentNode->data);

		for (auto child : segmentNode->children) {
			segmentNodes.push(child);
		}
	}

	processManager->jobFinish(j);
}

File * OperatingSystem::getFile(std::string name) {
	return informationManager->getFile(name);
}

void OperatingSystem::processorRequest(Job * j) {
	processManager->addJob(j);
}

