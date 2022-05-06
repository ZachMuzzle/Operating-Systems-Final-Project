#include "Node.h"
#include "headers.h"

int extractFromString(char *str) {
	int x = 0;
	int i = std::strlen(str) - 1;
	int j = 0;
	while (str[i] != '=') {
		x += pow(10, j) * (str[i] - '0');
		j++;
		i--;
	}
	return x;
}
