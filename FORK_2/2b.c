#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include<time.h>


void swap(int* a, int* b) 
{ 
	int t = *a; 
	*a = *b; 
	*b = t; 
} 

int split (int arr[], int low, int high) 
{ 
	int pivot = arr[high]; 
	int i = (low - 1); 

	for (int j = low; j <= high- 1; j++) 
	{ 
		if (arr[j] < pivot) 
		{ 
			i++; 
			swap(&arr[i], &arr[j]); 
		} 
	} 
	swap(&arr[i + 1], &arr[high]); 
	return (i + 1); 
} 


void qsp(int arr[], int low, int high) 
{ 
	if (low < high) 
	{ 
		
		pid_t pid;
  		pid=vfork();
  		if(pid==0)
  		{
  			int pi = split(arr, low, high); 
  			qsp(arr, low, pi - 1);
  			_exit(0);
  		}
  		else
  		{
  			int pi = split(arr, low, high); 
  			qsp(arr, pi + 1, high);
  		}
	} 
} 

void qss(int arr[], int low, int high) 
{ 
    if (low < high) 
    { 
        
        int pi = split(arr, low, high); 
  
        qss(arr, low, pi - 1); 
        qss(arr, pi + 1, high); 
    } 
} 

void printArray(int arr[], int size) 
{ 
	int i; 
	for (i=0; i < size; i++) 
		printf("%d ", arr[i]); 
	printf("\n"); 
} 

int main() 
{ 
	int n;
	clock_t t1,t2;
	
	n=8000;
	int arr1[n];
	int arr2[n];
	printf("\nNo of Elements: %d\n",n);

	for(int i=0;i<n;i++)
	{
		int x=rand();
		arr1[i]=arr2[i]=x;
	}

	t1=clock();
	qsp(arr1, 0, n-1); 
	t2=clock();
	
 	printf("Multi-processing: %lf\n",(t2-t1)/(double)CLOCKS_PER_SEC);
 
	t1=clock();
	qss(arr2, 0, n-1); 
 	t2=clock();
 
	printf("Normal Processing: %lf\n\n",(t2-t1)/(double)CLOCKS_PER_SEC);
	
	return 0; 
} 

