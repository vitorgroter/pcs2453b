#ifndef FILE_H
#define FILE_H

#include <string>
#include <list>

class File {
public:
	virtual ~File() = 0;
	virtual std::string getName();
	virtual int getSize() = 0;

protected:
	std::string filename;
};



class PlainFile : public File {
public:
	PlainFile(std::string name, int fileSize);
	
	int getSize();

private:
	int fileSize;
};



class Directory : public File {
public:
	Directory(std::string name);
	~Directory();

	File * getFile(std::string filename);
	File * recursivelyGetFile(std::string relativePath);

	void addFile(File * f);
	Directory * recursivelyCreateDir(std::string relativePath);

	int getSize();

private:
	std::list<File *> files;
};

#endif // FILE_H
