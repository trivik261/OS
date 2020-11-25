#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include<time.h>

void countstr(char string[],char c,int size,int freq[],int index)
{
    for(int i=0;i<size;i++)
        if(string[i]==c)
            freq[index]+=1;
    
}

int main()
{
    int n;
    pid_t pid;
    printf("Enter the n value\n");
    scanf("%d",&n);

    char string1[n+1];

    int heap[128];
      for(int i=0;i<128;i++)
        heap[i]=0;


    printf("Enter the String:\n");

  

    int count=0;
    int index=0;

    scanf("%s",string1);


    for(int i=0;i<n;i++)
         {
             
             
             int ind=(int)string1[i];
            if(heap[ind]!=1)
            {
                
                 heap[ind]=1;

                 count++;
            }
            
         }
       
   char ll[count];

    
   for(int i=0;i<128;i++)
        if(heap[i]==1)
           {
               ll[index++]=i;
                
           } 

    int freq[count];
    int status;
    
    for(int i=0;i<count;i+=2)
        {
            pid=vfork();
            if(pid==0)
            {
                freq[i]=0;
                countstr(string1,ll[i],n,freq,i);
                _exit(0);
            }
            else
            {
                freq[i+1]=0;
               countstr(string1,ll[i+1],n,freq,i+1);
            }
            

        }
    waitpid(-1,&status,0);
    printf("\nHistogram:\n");
    printf("Count/String:\t");
    for(int i=0;i<count;i++)
        {   
            printf("%c\t",ll[i]);
        }
    printf("\n");
    int co=0;
    int flag=0;
    do {
        printf("\t%d",(++co));
        flag=0;
    for(int i=0;i<count;i++)
        {
            printf("\t");
            if(freq[i]>0)
            {
                freq[i]-=1;
                printf("*");
                if(freq[i]>0)
                flag=1;
            }
        }
        printf("\n");
    }while(flag!=0);
}