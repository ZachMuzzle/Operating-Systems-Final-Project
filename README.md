# Operating Systems Programming Project: Scheduling and Deadlock Avoidance

## Goal of This Project
* In this project, you will design and implement a program that simulates the job scheduling, CPU scheduling, and deadlock avoidance of an operating system.

### Diagram for Project
For this simulation we will be following a diagram that consists of a submit queue, two hold queues, a ready queue, a wait queue, a run state (CPU), and a complete queue.

![diagram](photos/Screen%20Shot%202022-05-02%20at%208.29.14%20PM.jpg)

### When a job Arrives

  1. If there is not enough total main memory or total number of devices in the system for the job,the job is rejected never gets to one of the **Hold Queues**.
  2. If there is not enough available main memory for the job, the job is put in one of the **Hold Queues**, based on its priority, to wait for enough available main memory.
  3. If there is enough main memory for the job, then a process is created for the job, the required main memory is allocated to the process, and the process is put in the **Ready Queue**.

### When a job Terminates

When a job terminates, the job releases any main memory and devices(s) that it held. The release of main memory may cause one or more jobs to leave one of the **Hold Queues** and move to the **Ready Queue**. The implicit release of devices may cause one or more jobs to move from the Wait Queue to the **Ready Queue**.

### Queues are Based on Priority

We assume that the two **Hold Queues** are based on priority. There are two priorities: 1 and 2, with 1 being the highest priority. **Priority is only used for the job scheduler**.

* Job scheduling for **Hold Queue 1** is **Shortest Job First (SJF)**.
* Job scheduling for **Hold Queues 2** is **First In First Out (FIFO)**.
* Process scheduling will be **Round Robin** (with a quantum).

### Input Specification

The input for this program will be text. Each line in the file will contain one of the commands listed below. Each command consists of a letter in column one followed by a set of parameters. Each text file contains multiple type "C" (system configuration) commands.

1. **System Configuration:**
C 9 M=45 S=12 Q=1
The example above states that the system to be simulated starts at time 9, and that the system has a main memory consisting of 45; 12 serial devices; and a time quantum or time slice of 1.
<br>

2. **A Job Arrival:**
A 10 J=1 M=5 S=4 R=3 P=1
The example above states that job number 1 with priority 1 arrives at time 10, requires 5 units of main memory, holds no more than 4 devices at any point during execution, and runs for 3 units of time.
<br>

3. **A Request for Devices:**
Q 10 J=3 D=4
The example above states that at time 10, job number 3 requests for 4 devices. A job only requests devices when it is running on the **CPU**. The Quantum is interrupted to process the request. If request is granted, the process goes to the end of the **Ready Queue**, else it goes to the **Wait Queue**.
<br>

4. **A Release for Devices:**
L 10 J=5 D=1
The example above states that at time 10, job number 5 releases one device. A job only releases devices when it is running on the **CPU**. Quantum is interrupted. One or more jobs may be taken off the **Wait Queue** due to this.
<br>

5. **A Display of the Current System Status in Readable Format (with headings and properly aligned):**
D 11
The example above states that at time 11 an external event is generated and the following should be printed:
    1. A list of each job that has entered the system; for each job, print the state of the job (e.g., running on the **CPU**, in the **Hold Queue**, or finished at time 11), the remaining service time for unfinished jobs, and the turnaround time and waiting time for finished jobs.
    2. The contents of each queue.
    3. The system turnaround time only at the last display. Assume that the input file has a "D 9999" command at the end, so that you present the final state of the system.

### Deadlock

When a running job requests devices, the Banker’s algorithm is used to determine if the request can be satisfied. If the request cannot be satisfied, the process is immediately switched from the **CPU** to the **Wait Queue**.

Whenever a running job releases devices and the **Wait Queue** is not empty, the Banker’s algorithm is executed in FIFO order on each job in the Wait Queue to determine if any jobs in the **Wait Queue** can be allocated its last request of devices. If necessary, the entire **Wait Queue** is checked to restart as many jobs as possible. A similar remark applies when a job that holds devices terminates, because a job implicitly releases devices upon termination.

The **Wait Queue** is checked **FIRST** (before the **Hold Queues**) upon a completion.

### Sample Input

```
C 1 M=200 S=12 Q=4
A 3 J=1 M=20 S=5 R=10 P=1
A 4 J=2 M=30 S=2 R=12 P=2
A 9 J=3 M=10 S=8 R=4 P=1
Q 10 J=1 D=5
A 13 J=4 M=20 S=4 R=11 P=2
Q 14 J=3 D=2
A 24 J=5 M=20 S=10 R=9 P=1
A 25 J=6 M=20 S=4 R=12 P=2
Q 30 J=4 D=4
Q 31 J=5 D=7
L 32 J=3 D=2
D 9999
```

## How to Compile and run Program
* To get **.o** files:
`clang++ -c main.cpp Node.cpp`
* To create **.exec** file:
`clang++ main.o Node.o -o main.exec`
* To run program:
`./main.exec`