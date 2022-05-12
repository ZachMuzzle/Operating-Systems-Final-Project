#include "Node.h"
#include "headers.h"
/*Maintenance function*/
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