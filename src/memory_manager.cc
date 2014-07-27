#include "memory_manager.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

#include "common.h"
#include "job.h"
#include "scheduler.h"
#include "segment.h"
#include "events/processor_request_event.h"

MemoryManager::MemoryManager(Scheduler * s, OperatingSystem * os) : 
							 scheduler(s), operatingSystem(os) {
	memorySize = 500000;
	std::cout << "Initial memory table is all free" << std::endl;
	printTable();
	std::cout << std::endl;
}

void MemoryManager::loadSegment(std::string name, int size, Segment ** segment, Job * j) {
	*segment = findLoadedSegment(name);

	// segment is not loaded yet
	if (*segment == nullptr) {
		int position = findContiguousMemory(size);
		if (position != -1) {
			*segment = new Segment(name, position, size);
			segments.push_back(*segment);
			(*segment)->increaseReferenceCount();

			std::cout << "Segment \"" + name + "\" loaded for job \"";
			std::cout << j->getName() << "\"." << std::endl;
			printTable();
			std::cout << std::endl;

			j->increaseTotalLoadedSegments();
		}
		else {
			// to-do: add segment to segment allocation queue
		}
	}

	// segment is already loaded
	else {
		std::cout << "Segment \"" + name + "\" requested by job \"";
		std::cout << j->getName() << "\" is already loaded." << std::endl;
		(*segment)->increaseReferenceCount();
		j->increaseTotalLoadedSegments();
	}

	if (j->areAllSegmentsLoaded()) {
		std::cout << "All segments from job \"" << j->getName();
		std::cout << "\" loaded." << std::endl;

		ProcessorRequestEvent * event = new ProcessorRequestEvent(j, operatingSystem); 
		scheduler->scheduleEvent(0.0, event);
	}
}

void MemoryManager::releaseSegment(Segment * segment) {
	segment->decreaseReferenceCount();

	if (segment->getReferenceCount() == 0) {
		std::cout << "Segment " << segment->getName() << " is not in use by ";
		std::cout << "any job, releasing its memory." << std::endl;
		segments.erase(std::find(segments.begin(), segments.end(), segment));
		delete segment;
		
		printTable();
		std::cout << std::endl;
	}
}

Segment * MemoryManager::findLoadedSegment(std::string name) {
	for (auto segment : segments) {
		if (segment->getName() == name)
			return segment;
	}

	return nullptr;
}

int MemoryManager::findContiguousMemory(int size) {
	std::vector <std::pair <int, int> > occupiedMemory;

	for (auto segment : segments)
		occupiedMemory.push_back(std::make_pair(segment->getPosition(), segment->getPosition() + segment->getSize()));	
	std::sort(occupiedMemory.begin(), occupiedMemory.end());

	// memory is empty
	if (occupiedMemory.size() == 0) {
		// memory is big enough
		if (getMemorySize() >= size)
			return 0;

		// memory isn't big enough
		else
			return -1;
	}

	// it fits in the begging of memory
	if (occupiedMemory.begin()->first >= size)
		return 0;

	for (int i = 0; i < occupiedMemory.size() - 1; i++) {
		// it fits between two segments
		if (occupiedMemory[i + 1].first - occupiedMemory[i].second >= size)
			return occupiedMemory[i].second;
	}

	// it fits in the ending of memory
	if (getMemorySize() - occupiedMemory.back().second >= size)
		return occupiedMemory.back().second;

	return -1;
}

void MemoryManager::printTable() {
	std::vector <std::pair <int, int> > occupiedMemory;

	for (auto segment : segments)
		occupiedMemory.push_back(std::make_pair(segment->getPosition(), segment->getPosition() + segment->getSize()));	
	std::sort(occupiedMemory.begin(), occupiedMemory.end());

	std::cout << getPageBreaker("Memory Table") << std::endl;
	// memory is completely free
	if (occupiedMemory.size() == 0) {
		std::cout << "[0; " << getMemorySize() - 1 << "] - free" << std::endl;
	}

	else {
		// free space at the beggining of memory
		if (occupiedMemory.begin()->first > 0) {
			std::cout << "[0; ";
			std::cout << occupiedMemory.begin()->first - 1 << "]";
			std::cout << " - free" << std::endl;
		}

		// segments
		for (int i = 0; i < segments.size() - 1; i++) {
			std::cout << "[" << segments[i]->getPosition() << "; ";
			std::cout << segments[i]->getPosition() + segments[i]->getSize() - 1;
			std::cout << "] - " << segments[i]->getName() << std::endl;

			if (segments[i]->getPosition() + segments[i]->getSize() != segments[i + 1]->getPosition()) {
				std::cout << "[" << segments[i]->getPosition() + segments[i]->getSize() - 1;
				std::cout << "; " << segments[i + 1]->getPosition() - 1;
				std::cout << "] -  free" << std::endl;
			}
		}
		std::cout << "[" << segments.back()->getPosition() << "; ";
		std::cout << segments.back()->getPosition() + segments.back()->getSize() - 1;
		std::cout << "] - " << segments.back()->getName() << std::endl;

		// free space at the ending of memory
		if (occupiedMemory.back().second != getMemorySize()) {
			std::cout << "[" << occupiedMemory.back().second << "; ";
			std::cout << getMemorySize() - 1;
			std::cout << "] - free" << std::endl;
		}
	}

	std::cout << getPageBreaker("End of Memory Table") << std::endl;
}

int MemoryManager::getMemorySize() {
	return memorySize;
}

