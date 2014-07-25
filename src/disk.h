#ifndef DISK_H
#define DISK_H

#include "scheduler.h"

class Disk {
public:
	Disk(Scheduler * s);

private:
	Scheduler * scheduler;
};

#endif // DISK_H