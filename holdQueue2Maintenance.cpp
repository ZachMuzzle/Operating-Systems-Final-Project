#include "Node.h"
#include "headers.h"

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