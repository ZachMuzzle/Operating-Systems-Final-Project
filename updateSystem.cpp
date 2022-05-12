#include "Node.h"
#include "headers.h"
/* Update System Function
Just sets temp of system, if the temp is equal to update pointer of jobNumber then temp status is set to the current status.
Otherwise temp is set to temp pointer to next.
 */
void updateSystem(Node *sys, Node *update, string status) {
	Node *temp = sys;
	while (temp != NULL) {
		if(temp->jobNumber == update->jobNumber) {
			temp->status = status;
		}
		temp = temp->next;
	}
}