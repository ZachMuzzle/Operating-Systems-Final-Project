program: main.o configureSystem.o createJob.o extractFromString.o getCurrentInputTime.o holdQueue1Maintenance.o holdQueue2Maintenance.o \
makeRequest.o Node.o readCommand.o readyQueueMaintenance.o release.o runningQueueMaintenance.o  statusDisplay.o \
submitQueueMaintenance.o updateSystem.o waitQueueMaintenance.o
	clang++ -o main.exec main.o configureSystem.o createJob.o extractFromString.o getCurrentInputTime.o holdQueue1Maintenance.o holdQueue2Maintenance.o \
	makeRequest.o Node.o readCommand.o readyQueueMaintenance.o release.o runningQueueMaintenance.o  statusDisplay.o \
	submitQueueMaintenance.o updateSystem.o waitQueueMaintenance.o

main.o: main.cpp
	clang++ -c main.cpp

configureSystem.o: configureSystem.cpp
	clang++ -c configureSystem.cpp

createJob.o: createJob.cpp
	clang++ -c createJob.cpp

extractFromString.o: extractFromString.cpp
	clang++ -c extractFromString.cpp

getCurrentInputTime.o: getCurrentInputTime.cpp
	clang++ -c getCurrentInputTime.cpp

holdQueue1Maintenance.o: holdQueue1Maintenance.cpp
	clang++ -c holdQueue1Maintenance.cpp

holdQueue2Maintenance.o: holdQueue2Maintenance.cpp
	clang++ -c holdQueue2Maintenance.cpp

makeRequest.o: makeRequest.cpp
	clang++ -c makeRequest.cpp

Node.o: Node.cpp
	clang++ -c Node.cpp

readCommand.o: readCommand.cpp
	clang++ -c readCommand.cpp

readyQueueMaintenance.o: readyQueueMaintenance.cpp
	clang++ -c readyQueueMaintenance.cpp

release.o: release.cpp
	clang++ -c release.cpp

runningQueueMaintenance.o: runningQueueMaintenance.cpp
	clang++ -c runningQueueMaintenance.cpp

statusDisplay.o: statusDisplay.cpp
	clang++ -c statusDisplay.cpp

submitQueueMaintenance.o: submitQueueMaintenance.cpp
	clang++ -c submitQueueMaintenance.cpp

updateSystem.o: updateSystem.cpp
	clang++ -c updateSystem.cpp

waitQueueMaintenance.o: waitQueueMaintenance.cpp
	clang++ -c waitQueueMaintenance.cpp

run: program
	./main.exec

clean:
	rm -rf *.exec && rm -rf *.o