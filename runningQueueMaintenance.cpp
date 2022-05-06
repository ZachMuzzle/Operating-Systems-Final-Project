#include "Node.h"
#include "headers.h"
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