#include "headers.h"

#ifndef NODE_H_
#define NODE_H_

struct Node {
	bool head;
	struct Node *next;
	string status;
	int arrivalTime;
	int completionTime;
	int turnaroundTime;
	double weightedTT;
	int jobNumber;
	int jobPriority;
	int runTime;
	int remainingTime;
	int jobMemory;
	int maxJobDevices;
	int devicesRequested;
	bool jobDevicesGranted;
};

void printSystem(Node *list);
void traverseAndPrint(Node *list);
void addToFront(Node *head, Node *addition);
void addToEnd(Node *head, Node *addition);
Node *remove(Node *head, int target);

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

#endif /* NODE_H_ */
