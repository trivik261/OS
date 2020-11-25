#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include<math.h>
#include<pthread.h>
struct fibo
{
    int index;
    int value;
};
int fib(int n)
{
    if(n==0 || n==1)
        return n;
    else
        return fib(n-1)+fib(n-2);
}

void* process(void *arg)
{
    struct fibo *temp=(struct fibo*)arg;
    temp->value=fib(temp->index);
    pthread_exit(NULL);
}

int main()
{
    int n;
    printf("Enter the no of terms to be generated:\n");
    scanf("%d",&n);

    struct fibo* series=(struct fibo*)malloc(n*sizeof(struct fibo));

    pthread_t pth[n];
    printf("Fibonacci Series:\n");
    for(int i=0;i<n;i++)
    {
        series[i].index=i;
        pthread_create(&pth[i],NULL,process,&series[i]);
    }
        
    for(int i=0;i<n;i++)
        {
            pthread_join(pth[i],NULL);
            printf("%d ",series[i].value);
        }
        printf("\n");
    
    return 0;
}