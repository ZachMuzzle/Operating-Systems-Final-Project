#include "Node.h"
#include "headers.h"
/* This function is similar to configureSystem.cpp but it does a little more then just get the values of strings
a sets the values to each.
Here we use our Node to set our status,arrival times, head, and next of the node.
 */
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

	/*This part is similar to configureSystem.cpp as we go through the string and assign each value to the corresponding
	letter. J for Job, M for memory, R for units of time, S for max devices and P for priority.  */
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