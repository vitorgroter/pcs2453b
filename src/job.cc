#include <cassert>
#include <fstream>
#include <limits>
#include <iostream>
#include <queue>
#include <stdexcept>

#include "common.h"
#include "job.h"

Job::Job(const char filename[]) : name(filename) {
	processingTime = 0.0;
	totalLoadedSegments = 0;
	std::ifstream file(filename);

	if (!file.is_open())
		throw std::runtime_error("Could not read job info: " + name + " does not exist.");

	while (!file.eof()) {
		std::string varName;
		varName = readString(file);


		if (varName == "arrival_time") {
			readEqualSign(file);	
			arrivalTime = readDouble(file);
		}
		else if (varName == "segment_tree") {
			readEqualSign(file);	
			segmentNameTree = readStringTree(file);
		}
		else if (varName == "total_inputs") {
			readEqualSign(file);
			totalInputs = readInteger(file);
		}
		else if (varName == "total_outputs") {
			readEqualSign(file);
			totalOutputs = readInteger(file);
		}
		else if (varName == "total_file_accesses") {
			readEqualSign(file);
			totalFileAccesses = readInteger(file);
		}
		else if (varName == "file_list") {
			readEqualSign(file);
			readQuotedStringsList(file);
		}
		else if (varName == "total_processing_time") {
			readEqualSign(file);
			totalProcessingTime = readDouble(file);
		}
		else if (varName == "") {
			file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			assert(false);
		}
	}

	// makes sure every segment in the segment name tree is a valid path string and create the segment tree
	totalSegments = 0;

	std::queue <Tree <std::string> *> nameNodes;
	std::queue <Tree <Segment *> *> segmentNodes;
	segmentTree = new Tree <Segment *> (nullptr);

	nameNodes.push(segmentNameTree);
	segmentNodes.push(segmentTree);
	while (!nameNodes.empty()) {
		totalSegments++;

		Tree <std::string> * nameNode = nameNodes.front();
		Tree <Segment *> * segmentNode = segmentNodes.front();

		nameNodes.pop();
		segmentNodes.pop();

		if (!isPath(nameNode->data))
			throw std::runtime_error("Job segment is not a path.");

		for (auto nameChild : nameNode->children) {
			Tree <Segment *> * segmentChild = new Tree <Segment *> (nullptr);
			segmentNode->children.push_back(segmentChild);
			
			nameNodes.push(nameChild);
			segmentNodes.push(segmentChild);
		}
	}

	/*
	std::cout << "arrival_time = " << arrivalTime << std::endl;
	std::cout << "total_inputs = " << totalInputs << std::endl;
	std::cout << "total_outputs = " << totalOutputs << std::endl;
	std::cout << "total_file_accesses = " << totalFileAccesses << std::endl;
	std::cout << "total_processing_time = " << totalProcessingTime << std::endl;
	*/	
}

void Job::increaseTotalLoadedSegments() {
	totalLoadedSegments++;
}

double Job::getArrivalTime() {
	return arrivalTime;
}

Tree <std::string> * Job::getSegmentNameTree() {
	return segmentNameTree;
}

Tree <Segment *> * Job::getSegmentTree() {
	return segmentTree;
}

bool Job::areAllSegmentsLoaded() {
	std::cout << std::endl;
	return totalSegments == totalLoadedSegments;
}

double Job::getTotalProcessingTime() {
	return totalProcessingTime;
}

double Job::getProcessingTime() {
	return processingTime;
}

void Job::increaseProcessingTime(double dt) {
	processingTime += dt;
}

double Job::getRemainingProcessingTime() {
	return totalProcessingTime - processingTime;
}

std::string Job::getName() {
	return name;
}

