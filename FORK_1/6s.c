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

void bubblesort(int a[],int ch,int start,int end)
{



for(int i=start;i<end-1;i++)
{
for(int j=start;j<end-(i-start)-1;j++)
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
printf("Enter n\n");
scanf("%d",&n);
int *a =(int *)malloc(n*sizeof(int));
printf("Enter Array values\n");
for(int i=0;i<n;i++)
{
scanf("%d",&a[i]);

}
pid_t pid1;
pid1=vfork();
if(pid1==0)
{


bubblesort(a,1,0,n/2);
exit(0);
}
else
{
wait(NULL);
bubblesort(a,0,n/2,n);
printf("Result: ");
display(a,n);

}


return 0;
}


