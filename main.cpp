
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <math.h>
#include <iomanip>
#include "Node.h"

using namespace std;

#define MAX_NUMBER_INPUTS 50
#define LONG_TIME 9999

/*Define the path of the input file*/
#define FILE "/Users/zachary/CISC361/Project/test-project/test-code/test_file/text.txt"

/*Possible statuses of nodes*/
#define REJECTED "Rejected"
#define SUBMIT_QUEUE "Submit Queue"
#define HOLD_QUEUE_1 "Hold Queue 1"
#define HOLD_QUEUE_2 "Hold Queue 2"
#define READY_QUEUE "Ready Queue"
#define RUNNING "Running on the CPU"
#define WAIT_QUEUE "Wait Queue"
#define COMPLETED "Completed"

int realTime = 0;
int inputNumber = 0;
bool simulating = true;
bool allInputRead = false;
bool multipleInputs = false;
int currentInputTime;
int numberOfInputs;

int memory = 0;
int currentMemory = 0;
int devices = 0;
int currentDevices = 0;
int quantum = 0;
int quantumSlice = 0;

/*Input processing*/
int getCurrentInputTime(string input);
void readCommand(string input, Node *sys, Node *submit, Node *wait, Node *hold1, Node *hold2, Node *ready, Node *run, Node *complete);
void statusDisplay(string input, Node *sys, Node *submit, Node *hold1, Node *hold2, Node *ready, Node *run, Node *wait, Node *complete);
void configureSystem(char *str);
void createJob(char *str, Node *sys, Node *submit);
void makeRequest(char *str, Node *sys, Node *run, Node *ready, Node *wait);
void release(char *str, Node *sys, Node *run, Node *wait, Node *ready);

/*Queue maintenance*/
void submitQueueMaintenance(Node *sys, Node *submit, Node *hold1, Node *hold2);
void waitQueueMaintenance(Node *sys, Node *wait, Node *ready);
void holdQueue1Maintenance(Node *sys, Node *hold1, Node *ready);
void holdQueue2Maintenance(Node *sys, Node *hold2, Node *ready);
void readyQueueMaintenance(Node *sys, Node *ready, Node *run);
void runningQueueMaintenance(Node *sys, Node *wait, Node *hold1, Node *hold2, Node *ready, Node *run, Node *complete);

/*Helper methods*/
void updateSystem(Node *sys, Node *update, string status);
int extractFromString(char *str);

int main () {
	/*Read input from the target text file and place in a queue of strings*/
	string line;
	string queue[MAX_NUMBER_INPUTS];
	ifstream myfile (FILE);
	if (myfile.is_open()) {
		int i = 0;
		while (getline(myfile, line)) {
			if (line[line.length() - 1] != ' ') { //Safety check
				cout << "Line not ending with a space (line " << i + 1 << ") - input ignored." << endl;
				i--;
			} else {
				queue[i] = line;
			}
			i++;
		}
		numberOfInputs = i;
		myfile.close();
	} else {
		cout << "Unable to open selected file.";
		return 0;
	}

	/*Create necessary queues*/
	Node *sys = new Node; //System is a keyword so use sys just to be safe
	sys->head = true;
	sys->next = NULL;

	Node *submitQueue = new Node;
	submitQueue->head = true;
	submitQueue->next = NULL;

	Node *holdQueue1 = new Node;
	holdQueue1->head = true;
	holdQueue1->next = NULL;

	Node *holdQueue2 = new Node;
	holdQueue2->head = true;
	holdQueue2->next = NULL;

	Node *readyQueue = new Node;
	readyQueue->head = true;
	readyQueue->next = NULL;

	Node *runningQueue = new Node;
	runningQueue->head = true;
	runningQueue->next = NULL;

	Node *waitQueue = new Node;
	waitQueue->head = true;
	waitQueue->next = NULL;

	Node *completeQueue = new Node;
	completeQueue->head = true;
	completeQueue->next = NULL;

	/*Begin simulation of system*/
	while (simulating) {

		string current = queue[inputNumber];

		/*Update time of the current input*/
		if (!allInputRead) {
			currentInputTime = getCurrentInputTime(current);
		}

		/*Process the current input, check if multiple inputs arrive at this time*/
		if (!allInputRead && realTime >= currentInputTime && !multipleInputs) {
			readCommand(current, sys, submitQueue, waitQueue, holdQueue1, holdQueue2, readyQueue, runningQueue, completeQueue);
			inputNumber++;
			if (inputNumber >= numberOfInputs - 1) {
				allInputRead = true;
			}

			if (!allInputRead) {
				int nextInputTime = getCurrentInputTime(queue[inputNumber]);
				if (currentInputTime == nextInputTime) {
					multipleInputs = true;
				}
			}
		}

		/*Handle other inputs if multiple*/
		if (multipleInputs) {
			readCommand(queue[inputNumber], sys, submitQueue, waitQueue, holdQueue1, holdQueue2, readyQueue, runningQueue, completeQueue);
			inputNumber++;
			if (inputNumber >= numberOfInputs - 1) {
				allInputRead = true;
			}

			if (!allInputRead) {
				int nextInputTime = getCurrentInputTime(queue[inputNumber]);
				if (currentInputTime == nextInputTime) {
					multipleInputs = true;
				} else {
					multipleInputs = false;
				}
			} else {
				multipleInputs = false;
			}
		}

		/*Perform submit queue maintenance*/
		submitQueueMaintenance(sys, submitQueue, holdQueue1, holdQueue2);

		/*Perform wait queue maintenance*/
		waitQueueMaintenance(sys, waitQueue, readyQueue);

		/*Perform hold queue 1 maintenance*/
		holdQueue1Maintenance(sys, holdQueue1, readyQueue);

		/*Perform hold queue 2 maintenance*/
		holdQueue2Maintenance(sys, holdQueue2, readyQueue);

		/*Perform ready queue maintenance*/
		readyQueueMaintenance(sys, readyQueue, runningQueue);

		/*Perform running queue maintenance*/
		if (!multipleInputs) {
			runningQueueMaintenance(sys, waitQueue, holdQueue1, holdQueue2, readyQueue, runningQueue, completeQueue);
		}

		/*Handle time slice switch*/
		if (quantumSlice == quantum) {
			quantumSlice = 0;
			if (readyQueue->next != NULL) {
				Node *firstTransfer = remove(runningQueue, runningQueue->next->jobNumber);
				addToEnd(readyQueue, firstTransfer);
				Node *secondTransfer = remove(readyQueue, readyQueue->next->jobNumber);
				addToEnd(runningQueue, secondTransfer);

				/*Update system status*/
				updateSystem(sys, firstTransfer, READY_QUEUE);
				updateSystem(sys, secondTransfer, RUNNING);
			}
		}

		/*Increment real time*/
		if (!multipleInputs) {
			realTime++;
		}

		/*End simulation only when all input completed and CPU finished*/
		if (runningQueue->next == NULL && allInputRead) {
			simulating = false;
		}
	}

	/*Final system display*/
	cout << "Final system status: " << endl;
	printSystem(sys);
	cout << endl << "Submit Queue contents: " << endl;
	traverseAndPrint(submitQueue);
	cout << endl << "Hold Queue 1 contents: " << endl;
	traverseAndPrint(holdQueue1);
	cout << endl << "Hold Queue 2 contents: " << endl;
	traverseAndPrint(holdQueue2);
	cout << endl << "Ready Queue contents: " << endl;
	traverseAndPrint(readyQueue);
	cout << endl << "Running on the CPU: " << endl;
	if (runningQueue->next != NULL) {
		traverseAndPrint(runningQueue);
	} else {
		cout << "No job currently running." << endl;
	}
	cout << endl << "Wait Queue contents: " << endl;
	traverseAndPrint(waitQueue);
	cout << endl << "Complete Queue contents: " << endl;
	traverseAndPrint(completeQueue);

	/*Print system turnaround time and system weighted turnaround time*/
	double i = 0;
	double k = 0;
	int j = 0;
	Node *temp = sys;
	while (temp->next != NULL) {
		i += temp->turnaroundTime;
		k += temp->weightedTT;
		j++;
		temp = temp->next;
	}
	i += temp->turnaroundTime;
	k += temp->weightedTT;
	i /= j;
	k /= j;
	cout << endl << "Average turnaround time: ";
	// std::printf("%.2f", i);
	cout << fixed << setprecision(2) << i;
	cout << endl << "Average weighted turnaround time: ";
	// std::printf("%.2f", k);
	cout << fixed << setprecision(2) << k;
	return 1;
}

/*Input processing methods*/
int getCurrentInputTime(string input) {
	char parsed[input.length()];
	std::strcpy(parsed, input.c_str()); //Convert string to char array - type out std:: just to be safe
	char * temp;
	temp = std::strtok(parsed, " "); //Split string with space as delimiter
	int i = 0;
	int t = 0;
	while (temp != NULL) {
		if (i == 1) { //We know the second char cluster in temp must be the time
			for (int j = 0; j < std::strlen(temp); j++) { //Translate char to int
				t += pow(10, std::strlen(temp) - j - 1) * (temp[j] - '0');
			}
		}
		temp = std::strtok(NULL, " ");
		i++;
	}
	return t;
}

void readCommand(string input, Node *sys, Node *submit, Node *wait, Node *hold1, Node *hold2, Node *ready, Node *run, Node *complete) {
	/*Convert the string to a char array and split (space as delimiter)*/
	char parsed[input.length()];
	std::strcpy(parsed, input.c_str());
	char *str;
	str = std::strtok(parsed, " ");

	/*Pass the current input to appropriate method*/
	if (input[0] == 'C') {
		/*System configuration*/
		configureSystem(str);
	} else if (input[0] == 'A') {
		/*Arrival of a job*/
		createJob(str, sys, submit);
	} else if (input[0] == 'Q') {
		/*A request for devices*/
		makeRequest(str, sys, run, ready, wait);
	} else if (input[0] == 'L') {
		/*A release of devices*/
		release(str, sys, run, wait, ready);
	} else if (input[0] == 'D') {
		/*Status display*/
		statusDisplay(input, sys, submit, hold1, hold2, ready, run, wait, complete);
	} else {
		/*Unrecognized input*/
	}
}

void statusDisplay(string input, Node *sys, Node *submit, Node *hold1, Node *hold2, Node *ready, Node *run, Node *wait, Node *complete) {
	if (input == "D 9999 " || input == "D 9999") {
		allInputRead = true;
		return;
	}
	cout << "System status at time " << realTime << ": " << endl;
	printSystem(sys);
	cout << endl << "Submit Queue contents: " << endl;
	traverseAndPrint(submit);
	cout << endl << "Hold Queue 1 contents: " << endl;
	traverseAndPrint(hold1);
	cout << endl << "Hold Queue 2 contents: " << endl;
	traverseAndPrint(hold2);
	cout << endl << "Ready Queue contents: " << endl;
	traverseAndPrint(ready);
	cout << endl << "Running on the CPU: " << endl;
	if (run->next != NULL) {
		cout << "Job Number: " << run->next->jobNumber << endl;
	} else {
		cout << "No job currently running." << endl;
	}
	cout << endl << "Wait Queue contents: " << endl;
	traverseAndPrint(wait);
	cout << endl << "Complete Queue contents: " << endl;
	traverseAndPrint(complete);
	cout << endl;
}

void configureSystem(char *str) {
	while (str != NULL) {
		if (str[0] == 'M') {
			memory = extractFromString(str);
			currentMemory = memory;
		} else if (str[0] == 'S') {
			devices = extractFromString(str);
			currentDevices = devices;
		} else if (str[0] == 'Q') {
			quantum = extractFromString(str);
		} else {
			/*Unrecognized input*/
		}
		str = std::strtok(NULL, " ");
	}
}

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

void makeRequest(char *str, Node *sys, Node *run, Node *ready, Node *wait) {
	quantumSlice = 0;
	int j = 0;
	int d = 0;
	while (str != NULL) {
		if (str[0] == 'J') {
			j = extractFromString(str);
		} else if (str[0] == 'D') {
			d = extractFromString(str);
		}
		str = std::strtok (NULL, " ");
	}
	run->next->devicesRequested = d;

	if (j != run->next->jobNumber) {
		cout << "Job " << j << "'s request for " << d << " devices denied." << endl;
		cout << "Job " << j << " not running on the CPU." << endl << endl;
		return;
	}

	if (run->next->devicesRequested > run->next->maxJobDevices) {
		cout << "Job " << j << "'s request for " << d << " devices denied." << endl;
		cout << "Request exceeds maximum." << endl << endl;
		return;
	}

	if (j == run->next->jobNumber && d <= currentDevices) {
		cout << "Job " << j << "'s request for " << d << " devices granted." << endl << endl;

		run->next->jobDevicesGranted = true;
		currentDevices -= d;
		Node *transfer = remove(run, run->next->jobNumber);
		addToEnd(ready, transfer);

		/*Update system status*/
		updateSystem(sys, transfer, READY_QUEUE);
	} else {
		cout << "Job " << j << "'s request for " << d << " devices denied." << endl;
		cout << "Devices not available." << endl << endl;

		run->next->jobDevicesGranted = false;
		Node *firstTransfer = remove(run, run->next->jobNumber);
		addToEnd(wait, firstTransfer);

		Node *secondTransfer = remove(ready, ready->next->jobNumber);
		addToEnd(run, secondTransfer);

		/*Update system status*/
		updateSystem(sys, firstTransfer, WAIT_QUEUE);
		updateSystem(sys, secondTransfer, RUNNING);
	}
}

void release(char *str, Node *sys, Node *run, Node *wait, Node *ready) {
	quantumSlice = 0;
	int j = 0;
	int d = 0;
	while (str != NULL) {
		if (str[0] == 'J') {
			j = extractFromString(str);
		} else if (str[0] == 'D') {
			d = extractFromString(str);
		}
		str = std::strtok (NULL, " ");
	}

	if (j != run->next->jobNumber) {
		cout << "Job " << j << " couldn't release devices. " << endl;
		cout << "Job " << j << " not running on the CPU. " << endl << endl;
		return;
	}

	if (run->next->jobDevicesGranted) {
		if (d > run->next->devicesRequested) {
			cout << "Job " << j << " couldn't release devices. " << endl;
			cout << "Release exceeds amount of devices requested. " << endl << endl;
			return;
		}
		cout << "Job " << j << " releases " << d << " devices." << endl << endl;
		currentDevices += d;

		/*Check wait queue*/
		waitQueueMaintenance(sys, wait, ready);
	} else {
		cout << "Job " << j << " couldn't release devices. " << endl;
		cout << "Job " << j << "'s initial request for devices was denied. " << endl << endl;
	}
}

/*Maintenance methods*/
void submitQueueMaintenance(Node *sys, Node *submit, Node *hold1, Node *hold2) {
	if (submit->next != NULL) {
		Node *temp = submit;
		while (temp != NULL) {
			if (temp->head == false) {
				if (temp->jobMemory > memory || temp->maxJobDevices > devices) {
					/*Reject this job - can never satisfy*/
					remove(submit, temp->jobNumber);

					/*Update system status*/
					updateSystem(sys, temp, REJECTED);
				}
				/*Transfer from submit queue to hold queues*/
				Node *transfer = remove(submit, temp->jobNumber);
				if (transfer != NULL) {
					if (transfer->jobPriority == 1) {
						addToEnd(hold1, transfer);

						/*Update system status*/
						updateSystem(sys, transfer, HOLD_QUEUE_1);
					} else if (transfer->jobPriority == 2) {
						addToFront(hold2, transfer);

						/*Update system status*/
						updateSystem(sys, transfer, HOLD_QUEUE_2);
					}
				}
			}
			temp = temp->next;
		}
	}
}

void waitQueueMaintenance(Node *sys, Node *wait, Node *ready) {
	if (wait->next != NULL) {
		Node *temp = wait;
		while (temp != NULL) {
			if (temp->head == false) {
				if (temp->maxJobDevices <= currentDevices) {
					Node *transfer = remove(wait, temp->jobNumber);
					addToEnd(ready, transfer);

					/*Update system status*/
					updateSystem(sys, transfer, READY_QUEUE);
				}
			}
			temp = temp->next;
		}
	}
}

void holdQueue1Maintenance(Node *sys, Node *hold1, Node *ready) {
	if (hold1->next != NULL) {
		Node *temp = hold1;
		int shortestJob = 0;
		int shortestJobTime = LONG_TIME; //Choose a long time to compare against
		/*Get job number of shortest job*/
		while (temp != NULL) {
			if (temp->head == false) {
				if (temp->jobMemory <= currentMemory && temp->maxJobDevices <= currentDevices) {
					if (temp->runTime < shortestJobTime) {
						shortestJobTime = temp->runTime;
						shortestJob = temp->jobNumber;
					}
				}
			}
			temp = temp->next;
		}
		/*Remove job from hold queue 1 and add to ready queue*/
		if (shortestJob > 0){
			Node *transfer = remove(hold1, shortestJob);
			addToEnd(ready, transfer);
			currentMemory -= transfer->jobMemory;

			/*Update system status*/
			updateSystem(sys, transfer, READY_QUEUE);
		}
	}
}

void holdQueue2Maintenance(Node *sys, Node *hold2, Node *ready) {
	if (hold2->next != NULL) {
		Node *temp = hold2;
		/*Get last node (FIFO)*/
		while (temp->next != NULL) {
			temp = temp->next;
		}
		if (temp->jobMemory <= currentMemory && temp->maxJobDevices <= currentDevices) {
			Node *transfer = remove(hold2, temp->jobNumber);
			addToEnd(ready, transfer);
			currentMemory = currentMemory - transfer->jobMemory;

			/*Update system status*/
			updateSystem(sys, transfer, READY_QUEUE);
		}
	}
}

void readyQueueMaintenance(Node *sys, Node *ready, Node *run) {
	if (ready->next != NULL) {
		if (run->next == NULL) {
			Node *transfer = remove(ready, ready->next->jobNumber);
			addToFront(run, transfer);
			quantumSlice = 0; //Reset quantum time

			/*Update system status*/
			updateSystem(sys, transfer, RUNNING);
		}
	}
}

void runningQueueMaintenance(Node *sys, Node *wait, Node *hold1, Node *hold2, Node *ready, Node *run, Node *complete) {
	if (run->next != NULL) {
		run->next->remainingTime--;
		quantumSlice++;

		/*Update system status*/
		Node *temp = sys;
		while (temp->jobNumber != run->next->jobNumber) {
			temp = temp->next;
		}
		temp->remainingTime--;

		if (run->next->remainingTime == 0) {
			quantumSlice = 0;
			run->next->completionTime = realTime + 1; //Add one because real time would increment at the end of this cycle
			run->next->turnaroundTime = realTime - run->next->arrivalTime;
			run->next->weightedTT = (double)run->next->turnaroundTime/(double)run->next->runTime;

			currentMemory += run->next->jobMemory;

			if (run->next->jobDevicesGranted) {
				currentDevices += run->next->devicesRequested;
			}

			/*Update system status*/
			Node *temp = sys;
			while (temp->jobNumber != run->next->jobNumber) {
				temp = temp->next;
			}
			temp->completionTime = realTime + 1;
			temp->turnaroundTime = run->next->turnaroundTime;
			temp->weightedTT = run->next->weightedTT;

			Node *transfer = remove(run, run->next->jobNumber);
			addToEnd(complete, transfer);

			/*Update system status*/
			updateSystem(sys, transfer, COMPLETED);

			/*Check wait queue, then hold queue 1, then hold queue 2*/
			waitQueueMaintenance(sys, wait, ready);
			holdQueue1Maintenance(sys, hold1, ready);
			holdQueue2Maintenance(sys, hold2, ready);

			readyQueueMaintenance(sys, ready, run);
		}
	}
}

/*Helper methods*/
void updateSystem(Node *sys, Node *update, string status) {
	Node *temp = sys;
	while (temp != NULL) {
		if(temp->jobNumber == update->jobNumber) {
			temp->status = status;
		}
		temp = temp->next;
	}
}

int extractFromString(char *str) {
	int x = 0;
	int i = std::strlen(str) - 1;
	int j = 0;
	while (str[i] != '=') {
		x += pow(10, j) * (str[i] - '0');
		j++;
		i--;
	}
	return x;
}
