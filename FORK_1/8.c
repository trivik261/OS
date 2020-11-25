#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
long long int fib(int n)
{

if (n==0)
return 0;
else if(n==1)
return 1;
else
{
long long int x=0,y=0;
pid_t pid;
pid=vfork();
if(pid==0)
{
x+=fib(n-2);

_exit(0);
}
else
{
y+=fib(n-1);
wait(NULL);
x+=y;

return x;

}



}


}
int main()
{
 int n;
printf("Enter n\n");
scanf("%d",&n);
printf("Series:\n");
register int i;
for(i=0;i<=n;i++)
{
printf("%lld ",fib(i));
}
printf("\n");

return 0;
}
