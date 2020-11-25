#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
void swap(int *p,int *q)
{
int temp=*p;
*p=*q;
*q=temp;

}

void bubblesort(int a[],int ch,int size)
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
 
void display(int a[],int size)
{

for(int i=0;i<size;i++)
{
printf("%d ",a[i]);
}
printf("\n");
}
 
int main()
{
int n;
printf("Enter the value of n(Size of Array): ");
scanf("%d",&n);
int *a =(int *)malloc(n*sizeof(int));
printf("Enter Array Elements: ");
for(int i=0;i<n;i++)
scanf("%d",&a[i]);
pid_t pid;
pid=fork();
if(pid==0)
{
printf("Ascending Order:");
bubblesort(a,1,n);
display(a,n);
}
else
{
wait(NULL);
printf("Descending Order:");
bubblesort(a,0,n);
display(a,n);
}

}
