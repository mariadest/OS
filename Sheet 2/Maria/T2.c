#include<stdio.h>
#include<stdlib.h>
#include<unistd.h> 
#include<pthread.h> 
#define SIZE 10000

void swap(int *xp, int *yp);
void sort(int arr[], int size);

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
