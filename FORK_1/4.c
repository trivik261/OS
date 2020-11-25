#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include<math.h>
#include<stdbool.h>

 
int main()
{
int n,flag=0;
printf("Enter value of n to generate fibonacci and prime number sequence: ");
scanf("%d",&n);

pid_t pid;
pid=fork();
if(pid==0)
{
int a=0,b=1;
printf("Fibonacci Series(n terms):");printf("%d %d ",a,b);
for(int i=2;i<n;i++)
{
a+=b;
int temp=a;
a=b;
b=temp;
printf("%d ",b);

}
printf("\n");
}
else
{
wait(NULL);
bool a[n+1];
for(int i=2;i<=n;i++)
a[i]=true;
a[0]=a[1]=false;

printf("List of prime numbers (before n):");
for(int i=2;i<=sqrt(n);i++)
{if(a[i]==true)
{int count=2;
for(int j=2*count;j<=n;j=i*count)
{
a[j]=false;	
count++;
}
}
}
for(int i=0;i<=n;i++)
if(a[i]==true)
printf("%d ",i);

printf("\n");
}
}


