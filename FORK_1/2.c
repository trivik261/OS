#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
pid_t pid;
int n;
printf("Enter n value:");
scanf("%d",&n);
pid=fork();


if(pid==0)
{
printf("Even terms: ");
int count=0;
for(int i=0;count<n;i+=2)
{
printf("%d ",i);
count++;
}
printf("\n");

}
else if(pid>0)
{
wait(NULL);
printf("Odd terms: ");
int count=0;
for(int i=1;count<n;i+=2)
{
printf("%d ",i);
count++;
}
printf("\n");



}

}
