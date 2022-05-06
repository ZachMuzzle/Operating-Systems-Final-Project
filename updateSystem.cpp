#include "Node.h"
#include "headers.h"

void updateSystem(Node *sys, Node *update, string status) {
	Node *temp = sys;
	while (temp != NULL) {
		if(temp->jobNumber == update->jobNumber) {
			temp->status = status;
		}
		temp = temp->next;
	}
}