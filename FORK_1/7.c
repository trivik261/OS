#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
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
int bs(int a[],int start,int end,int key)
{

while(start<end)
{
int mid=start+(end-start)/2;
if(a[mid]==key)
return 1;
else if(a[mid]<key)
start=mid+1;
else
end=mid-1;
}
return 0;
}

int main()
{
int n,key;
printf("Enter n and key value\n");
scanf("%d %d",&n,&key);
printf("Enter Array values\n");
int *a =(int*)malloc(n*sizeof(int));
for(int i=0;i<n;i++)
scanf("%d",&a[i]);

pid_t pid;
pid=fork();
if(pid==0)
{
bubblesort(a,1,0,n/2);

if(bs(a,0,n/2,key))
printf("Key found at first half\n");
else
printf("Key not found at first half\n");
}
else
{
wait(NULL);
bubblesort(a,1,n/2,n);

if(bs(a,n/2,n,key))
printf("Key found at second half\n");
else
printf("Key not found at second half\n");
}


}
