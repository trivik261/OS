#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include<time.h>


void merge(int start,int mid, int end,int arr[])
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

void mss(int start, int end,int arr[])
{
 if(start<end)
 {
  int mid=(start+end)/2;
  pid_t pid;
  pid=vfork();
  if(pid==0)
  {
  mss(start,mid,arr);
  _exit(0);
  }
  else
  {
  mss(mid+1,end,arr);
  
   merge(start,mid,end,arr);
  
   
  }
 
 }
}
void ms(int start, int end,int arr[])
{
 if(start<end)
 {
  int mid=(start+end)/2;
 
  ms(start,mid,arr);
 
 
  ms(mid+1,end,arr);
 
   merge(start,mid,end,arr);
  
   

 }
}
void main()
{
int n;
clock_t t1,t2;

n=10000;
int arr1[n];
int arr2[n];
printf("No of Elements:%d\n",n);

for(int i=0;i<n;i++)
{
int x=rand();
arr1[i]=arr2[i]=x;

}

t1=clock();
mss(0,n-1,arr1);
t2=clock();



 printf("Multi-processing%lf\n",(t2-t1)/(double)CLOCKS_PER_SEC);
 
t1=clock();
  ms(0,n-1,arr2);
 t2=clock();
 
 

 
 printf("Normal Processing:%lf\n",(t2-t1)/(double)CLOCKS_PER_SEC);
  
  
  
}
