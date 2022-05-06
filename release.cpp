#include "Node.h"
#include "headers.h"

void release(char *str, Node *sys, Node *run, Node *wait, Node *ready) {
	quantumSlice = 0;
	int j = 0;
	int d = 0;
	while (str != NULL) {
		if (str[0] == 'J') {
			j = extractFromString(str);
		} else if (str[0] == 'D') {
			d = extractFromString(str);
		}
		str = std::strtok (NULL, " ");
	}

	if (j != run->next->jobNumber) {
		cout << "Job " << j << " couldn't release devices. " << endl;
		cout << "Job " << j << " not running on the CPU. " << endl << endl;
		return;
	}

	if (run->next->jobDevicesGranted) {
		if (d > run->next->devicesRequested) {
			cout << "Job " << j << " couldn't release devices. " << endl;
			cout << "Release exceeds amount of devices requested. " << endl << endl;
			return;
		}
		cout << "Job " << j << " releases " << d << " devices." << endl << endl;
		currentDevices += d;

		/*Check wait queue*/
		waitQueueMaintenance(sys, wait, ready);
	} else {
		cout << "Job " << j << " couldn't release devices. " << endl;
		cout << "Job " << j << "'s initial request for devices was denied. " << endl << endl;
	}
}