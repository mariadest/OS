#include<stdio.h>
#include<stdlib.h>
#include<unistd.h> 
#include<pthread.h> 
#define SIZE 10000

void swap(int *xp, int *yp);
void sort(int arr[], int size);
int gettid();

void* meanCalc(void * arg) {
    // gets the array
    int *a = (int *) arg;
    // saves space for the calculated result
    float *result = (float *) malloc(sizeof(float));

    // calculates the mean
    for (int i = 0; i < SIZE; i++) {
		*result += a[i];
	}
	*result /= SIZE;

    // printing the thread id
    pid_t tid = gettid();
    printf("TID of the mean-Thread: %i\n", tid);

    // returns the mean
    return result;
}

void* medianCalc(void * arg) {
    // gets the array
    int *a = (int *) arg;
    // saves space for the calculated result
    float *result = (float *) malloc(sizeof(float));

    // calculates the median
    if (SIZE % 2 == 0) {
		*result = (a[SIZE/2] + a[SIZE/2 + 1]) / 2;
	} else {
		*result = a[SIZE/2 + 1];
	}
	*result = *result / 2.0;

    // printign the thread id
    pid_t tid = gettid();
    printf("TID of the median-Thread: %i\n", tid);

    // returns the median
    return result;
}

int main (){

        int arr[SIZE];    
        for(int i=SIZE-1;i>=0;i--)
                if(i%2==0)
                        arr[(SIZE-1)-i]=0;
                else
                        arr[(SIZE-1)-i]=1;
	// TODO implement you solution here
	// TODO a new thread here
        // One thread should calculate the median
        // The other thread should calculate the mean
	// One thread should display the result (mean, median)
    float *mean;
    float *median;

    // creating the threads
    pthread_t mean_thread, median_thread;
    
    pthread_create(&mean_thread, NULL, meanCalc, &arr);
    pthread_create(&median_thread, NULL, medianCalc, &arr);

    // waits for the threads to be finished
    pthread_join(mean_thread, (void *) &mean);
    pthread_join(median_thread, (void *) &median);

    // prints the results
    printf("Calculated mean: %f\n", *mean);
    printf("Calculated median: %f\n", *median);
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