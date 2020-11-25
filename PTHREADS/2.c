#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include<math.h>
#include<pthread.h>
int asc[10000],desc[10000];
int size;

void swap(int *p,int *q)
{
int temp=*p;
*p=*q;
*q=temp;

}

void bubblesort(int a[],int ch)
{


for(int i=0;i<size-1;i++)
{
for(int j=0;j<size-i-1;j++)
{
int choice=(ch==0)?(a[j]<a[j+1]):(a[j]>a[j+1]);
if(choice==1)
{
swap(&a[j],&a[j+1]);

}
 }
 }
 }
void* process(void *arg)
{
   int ch=*((int*)arg);
   if(ch==0)
   bubblesort(desc,ch);
   else
   bubblesort(asc,ch);
   
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
{
scanf("%d",&x);
asc[i]=x;
desc[i]=x;
}

pthread_t pth[2];

int as=0;
pthread_create(&pth[0],NULL,process,&as);
int de=1;
pthread_create(&pth[1],NULL,process,&de);


for(int i=0;i<2;i++)
{
   pthread_join(pth[i],NULL);   
}
printf("Descending Order:\n");
display(desc);
printf("Ascending Order:\n");
display(asc);

return 0;
}