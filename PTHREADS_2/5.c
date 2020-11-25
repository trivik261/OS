#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include<math.h>
#include<pthread.h>

int count=0;


void* de_sum(void *arg)
{
int n=*((int*)arg);
int size=log10(n);

int num=n;

int digits[size];

int sum=0;
int expo=0;
while(n!=0)
{
digits[expo]=n%10;
n/=10;
expo++;
}

for(int i=0;i<expo;i++)
sum+=pow(digits[i],expo);

if(num==sum)
{
    printf("%d ",sum);
    count++;
}
pthread_exit(NULL);
}
 
int main()
{
int a,b;

printf("Enter a  and  b\n");
scanf("%d %d",&a ,&b);
printf("\nArmstrong Numbers between %d and %d:\n",a,b);
pthread_t pth[b-a+1];

for(int i=a;i<=b;i++)
{ 
if(i<=9)
printf("%d ",i);
else
pthread_create(&pth[i-a],NULL,de_sum,&i);

}
//wait for all pid to complete
for(int i=a;i<=b;i++)
if(i>9)
pthread_join(pth[i-a],NULL);

if(count==0)
printf("No Armstrong Number in this range:!!!\n");
printf("\n");
return 0;
}

