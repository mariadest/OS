#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define SIZE 5
struct process{
	int process_id;
	int arrival_time;
	int execution_time;
	int start_time;
};

void init_processes(struct process *);
void display(struct process *);
void display_average_waiting_time(struct process *);
void schedule_FCFS(struct process *);
void schedule_SJF(struct process *);
void schedule_LJF(struct process *);



// ------------------------------------------------
//         MAIN METHOD
// ------------------------------------------------
int main()
{
	struct process processes[SIZE];	
	init_processes(processes);

	printf("Orignial input (processes)\n");
	display(processes);

	printf("\n");
	schedule_FCFS(processes);
	printf("Execution according to FCFS policy\n");
	display(processes);
	display_average_waiting_time(processes);	

	printf("\n");
	schedule_SJF(processes);
	printf("Execution according to SJF policy\n");
	display(processes);
	display_average_waiting_time(processes);	

	printf("\n");
	schedule_LJF(processes);
	printf("Execution according to LJF policy\n");
	display(processes);
	display_average_waiting_time(processes);	
	

}
// ------------------------------------------------


// initializes the struct process
void init_processes(struct process * input)
{
	srand(100);
	for(int i=0;i<SIZE;i++)
	{
		input[i].arrival_time = rand()%10;
		input[i].execution_time = rand()%10;
		input[i].process_id= i;
		input[i].start_time=-1;      
	}	
}

// displays the struct process
void display(struct process * input){
	printf("process<id, arr, exe, start>:");
	for(int i=0;i<SIZE;i++)
	{
		printf("<%d,%d,%d,%d> ",  input[i].process_id,
		 input[i].arrival_time,  input[i].execution_time, input[i].start_time);	
	}
	printf("\n");
}

// schedules according to FCFS
void schedule_FCFS(struct process * arr)
{
	// calculates the start_time of each process by giving the first process to arrive a start_time of 0
	// all following processes get the execution_time of those before added to their start_time
	int startTime = 0;
	for (int i = 0; i < SIZE; i++){
		arr[i].start_time = startTime;
		startTime += arr[i].execution_time;
	}

}

// schedules the processes according to which job is the fastest
void schedule_SJF(struct process * arr)
{
	int shortestTime = INT_MAX;	// assuming no process is longer than that
	int shortestJob;
	int startingTime = 0;

	// reseting starting times
	// this is technically not needed but it allows to run several scheduling methods in the main method without recompiling
	for (int i = 0; i < SIZE; i++) {
		arr[i].start_time = -1;
	}

	// goes over all processes
	for (int j = 0; j < SIZE; j++) {
		// gets the shortest process which hasn't been assigned a starting time
		for (int i = 0; i < SIZE; i++) {
			if (arr[i].execution_time <= shortestTime && arr[i].start_time == -1) {
				shortestTime = arr[i].execution_time;
				shortestJob = i;
			}
		}

		arr[shortestJob].start_time = startingTime;			// sets the start time of the chosen process
		startingTime += arr[shortestJob].execution_time;	// updates the general starting time
		shortestTime = INT_MAX;								// resets variable to check for the shortest execution time
	}
}

// schedules the processes according to which job takes the longest
void schedule_LJF(struct process * arr)
{
    int longestJob;
	int longestTime = 0;
	int startingTime = 0;

	// reseting starting times
	// this is technically not needed but it allows to run several scheduling methods in the main method without recompiling
	for (int i = 0; i < SIZE; i++) {
		arr[i].start_time = -1;
	}

	// goes over all processes
	for (int j = 0; j < SIZE; j++) {
		// gets the longest process which hasn't been assigned a starting time
		for (int i = 0; i < SIZE; i++) {
			if (arr[i].execution_time >= longestTime && arr[i].start_time == -1) {
				longestTime = arr[i].execution_time;
				longestJob = i;
			}
		}

		arr[longestJob].start_time = startingTime;			// sets the start time of the chosen process
		startingTime += arr[longestJob].execution_time;		// updates the general starting time
		longestTime = 0;									// resets variable to check for the longest execution time
	}
}

void display_average_waiting_time(struct process * arr)
{
	// calculates the average waiting time by adding up all start times and then dividing by the amount of processes
	float avgWaitingTime = 0;
	for (int i = 0; i < SIZE; i++) {
		avgWaitingTime += arr[i].start_time;
	}
	avgWaitingTime = avgWaitingTime / SIZE;
	printf("-------------------------------\n");
	printf("| Average waiting time: %2.2fs |\n", avgWaitingTime);
	printf("-------------------------------\n");
}
