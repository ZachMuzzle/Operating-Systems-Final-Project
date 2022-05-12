#include "Node.h"
#include "headers.h"
/* Function just reads command as a string and will decide which function it then goes to. */
void readCommand(string input, Node *sys, Node *submit, Node *wait, Node *hold1, Node *hold2, Node *ready, Node *run, Node *complete) {
	/*Convert the string to a char array and split (space as delimiter)*/
	char parsed[input.length()];
	std::strcpy(parsed, input.c_str());
	char *str;
	str = std::strtok(parsed, " ");

	/*Pass the current input to appropriate method*/
	if (input[0] == 'C') {
		/*System configuration*/
		configureSystem(str);
	} else if (input[0] == 'A') {
		/*Arrival of a job*/
		createJob(str, sys, submit);
	} else if (input[0] == 'Q') {
		/*A request for devices*/
		makeRequest(str, sys, run, ready, wait);
	} else if (input[0] == 'L') {
		/*A release of devices*/
		release(str, sys, run, wait, ready);
	} else if (input[0] == 'D') {
		/*Status display*/
		statusDisplay(input, sys, submit, hold1, hold2, ready, run, wait, complete);
	} else {
		/*Unrecognized input*/
	}
}