#include <stdexcept>
#include <fstream>
#include <sstream>

#include "information_manager.h"
#include "common.h"
#include "file.h"

InformationManager::InformationManager(Scheduler * s, std::string filename) :
									   scheduler(s) {
	std::string line;
	std::ifstream file(filename.c_str());
	if (!file.is_open())
		throw std::runtime_error("Could not read filesystem info: " + filename +
							     " does not exist.");

	int isPublic;
	std::string owner;
	int fileSize;
	std::string fullpath;

	root = new Directory("");
	
	while (!file.eof()) {
		std::string line;
		getline (file, line);
		std::stringstream lineStream(line);

		if(line == "")
			continue;

		isPublic = readInteger(lineStream);
		if (isPublic < 0 || isPublic > 1)
			throw std::runtime_error("Invalid information in filesystem \
description: public attribute should be 0 or 1.");

		owner = readString(lineStream);
		// to-do: check if file has a valid owner

		fileSize = readInteger(lineStream);
		if (fileSize < 0)
			throw std::runtime_error("Invalid information in filesystem \
description: filesize must be positive.");

		fullpath = readQuotes(lineStream);
		if (!isPath(fullpath))
			throw std::runtime_error("Invalid information in filesystem \
description: invalid path.");

		std::string strParentDir = getParentDir(fullpath);
		Directory * parentDir = root->recursivelyCreateDir("." + strParentDir); 
		File * file = new PlainFile(fullpath.substr(strParentDir.length(),
													fullpath.size() - strParentDir.length()),
									fileSize);
		parentDir->addFile(file);
	}
}

InformationManager::~InformationManager() {
	delete root;
}

File * InformationManager::getFile(std::string fullpath) {
	return root->recursivelyGetFile('.' + fullpath);
}

