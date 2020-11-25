#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include<math.h>
int de_sum(int n)
{
int size=log10(n);

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

return sum;
}
 
int main()
{
int a,b;
printf("Enter a  and  b\n");
scanf("%d %d",&a ,&b);
printf("Output\n");
int count=0;
for(int i=a;i<=b;i++)
{ 
int result;
pid_t pid1;
pid1=vfork();
if(pid1==0)
{

result=de_sum(i);
exit(0);
}
else
{
wait(NULL);
if(result==i) 
{printf("%d is an armstrong number\n",i); count++;}



}

}
if(count==0)
printf("No Armstrong Number in this range:!!!\n");
return 0;
}


