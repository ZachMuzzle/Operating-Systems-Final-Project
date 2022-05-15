
#include "Node.h"
#include "headers.h"

using namespace std;

/*Traverse the system node and print information*/
void printSystem(Node *list) {
	Node *temp = list;
	if (temp->next == NULL) {
		cout << "No jobs have arrived yet." << endl;
	} else {
		while (temp != NULL) {
			if (temp->head == false) {
				cout << "Job number: " << temp->jobNumber << " | Status: ";
				if (temp->status == "Completed") {
					cout << temp->status << " at time " << temp->completionTime << " | Turnaround Time: " << temp->turnaroundTime << " | Weighted Turnaround Time: ";
					cout << fixed << setprecision(2) << temp->weightedTT;
				} else {
					cout << temp->status << " | Time Remaining: " << temp->remainingTime;
				}
				cout << endl;
			}
			temp = temp->next;
		}
	}
}

/*Traverse a list and print information about each node*/
void traverseAndPrint(Node *list) {
	Node *temp = list;
	if (temp->next == NULL) {
		cout << "This Queue is empty." << endl;
	} else {
		int i = 1;
		while (temp != NULL) {
			if (temp->head == false) {
				cout << "Place in queue: " << i << " | Job number: " << temp->jobNumber << " " << endl;
				i++;
			}
			temp = temp->next;
		}
	}
}

/*Add node to front of list*/
void addToFront(Node *head, Node *addition) {
	Node *temp = new Node;
	temp->next = head->next;
	head->next = addition;
	addition->next = temp->next;
}

/*Add node to end of list*/
void addToEnd(Node *head, Node *addition) {
	if (head->next == NULL) {
		head->next = addition;
		addition->next = NULL;
	} else {
		Node *temp = head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = addition;
		addition->next = NULL;
	}

}

/*Remove a node from a list and return that node*/
Node *remove(Node *head, int target){
	Node *temp = head;
	Node *tempPrev = NULL; //Keep track of previous node

	while(temp != NULL) {
		if (temp->jobNumber == target) {
			tempPrev->next = temp->next; //Remove selected node from queue
			temp->next = NULL;
			return temp;
		}
		tempPrev = temp;
		temp = temp->next;
	}

	return NULL; //Node not in list
}
