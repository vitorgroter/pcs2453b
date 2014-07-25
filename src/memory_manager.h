#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <vector>
#include <string>

class Memory;
class OperatingSystem;
class Scheduler;
class Segment;

class MemoryManager {
public:
	MemoryManager(Scheduler * s, OperatingSystem * os, Memory * m);
	void loadSegment(std::string name);
	void printTable();

private:
	Scheduler * scheduler;
	OperatingSystem * operatingSystem;
	Memory * memory;

	Segment * findLoadedSegment(std::string name);
	std::vector <Segment *> segments;

	int findContiguousMemory(int size);
};

#endif // MEMORY_MANAGER_H
