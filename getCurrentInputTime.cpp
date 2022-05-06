#include "Node.h"
#include "headers.h"

/*Input processing methods*/
int getCurrentInputTime(string input) {
	char parsed[input.length()];
	std::strcpy(parsed, input.c_str()); //Convert string to char array - type out std:: just to be safe
	char * temp;
	temp = std::strtok(parsed, " "); //Split string with space as delimiter
	int i = 0;
	int t = 0;
	while (temp != NULL) {
		if (i == 1) { //We know the second char cluster in temp must be the time
			for (int j = 0; j < std::strlen(temp); j++) { //Translate char to int
				t += pow(10, std::strlen(temp) - j - 1) * (temp[j] - '0');
			}
		}
		temp = std::strtok(NULL, " ");
		i++;
	}
	return t;
}