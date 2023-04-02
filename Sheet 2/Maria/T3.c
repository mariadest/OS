#include<stdio.h>
#include<stdlib.h>
#include<unistd.h> 
#include<pthread.h> 
#define SIZE 10000
#define NUM_THREADS 5
int result;
pthread_mutex_t lock;

struct args
{
	int *arr;
	int start;
	int end;
};

void * accumulate(void * in)
{
	//TODO implement accumlate
	// saves the sum in a separate variable 
	// only adds to the actual result when done calculating
	int sum = 0;

	struct args *thread_args = (struct args*) in;

	// calculating
	for(int i = (*thread_args).start; i < (*thread_args).end; i++) {
		sum += (*thread_args).arr[i];
	}

	// waiting to unlock the mutex lock and then adding to the total sum
	pthread_mutex_lock(&lock);
	result += sum;
	pthread_mutex_unlock(&lock);

	return NULL;
}

int main ()
{

	result=0;
    int arr[SIZE];    
    for(int i=0;i<SIZE;i++){
		arr[i]=1;
	}

	pthread_t threads[NUM_THREADS-1];
	struct args thread_args[NUM_THREADS-1];
	// TODO create a team of thread, each thread must take SIZE/NUM_THREADS to accumulate
	// TODO use struct args to pass arguments to the accumulate function  
	// TODO main thread must participate in the calculation
	// TODO make sure all threads finished

	// create mutex lock
	pthread_mutex_init(&lock, NULL);

	// fill in thread_args
	for (int i = 0; i < NUM_THREADS - 1; i++) {
		int nr = SIZE/NUM_THREADS;
		
		thread_args[i].arr = arr;
		thread_args[i].start = i * nr;
		thread_args[i].end = (i + 1) * nr;
	}


	// fill in thread_args and create thrads
	for (int i = 0; i < NUM_THREADS - 1; i++) {
		pthread_create(&threads[i], NULL, &accumulate, (void*) &thread_args[i]);
	}

	// waiting for all threads to finish
	for (int i = 0; i < NUM_THREADS - 1; i++) {
		pthread_join(threads[i], NULL);
	}

	// calculating in the main thread
	int sum = 0;

	for(int i = (*thread_args).start; i < (*thread_args).end; i++) {
		sum += (*thread_args).arr[i];
	}

	// unlocks the mutex lock to then add to the total sum
	pthread_mutex_lock(&lock);
	result += sum;
	pthread_mutex_unlock(&lock);

	// printing the result
	printf("sum  is %d\n", result);
}

