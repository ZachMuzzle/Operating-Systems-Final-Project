#include "Node.h"
#include "headers.h"

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
		str = std::strtok(NULL, " ");
	}
}
