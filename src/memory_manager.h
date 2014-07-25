#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <vector>
#include <string>

class Job;
class Memory;
class Scheduler;
class Segment;

class MemoryManager {
public:
	MemoryManager(Scheduler * s, Memory * m);
	void loadSegment(std::string name, int size, Segment ** segment, Job * j);
	void printTable();

private:
	Scheduler * scheduler;
	Memory * memory;

	Segment * findLoadedSegment(std::string name);
	std::vector <Segment *> segments;

	int findContiguousMemory(int size);
};

#endif // MEMORY_MANAGER_H
