#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

#define read_end 0
#define write_end 1

int pipe1[2],pipe2[2];
int status1,status2;
char string1[100],string2[100],string3[100];

void error_print(int status1,int status2)
{
    if(status1==-1)
    {
        printf("Pipe1 Failed!!!!\n");
    }
    if(status2==-1)
    {
        printf("Pipe2 Failed!!!!\n");
    }

}
void process()
{
    pid_t pid=fork();
    if(pid>0)
    {
        close(pipe1[read_end]);
        close(pipe2[write_end]);
        printf("\n-------------------------Parent Process--------------------\n");
        printf("Enter the String(less than length 100):\n");
        scanf("%[^\n]*c",string1);
        getchar();

        memset(string2,0,sizeof(string2));
        printf("String Sent to Child To Reverse!\n");
        write(pipe1[write_end],string1,sizeof(string1)+1);

        read(pipe2[read_end],string2,sizeof(string2));

        printf("String After Reversed:%s\n\n",string2);

    }
    else
    {

       close(pipe1[write_end]); 
       close(pipe2[read_end]);

       read(pipe1[read_end],string3,sizeof(string3));
       printf("\n-------------------------Child Process--------------------\n");
       printf("String Received to be Reversed:");
       printf("%s\n",string3);
       char temp;
       int size=strlen(string3);
       for(int j=0;j<size/2;j++)
       {
           
           temp=string3[j];
           string3[j]=string3[size-1-j];
           string3[size-1-j]=temp;
          
       }
       write(pipe2[write_end],string3,sizeof(string3)+1);
       printf("Reversed String Sent Successfully to Parent!\n");
       printf("-------------------------End of Child Process--------------------\n\n");

    }

}
void pre_process()
{
    status1=pipe(pipe1);
    status2=pipe(pipe2);
    error_print(status1,status2);
    process();
}

int main()
{
    pre_process();
    return 0;
}
