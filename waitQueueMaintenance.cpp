#include "Node.h"
#include "headers.h"
/* Wait Queue Maintenacne Function */
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