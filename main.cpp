#include "Node.h"
#include "headers.h"

/* TODO: NEED TO MAKE SURE VARIABLES ARE  DEFINED IN EVERY FUNCTION
	AS PREVIOUS WAS JUST ALL IN MAIN
 */

/* Define variables globally */
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

/* TODO: MAYBE PASS VARIABLES THROUGH THE FUNCTION */
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
	return 0;
}
