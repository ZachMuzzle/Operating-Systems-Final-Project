#include "Node.h"
#include "headers.h"

void statusDisplay(string input, Node *sys, Node *submit, Node *hold1, Node *hold2, Node *ready, Node *run, Node *wait, Node *complete) {
	if (input == "D 9999 " || input == "D 9999") {
		allInputRead = true;
		return;
	}
	cout << "System status at time " << realTime << ": " << endl;
	printSystem(sys);
	cout << endl << "Submit Queue contents: " << endl;
	traverseAndPrint(submit);
	cout << endl << "Hold Queue 1 contents: " << endl;
	traverseAndPrint(hold1);
	cout << endl << "Hold Queue 2 contents: " << endl;
	traverseAndPrint(hold2);
	cout << endl << "Ready Queue contents: " << endl;
	traverseAndPrint(ready);
	cout << endl << "Running on the CPU: " << endl;
	if (run->next != NULL) {
		cout << "Job Number: " << run->next->jobNumber << endl;
	} else {
		cout << "No job currently running." << endl;
	}
	cout << endl << "Wait Queue contents: " << endl;
	traverseAndPrint(wait);
	cout << endl << "Complete Queue contents: " << endl;
	traverseAndPrint(complete);
	cout << endl;
}