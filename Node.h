
#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include <stdlib.h>
#include <string>
#include <cctype>

using namespace std;

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

#endif /* NODE_H_ */
