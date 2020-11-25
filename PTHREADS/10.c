#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include<math.h>
#include<pthread.h>
#include<string.h>

struct node
{
    int n1;
    int n2;
    int count;
};

//global variables
//to store strings
char a[10000],b[10000];
//to store longest common subsequence
int dp[10000][10000];

//function declarations
struct node* create(int ,int );
int max(int,int);
int subfunc(struct node *temp1,struct node *temp2);
int lcs(int ,int);
void* process(void *);

//function definitions

struct node* create(int n1,int n2)
{
    node *temp =new node();
    temp->n1=n1;
    temp->n2=n2;
    temp->count=0;
    return temp;
}

int max(int x,int y)
{
    return  (x>y)?(x):(y);
}

int subfunc(struct node *temp1,struct node *temp2)
{
    pthread_t *pth=(pthread_t*)malloc(2*sizeof(pthread_t));
    pthread_create(&pth[0],NULL,process,temp1);
    pthread_create(&pth[1],NULL,process,temp2);
    pthread_join(pth[0],NULL);
    pthread_join(pth[1],NULL);
    
return max(temp1->count,temp2->count);
}

int lcs(int n1,int n2)
{   
    if(dp[n1][n2]!=-1)
    return dp[n1][n2];

    int status=0;
    if(a[n1]=='\0'|| b[n2]=='\0')
    dp[n1][n2]=0;
    else if(a[n1]==b[n2])
    dp[n1][n2]=1+lcs(n1+1,n2+1);
    else
    {
    struct node *temp1=create(n1+1,n2);
    struct node *temp2=create(n1,n2+1);  

    dp[n1][n2]=subfunc(temp1,temp2);

    }
    return dp[n1][n2];
}

void* process(void *arg)
{
    struct node *temp=(struct node*)arg;
    
    int n1=temp->n1;
    int n2=temp->n2;
    temp->count=lcs(n1,n2);

    pthread_exit(NULL);
}

int main()
{
    
    memset(&dp,-1,sizeof(dp));
    int n1,n2;
    printf("Enter the size of string1 and string 2:\n");
    scanf("%d %d",&n1,&n2);

    struct node *lc=create(0,0);

    printf("Enter String1 and String2:\n");
    scanf("%s %s",a,b);

    pthread_t *pth=(pthread_t*)malloc(sizeof(pthread_t));
   

    pthread_create(pth,NULL,process,lc);
    pthread_join(*pth,NULL);

    printf("\nLongest Common Subsequence:%d\n",lc->count);

return 0;
}