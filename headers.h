#ifndef HEAD_H
#define HEAD_H

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <math.h>
#include <iomanip>
#include <cctype>


using namespace std;

#define MAX_NUMBER_INPUTS 50
#define LONG_TIME 9999

/*Define the path of the input file*/
#define FILE "/Users/zachary/CISC361/Project/test-project/test-code/test_file/text.txt"

/*Possible statuses of nodes*/
#define REJECTED "Rejected"
#define SUBMIT_QUEUE "Submit Queue"
#define HOLD_QUEUE_1 "Hold Queue 1"
#define HOLD_QUEUE_2 "Hold Queue 2"
#define READY_QUEUE "Ready Queue"
#define RUNNING "Running on the CPU"
#define WAIT_QUEUE "Wait Queue"
#define COMPLETED "Completed"

extern int realTime; //= 0;
extern int inputNumber; //= 0;
extern bool simulating; //= true;
extern bool allInputRead; //= false;
extern bool multipleInputs; //= false;
extern int currentInputTime;
extern int numberOfInputs; 
extern int memory; //= 0;
extern int currentMemory; //= 0;
extern int devices; //= 0;
extern int currentDevices; //= 0;
extern int quantum; //= 0;
extern int quantumSlice; //= 0;

#endif /* HEAD_H */