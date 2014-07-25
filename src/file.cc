#include "file.h"
#include <stdexcept>

#include "common.h"

File::~File() {

}

std::string File::getName() {
	return filename;
}



PlainFile::PlainFile(std::string name, int fileSize) {
	filename = name;
	if (fileSize < 0)
		throw std::runtime_error("Filesize must be positive.");
	this->fileSize = fileSize;
}

int PlainFile::getSize() {
	return fileSize;
}



Directory::Directory(std::string name) {
	filename = name;
}

Directory::~Directory() {
	for (auto file : files)
		delete file;
}

File * Directory::getFile(std::string filename) {
	for (auto it = files.begin(); it != files.end(); it++) {
		if ((*it)->getName() == filename) {
			return *it;
		}
	}

	return nullptr;
}

File * Directory::recursivelyGetFile(std::string relativePath) {
	// makes sure relativePath is a relative path
	if (!isRelativePath(relativePath))
		throw std::logic_error("Directory::recursivelyGetFile expects a relative path.");

	// if necessary, removes the extra '/' at the end
	if (relativePath[relativePath.length() - 1] == '/')
		relativePath = relativePath.substr(0, relativePath.length() - 1);

	// finds the first slash after the initial "./"
	std::string::size_type slashPos = relativePath.find('/', 2);

	// no slash, we're the parent directory of the file
	if (slashPos == std::string::npos)
		return getFile(relativePath.substr(2, relativePath.length() - 2));

	// found a slash, asks for the subdirectory to find that file
	else {
		File * file = getFile(relativePath.substr(2, slashPos - 2));
		Directory * directory = dynamic_cast<Directory *> (file);

		if (directory != nullptr)
			return directory->recursivelyGetFile("./" + relativePath.substr(slashPos + 1, relativePath.length() - slashPos));
	}

	return nullptr;
}

void Directory::addFile(File * file) {
	files.push_back(file);
}

Directory * Directory::recursivelyCreateDir(std::string relativePath) {
	if (!isRelativePath(relativePath))
		throw std::logic_error("Directory::recursivelyCreateDir expects a relative path");
	
	std::string::size_type slashPos = relativePath.substr(2, relativePath.length() - 2).find('/');

	// relativePath is not actually a directory
	if (slashPos == std::string::npos)
		throw std::logic_error("Directory::recursivelyCreateDir expects directory path");

	// we're the parent dir of the directory
	else if (slashPos == relativePath.length() - 3) {
		File * file;
		Directory * dir;

		file = getFile(relativePath.substr(2, relativePath.length() - 3));
		if (file != nullptr) {
			dir = dynamic_cast<Directory *> (file);
			if (dir == nullptr)
				throw std::logic_error("Trying to create a directory but a file already exists with that name.");
		}
			else {
			dir = new Directory(relativePath.substr(2, relativePath.length() - 3));
			addFile(dir);
		}

		return dir;
	}

	// we're not the parent dir of the directory
	else {
		File * file;
		Directory * dir;

		file = getFile(relativePath.substr(2, slashPos));
		if (file != nullptr) {
			dir = dynamic_cast<Directory *> (file);
			if (dir == nullptr)
				throw std::logic_error("Trying to create a directory but a file already exists with that name.");
		}
		else {
			dir = new Directory(relativePath.substr(slashPos + 3, relativePath.length() - slashPos - 4));
			addFile(dir);
		}

		return dir->recursivelyCreateDir("./" + relativePath.substr(slashPos + 3, relativePath.length() - slashPos - 3));
	}


	assert(false);
	return nullptr;
}

int Directory::getSize() {
	return 0;
}

