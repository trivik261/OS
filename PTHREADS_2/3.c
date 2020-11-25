#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

#define read_end 0
#define write_end 1

int pipe1[2],pipe2[2],pipe3[2];
int status1,status2,status3;
char string1[100],string2[100],string3[100];

void error_print(int status1,int status2,int status3)
{
    if(status1==-1)
    {
        printf("Pipe1 Failed!!!!\n");
    }
    if(status2==-1)
    {
        printf("Pipe2 Failed!!!!\n");
    }
    if(status3==-1)
    {
        printf("Pipe3 Failed!!!!\n");
    }

}
void process()
{
    pid_t pid=fork();
    if(pid>0)
    {
        close(pipe1[read_end]);
        close(pipe2[read_end]);
        close(pipe3[write_end]);

        printf("Enter the String(less than length 100):\n");
        scanf("%[^\n]*c",string1);
        getchar();
        int index[2];
        printf("Enter the start and end index for substring:\n");
        scanf("%d %d",&index[0],&index[1]);

        memset(string2,0,sizeof(string2));
        
        write(pipe1[write_end],string1,sizeof(string1)+1);
        write(pipe2[write_end],index,sizeof(index)+1);

        read(pipe3[read_end],string2,sizeof(string2));

        printf("Sub-String Generated:%s\n\n",string2);

    }
    else
    {

       close(pipe1[write_end]); 
       close(pipe2[write_end]); 
       close(pipe3[read_end]);

       read(pipe1[read_end],string3,sizeof(string3));

       int index[2];
       read(pipe2[read_end],index,sizeof(index));

       if(index[0]<0)
       index[0]=0;
       if(index[1]>=strlen(string3))
       index[1]=strlen(string3)-1;
      
       int ar_index=0;
       for(int j=index[0];j<index[1];j++)
       {
           
           string2[ar_index++]=string3[j];
          
       }
       write(pipe3[write_end],string2,sizeof(string2)+1);
       
       

    }

}
void pre_process()
{
    status1=pipe(pipe1);
    status2=pipe(pipe2);
    status3=pipe(pipe3);
    error_print(status1,status2,status3);
    process();
}

int main()
{
    pre_process();
    return 0;
}
