#include "Node.h"
#include "headers.h"
/* This function is used to extract the string input e.g: Any input that starts with a letter we find and extact the string to then decide
what operation we use */
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
