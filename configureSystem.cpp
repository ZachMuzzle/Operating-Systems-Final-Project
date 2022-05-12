#include "Node.h"
#include "headers.h"
/* Function is used to configure the system we just get the values of our M, S, and Q states */
void configureSystem(char *str) {
	while (str != NULL) {
		if (str[0] == 'M') {
			memory = extractFromString(str);
			currentMemory = memory;
		} else if (str[0] == 'S') {
			devices = extractFromString(str);
			currentDevices = devices;
		} else if (str[0] == 'Q') {
			quantum = extractFromString(str);
		} else {
			/*Unrecognized input*/
		}
		str = std::strtok(NULL, " "); // Split on each spaced string and return str again until empty.
	}
}
