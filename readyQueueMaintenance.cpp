#include "Node.h"
#include "headers.h"

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