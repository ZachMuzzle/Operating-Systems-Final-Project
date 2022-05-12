#include "Node.h"
#include "headers.h"
/* When queue is ready reset quantum time and update system with removed transfer. */
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