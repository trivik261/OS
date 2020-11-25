#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include<math.h>
#include<pthread.h>
#include<string.h>

struct node
{
    int index;
};

int pno[10000];


void* prime(void *arg)
{
    int flag=0;
    struct node *temp=((struct node*)arg);
    int n=temp->index;
    
    if(n<=1)
        flag=1;
    
    for(int i=2;i<n;i++)
    {
        if(n%i==0)
        flag=1;
    }

   if(flag!=1)
   {
       pno[n]=1;
       
   }
   pthread_exit(NULL);
}


void print(int n)
{
    struct node *p=(struct node*)malloc(n*sizeof(struct node));
    
    printf("Prime Numbers:\n");
    pthread_t pth[n+1];
    
    for(int i=0;i<=n;i++)
    {
        p[i].index=i;
        pthread_create(&pth[i],NULL,prime,&p[i]);
    }
        

    for(int i=0;i<=n;i++)
        pthread_join(pth[i],NULL);
   

    for(int i=0;i<n;i++)
    {
        if(pno[i]==1)
            printf("%d ",i);
    }
    printf("\n");
}


int main(int argc,char *argv[])
{
    if (argc != 2)
	{
		
		printf("Arguments not enough.Terminating the program!!!\n");
		exit(EXIT_FAILURE);
	}
   int n=atoi(argv[1]);
   
   
   memset(&pno,0,sizeof(pno));
    
    print(n);

    return 0;
}