#include "Node.h"
#include "headers.h"
/* This function is the "A Request for Devices" part */
void makeRequest(char *str, Node *sys, Node *run, Node *ready, Node *wait) {
	int quantumSlice = 0;
	int j = 0;
	int d = 0;
	/* We check string and asssign values only to J and D */
	while (str != NULL) {
		if (str[0] == 'J') {
			j = extractFromString(str);
		} else if (str[0] == 'D') {
			d = extractFromString(str);
		}
		str = std::strtok (NULL, " ");
	}

	/* This is where the function is different.
	We are now making request for jobs. However, we must check if jobs are running on CPU. */
	run->next->devicesRequested = d;

	if (j != run->next->jobNumber) {
		cout << "Job " << j << "'s request for " << d << " devices denied." << endl;
		cout << "Job " << j << " not running on the CPU." << endl << endl;
		return;
	}

	if (run->next->devicesRequested > run->next->maxJobDevices) {
		cout << "Job " << j << "'s request for " << d << " devices denied." << endl;
		cout << "Request exceeds maximum." << endl << endl;
		return;
	}

	if (j == run->next->jobNumber && d <= currentDevices) {
		cout << "Job " << j << "'s request for " << d << " devices granted." << endl << endl;

		run->next->jobDevicesGranted = true;
		currentDevices -= d;
		Node *transfer = remove(run, run->next->jobNumber);
		addToEnd(ready, transfer);

		/*Update system status*/
		updateSystem(sys, transfer, READY_QUEUE);
	} else {
		cout << "Job " << j << "'s request for " << d << " devices denied." << endl;
		cout << "Devices not available." << endl << endl;

		run->next->jobDevicesGranted = false;
		Node *firstTransfer = remove(run, run->next->jobNumber);
		addToEnd(wait, firstTransfer);

		Node *secondTransfer = remove(ready, ready->next->jobNumber);
		addToEnd(run, secondTransfer);

		/*Update system status*/
		updateSystem(sys, firstTransfer, WAIT_QUEUE);
		updateSystem(sys, secondTransfer, RUNNING);
	}
}