#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include<math.h>
#include<pthread.h>
#include<string.h>


int arr[10000];

struct node
{
    int start;
    int end;
};

void merge(int start,int mid, int end)
{
 int at[end+1],k=start;
 int i=start,j=mid+1;
 while(i<=mid && j<=end)
 {
  if(arr[i]<arr[j])
  at[k++]=arr[i++];
  else 
    at[k++]=arr[j++];
 }
 
 if(i>mid)
 while(j<=end)
  at[k++]=arr[j++];
 if(j>end)
 while(i<=mid)
  at[k++]=arr[i++];
 
 for(int i=start;i<k;i++)
 {arr[i]=at[i];
 
 }
 
 
}

void ms(int start, int end)
{
 if(start<end)
 {
  int mid=(start+end)/2;
  pid_t pid;
  pid=vfork();
  if(pid==0)
  {
  ms(start,mid);
  _exit(0);
  }
  else
  {
  ms(mid+1,end);
  
   merge(start,mid,end);
  
  }
 
 }
}

void *process(void*arg)
{
    struct node *temp=(struct node*)arg;
    ms(temp->start,temp->end);
    pthread_exit(NULL);
}

void parallelize(int n)
{
    struct node* temp=(struct node*)malloc(4*sizeof(struct node));
    for(int i=0;i<4;i++)
    {
        temp[i].start=(i*(n/4));
        temp[i].end=(i+1)*(n/4)-1;
    }
    
    pthread_t pid[4];
    for(int i=0;i<4;i++)
        pthread_create(&pid[i],NULL,process,&temp[i]);
    
    for(int i=0;i<4;i++)
        pthread_join(pid[i],NULL);

    merge(0,(n/2-1)/2,n/2-1);
    merge(n/2,n/2+(n-1-n/2)/2,n-1);
    merge(0,(n-1)/2,n-1);

}

void display(int a[],int n)
{
    for(int i=0;i<n;i++)
        printf("%d ",a[i]);

    printf("\n");
}

int main()
{
int n;

printf("Enter No of Elements:\n");
scanf("%d",&n);

for(int i=0;i<n;i++)
{
int x=rand()%30;
arr[i]=x;

}
parallelize(n);


printf("Multi-processing Merge Sort Result:\n");
 
display(arr,n);
  
  return 0;
}
