#ifndef INFORMATION_MANAGER_H
#define INFORMATION_MANAGER_H

#include <string>

class Directory;
class Disk;
class File;
class Scheduler;

class InformationManager {
public:
	InformationManager(Scheduler * s, std::string filename);
	~InformationManager();
	File * getFile(std::string fullpath);

private:
	Scheduler * scheduler;
	Disk * disk;
	Directory * root;
};

#endif
