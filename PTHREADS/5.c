#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include<math.h>
#include<pthread.h>
#include<string.h>

struct node
{
    int *elements;
    float mean;
    float median;
    int mode;
    int size;
};

void swap(int *p,int *q)
{
int temp=*p;
*p=*q;
*q=temp;

}
void bubblesort(int a[],int ch,int size)
{


for(int i=0;i<size-1;i++)
{
for(int j=0;j<size-i-1;j++)
{
    int choice=(ch==0)?(a[j]<a[j+1]):(a[j]>a[j+1]);
    if(choice==1)   
    {
        swap(&a[j],&a[j+1]);

    }
}
}
}

void *mean(void *arg)
{
    int sum=0;
    struct node *temp=((struct node*)arg);
    for(int i=0;i<temp->size;i++)
    {
        sum+=temp->elements[i];
    }
    temp->mean=float(sum)/float(temp->size);

    pthread_exit(NULL);
}

void *median(void *arg)
{
    struct node *temp=((struct node*)arg);
    int *a=temp->elements;
    bubblesort(a,1,temp->size);
    if(temp->size%2==0)
    {
        temp->median=((float)a[temp->size/2]+(float)a[(temp->size-1)/2])/2;
    }
    else
        temp->median=a[temp->size/2];
    
    pthread_exit(NULL);
}
int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

void *mode(void *arg)
{
    struct node *temp=((struct node*)arg);
    int *a=temp->elements;

    qsort(a,temp->size,sizeof(int),cmpfunc);
    int count1=1,count2=1;
    int i=0,index=1;
    int mo=a[0];
    
    for(i=0;i<temp->size;i++)
    {
        if(a[i]==a[i+1])
        {   
            while(a[i]==a[i+1])
            {
                count1++;
                i++;
            }
            if(count1>count2)
            {
                count2=count1;
                mo=a[i];
                count1=1;
            }
        }
           

    }
    temp->mode=mo;

    pthread_exit( NULL );
}


void process(struct node * temp)
{
    pthread_t pth[3];

    pthread_create(&pth[0],NULL,mean,temp);
    pthread_create(&pth[1],NULL,median,temp);
    pthread_create(&pth[2],NULL,mode,temp);
    
    for(int i=0;i<3;i++)
    pthread_join(pth[i],NULL);
    

    

    printf("\nMean=%f Median=%f Mode=%d\n",temp->mean,temp->median,temp->mode);

}

int main()
{
    struct node *result=(struct node*)malloc(sizeof(struct node));
    printf("Enter the no of elements:\n");
    scanf("%d",&result->size);
    result->elements=new int[result->size];

    printf("Enter the elements:\n");
    for(int i=0;i<result->size;i++)
    {
        scanf("%d",&result->elements[i]);
    }

    process(result);
    
    
    return 0;


}