#include "Node.h"
#include "headers.h"

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