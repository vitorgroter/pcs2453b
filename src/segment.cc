#include "segment.h"
#include <iostream>

Segment::Segment(std::string name, int position, int size) :
	name(name),
	position(position),
	size(size)          {

}

std::string Segment::getName() {
	return name;
}

int Segment::getPosition() {
	return position;
}

int Segment::getSize() {
	return size;
}

int Segment::getReferenceCount() {
	return referenceCount;
}

void Segment::increaseReferenceCount() {
	++referenceCount;
}

void Segment::decreaseReferenceCount() {
	--referenceCount;
}


