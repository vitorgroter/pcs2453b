#ifndef JOB_H
#define JOB_H

#include "tree.h"

class Segment;

class Job {
public:
	Job(const char filename[]);
	
	inline double getArrivalTime() {
		return arrivalTime;
	}

	inline Tree <std::string> * getSegmentNameTree() {
		return segmentNameTree;
	}

	inline Tree <Segment *> * getSegmentTree() {
		return segmentTree;
	}

	inline bool areAllSegmentsLoaded() {
		return totalSegments == totalLoadedSegments;
	}

	void increaseTotalLoadedSegments();

private:
	double arrivalTime;
	int totalInputs;
	int totalOutputs;
	int totalFileAccesses;
	double totalProcessingTime;
	Tree <std::string> * segmentNameTree;
	Tree <Segment *> * segmentTree;

	int totalSegments;
	int totalLoadedSegments;
};

#endif // JOB_H

