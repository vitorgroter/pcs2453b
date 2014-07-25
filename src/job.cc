#include <cassert>
#include <fstream>
#include <limits>
#include <iostream>
#include <queue>
#include <stdexcept>

#include "job.h"
#include "common.h"

Job::Job(const char filename[]) {
	std::ifstream file(filename);

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

	// makes sure every segment in the segment tree is a valid path string
	std::queue <Tree <std::string> *> nodes;
	nodes.push(segmentNameTree);
	Tree <std::string> * node;
	while (!nodes.empty()) {
		node = nodes.front();
		nodes.pop();

		if (!isPath(node->data))
			throw std::runtime_error("Job segment is not a path.");

		for (auto child : node->children) {
			nodes.push(child);
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

JobArrivalEvent::JobArrivalEvent(OperatingSystem * os, Job * j) : operatingSystem(os), job(j) {

}

JobArrivalEvent::~JobArrivalEvent() {

}

void JobArrivalEvent::execute() {
	operatingSystem->jobArrival(job);
}

