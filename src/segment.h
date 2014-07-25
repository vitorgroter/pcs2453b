#ifndef SEGMENT_H
#define SEGMENT_H

#include <string>

class Segment {
public:
	Segment(std::string name, int position, int size);

	std::string getName();
	int getPosition();
	int getSize();
	int getReferenceCount();
	
	void increaseReferenceCount();
	void decreaseReferenceCount();

private:
	std::string name;
	int position;
	int size;
	int referenceCount;
};

#endif // SEGMENT_H

