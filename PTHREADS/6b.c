#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include<time.h>
#include<pthread.h>
int arr[10000];

struct node
{
    int low;
    int high;
};

void qs(int low, int high) ;

void swap(int* a, int* b) 
{ 
	int t = *a; 
	*a = *b; 
	*b = t; 
} 

int split(int low, int high) 
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

void *process(void *arg)
{
	struct node *temp=(struct node*)arg;
	qs(temp->low,temp->high);

	pthread_exit(NULL);

}
	


void qs(int low, int high) 
{ 
    if (low < high) 
    { 
        
        int pi = split(low, high); 

   		struct node* temp=(struct node*)malloc(2*sizeof(struct node));
		   temp[0].low=low;
		   temp[0].high=pi-1;
		   temp[1].low=pi+1;
		   temp[1].high=high;

		pthread_t pid[2];
		
		for(int i=0;i<2;i++)
			{pthread_create(&pid[i],NULL,process,&temp[i]);}

		for(int i=0;i<2;i++)
			pthread_join(pid[i],NULL);

    } 
} 

void display(int n)
{
    for(int i=0;i<n;i++)
        printf("%d ",arr[i]);

    printf("\n");
}

int main() 
{ 
	int n;

	printf("Enter No of Elements:\n");
	scanf("%d",&n);

	for(int i=0;i<n;i++)
	{
		int x=rand()%20;
		arr[i]=x;;
	}

	
	qs(0, n-1); 
	printf("Multi-processing Quick Sort Result: \n");
	display(n);

	
 	
 
	
	return 0; 
} 

