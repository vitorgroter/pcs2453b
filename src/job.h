#ifndef JOB_H
#define JOB_H

#include "tree.h"

class Segment;

class Job {
public:
	Job(const char filename[]);
	double getArrivalTime();
	Tree <std::string> * getSegmentNameTree();
	Tree <Segment *> * getSegmentTree();
	bool areAllSegmentsLoaded();

	double getTotalProcessingTime();
	double getProcessingTime();
	double getRemainingProcessingTime();
	void increaseProcessingTime(double dt);

	void increaseTotalLoadedSegments();

	std::string getName();

private:
	double arrivalTime;
	int totalInputs;
	int totalOutputs;
	int totalFileAccesses;
	double totalProcessingTime;
	double processingTime;
	Tree <std::string> * segmentNameTree;
	Tree <Segment *> * segmentTree;

	double interrequestTime;

	int totalSegments;
	int totalLoadedSegments;
	
	std::string name;
};

#endif // JOB_H

