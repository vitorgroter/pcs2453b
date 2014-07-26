#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <vector>
#include <string>

class Job;
class OperatingSystem;
class Scheduler;
class Segment;

class MemoryManager {
public:
	MemoryManager(Scheduler * s, OperatingSystem * os);
	void loadSegment(std::string name, int size, Segment ** segment, Job * j);
	void releaseSegment(Segment * segment);
	void printTable();
	
	int getMemorySize();

private:
	Scheduler * scheduler;
	OperatingSystem * operatingSystem;

	Segment * findLoadedSegment(std::string name);
	std::vector <Segment *> segments;

	int findContiguousMemory(int size);
	int memorySize;
};

#endif // MEMORY_MANAGER_H
