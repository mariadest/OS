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
	return NULL;
}
int main ()
{

	result=0;
        int arr[SIZE];    
        for(int i=0;i<SIZE;i++)
		arr[i]=1;

	pthread_t threads[NUM_THREADS-1];
	struct args thread_args[NUM_THREADS-1];
	// TODO create a team of thread, each thread must take SIZE/NUM_THREADS to accumulate
	// TODO use struct args to pass arguments to the accumulate function  
	// TODO main thread must participate in the calculation
	// TODO make sure all threads finised
	printf("sum  is %d\n", result);
}

