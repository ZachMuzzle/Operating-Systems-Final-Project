#include "Node.h"
#include "headers.h"

void createJob(char *str, Node *sys, Node *submit) {
	Node *job = new Node;
	Node *copy = new Node; //Create a duplicate for the system history
	job->head = false;
	copy->head = false;
	job->status = SUBMIT_QUEUE;
	copy->status = SUBMIT_QUEUE;
	job->arrivalTime = currentInputTime;
	copy->arrivalTime = currentInputTime;
	job->next = NULL;
	copy->next = NULL;

	while (str != NULL) {
		if (str[0] == 'J') {
			job->jobNumber = extractFromString(str);
			copy->jobNumber = extractFromString(str);
		} else if (str[0] == 'M') {
			job->jobMemory = extractFromString(str);
			copy->jobMemory = extractFromString(str);
		} else if (str[0] == 'S') {
			job->maxJobDevices = extractFromString(str);
			copy->maxJobDevices = extractFromString(str);
		} else if (str[0] == 'R') {
			job->runTime = extractFromString(str);
			job->remainingTime = job->runTime;
			copy->runTime = extractFromString(str);
			copy->remainingTime = copy->runTime;
		} else if (str[0] == 'P') {
			job->jobPriority = extractFromString(str);
			copy->jobPriority = extractFromString(str);
		} else {
			/*Unrecognized input*/
		}
		str = std::strtok (NULL, " ");
	}

	addToEnd(submit, job);
	addToEnd(sys, copy);
}