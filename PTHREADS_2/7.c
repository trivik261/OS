#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include<math.h>
#include<pthread.h>
int a[10000];
int size;

struct node
{
    int key;
    int half;
    int first;
    int last;
};

int bs(int a[],int start,int end,int key)
{

while(start<=end)
{
int mid=start+(end-start)/2;
if(a[mid]==key)
return mid;
else if(a[mid]<key)
start=mid+1;
else
end=mid-1;
}
return -1;
}

void swap(int *p,int *q)
{
int temp=*p;
*p=*q;
*q=temp;

}

void bubblesort(int a[],int ch,int start ,int end)
{
int i,j;
for(i=start;i<end-1;i++)
{
for(j=start;j<end-(i-start)-1;j++)
{

int choice=(ch==0)?(a[j]<a[j+1]):(a[j]>a[j+1]);
if(choice==1)
{
swap(&a[j],&a[j+1]);

}
}
}
}

void occurence(int a[],int start,int end,int index,struct node *temp)
{
    
    int first=index,last=index;
    if(index!=-1)
    {
    while(a[first-1]==a[index] && first-1>=0)
    {
       first--;
    }
    while(a[last+1]==a[index] && last+1<end)
    {
       last++;
    }
    }
    temp->first=first;
    temp->last=last;

}

void* process(void *arg)
{
   struct node *temp=(struct node*)arg;
   
   if(temp->half==1)
   {
       bubblesort(a,1,0,size/2);
       int index=bs(a,0,size/2-1,temp->key);
       occurence(a,0,size/2,index,temp);
   }
   else
   {
       bubblesort(a,1,size/2,size);
       int index=bs(a,size/2,size-1,temp->key);
       occurence(a,size/2,size,index,temp);
    
    }
   
   pthread_exit(NULL);
}
 
void display(int a[])
{

for(int i=0;i<size;i++)
{
printf("%d ",a[i]);
}
printf("\n");
}
 
int main()
{
int x;
printf("Enter the value of n(Size of Array): ");
scanf("%d",&size);

printf("Enter Array Elements: ");

for(int i=0;i<size;i++)
scanf("%d",&a[i]);


struct node* keys=(struct node*)malloc(2*sizeof(struct node));

printf("Enter the key to be searched in first half and second half respectively:\n");
scanf("%d %d",&keys[0].key,&keys[1].key);

keys[0].half=1;
keys[1].half=2;

pthread_t pth[2];


pthread_create(&pth[0],NULL,process,&keys[0]);
pthread_create(&pth[1],NULL,process,&keys[1]);


for(int i=0;i<2;i++)
{
   pthread_join(pth[i],NULL);   
}

for(int i=0;i<2;i++)
{
    if(keys[i].first!=-1)
    printf("\nKey Searched at '%d' half:%d\nNo of Occurences:%d\n\n",keys[i].half,keys[i].key,keys[i].last-keys[i].first+1);
    else
    printf("\nKey=%d not found at '%d' half\n",keys[i].key,keys[i].half);
    
}

return 0;
}

