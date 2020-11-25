#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
pid_t pid;
printf("Enter n value:");
int n,sum;
scanf("%d",&n);
pid=fork();


if(pid==0)
{
sum=n*(n);
printf("Sum of %d odd terms=%d\n",n,sum);

}
else if(pid>0)
{
wait(NULL);
sum=n*(n+1);
printf("Sum of %d even terms=%d\n",n,sum);



}

}
