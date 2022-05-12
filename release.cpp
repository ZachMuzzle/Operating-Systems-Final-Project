#include "Node.h"
#include "headers.h"
/* Function for "A Release for Devices" part. */
void release(char *str, Node *sys, Node *run, Node *wait, Node *ready) {
	quantumSlice = 0;
	int j = 0;
	int d = 0;
	/* Loops str for J and D str and assign values */
	while (str != NULL) {
		if (str[0] == 'J') {
			j = extractFromString(str);
		} else if (str[0] == 'D') {
			d = extractFromString(str);
		}
		str = std::strtok (NULL, " ");
	}
	// If j is not equal to run pointer to next pointer to jobnumber then we couldn't release teh device
	if (j != run->next->jobNumber) {
		cout << "Job " << j << " couldn't release devices. " << endl;
		cout << "Job " << j << " not running on the CPU. " << endl << endl;
		return;
	}
	// 
	if (run->next->jobDevicesGranted) {
		if (d > run->next->devicesRequested) { // if devices is greater than devices requested we print and return
			cout << "Job " << j << " couldn't release devices. " << endl;
			cout << "Release exceeds amount of devices requested. " << endl << endl;
			return;
		}
		// otherwise we release devices
		cout << "Job " << j << " releases " << d << " devices." << endl << endl;
		currentDevices += d;

		/*Check wait queue*/
		waitQueueMaintenance(sys, wait, ready);
	} else {
		cout << "Job " << j << " couldn't release devices. " << endl;
		cout << "Job " << j << "'s initial request for devices was denied. " << endl << endl;
	}
}