#include<stdio.h>
#include<sys/mman.h>
#include<stdlib.h>
#include <fcntl.h>
#include <unistd.h> 
#include <errno.h>
#include <string.h>

#define SIZE 10000

void swap(int *xp, int *yp);
void sort(int arr[], int size);

int main ()
{
 	int arr[SIZE];         
	for(int i=SIZE-1;i>=0;i--)
		if(i%2==0)
            arr[(SIZE-1)-i]=0;
		else
			arr[(SIZE-1)-i]=1;

        // TODO fork another process here
	// One process should calculate the median
	// The other process should calculate the mean
	// One process should communicate its value to the other process
	// The other process should print both calculated results
	// Hint use shm_open, ftrucate, mmap, and mumap to communicate over mapped files
	
	// shared variables of the threads
	float mean = 0;
	pid_t parent;

	// create shared memory
	float* shared_memory;
	int shm;
	int size = 10240;
	shm = shm_open("median", O_RDWR | O_CREAT, 0644);			// establishes connection between shared memory object and file descriptor 
	ftruncate(shm, size);										// shortens the file to the lenght indicated by the open file
	shared_memory = (float *) mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, shm, 0); 	// mapping between address space of the processes and a file
	
	pid_t pid = fork();		// saves the current pid, will differ from parent to child

	// checks the ID and calculates either the median or mean
	// here the child calculates the median and the parent the mean
	if (pid == 0) {
		float median = 0; 

		// sorting the array
		sort(arr, SIZE);

		// calculating the median
		if (SIZE % 2 == 0) {
			median = (arr[SIZE/2] + arr[SIZE/2 + 1]) / 2;
		} else {
			median = arr[SIZE/2 + 1];
		}
		median = median / 2.0;

		// saves the median in the shared memory
		shared_memory[0] = median;
		
		// stops the child since it's not needed anymore
		exit(0);
		
	} else {
		parent = getpid();

		mean = 0;
		for (int i = 0; i < SIZE; i++) {
			mean += arr[i];
		}
		mean = mean / SIZE;
	}

	// print out the median and mean and which pid calculated it
	// we already know that the childs pid has to be 0 so we don't need to save it beforehand 
	printf("Median: %f, calculated with pid: 0\n", shared_memory[0]);
	printf("Mean: %f, calculated with pid: %i\n", mean, parent);

	return 0;
}




void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sort(int *arr, int size)
{
   int i, j;
   for (i = 0; i < size-1; i++)    
  
       // Last i elements are already in place   
       for (j = 0; j < size-i-1; j++) 
           if (arr[j] > arr[j+1])
              swap(&arr[j], &arr[j+1]);
}


