#include "memory.h"

Memory::Memory(Scheduler * s) : scheduler(s) {
	size = 500000;	
}

int Memory::getSize() {
	return size;
}

