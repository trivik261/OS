#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

#define read_end 0
#define write_end 1

int pipe1[2],pipe2[2];
int pipe3[2],pipe4[2],pipe5[2],pipe6[2];
int status1,status2;
char string1[100],string2[100],string3[100];
char user[100];
char pass[100];


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
       
        
        strcpy(string1,"Testing");
        printf("String Set by Parent:%s\n",string1);

        memset(string2,0,sizeof(string2));

        read(pipe2[read_end],string2,sizeof(string2));

        if(strcmp(string2,"Testing--Client")==0)
        strcpy(string3,"on");

        write(pipe1[write_end],string3,sizeof(string3)+1);

       

       

       close(pipe3[write_end]);
       close(pipe4[write_end]);
       close(pipe5[read_end]);
       close(pipe6[write_end]);

       read(pipe3[read_end],string1,sizeof(string1));
       read(pipe4[read_end],string2,sizeof(string2));

       printf("%s\n",string1);
       printf("%s\n",string2);

       if((strcmp(string1,"123")==0) && (strcmp(string2,"123")==0))
            {
                strcpy(string3,"correct");
                
            }
        else
        {
            strcpy(string3,"Unsuccessful Login");
            
        }
        
        write(pipe5[write_end],string3,sizeof(string3)+1);
        if(strcmp(string3,"correct")!=0)
            exit(0);

        int *ch;
        read(pipe6[read_end],ch,sizeof(ch));
        printf("%d",*ch);

       
    }
    else
    {

       close(pipe1[write_end]); 
       close(pipe2[read_end]);

       strcpy(string2,"Testing--Client"); 
       printf("String Set by Child:%s\n",string2);

       write(pipe2[write_end],string2,sizeof(string2)+1);

       read(pipe1[read_end],string3,sizeof(string3));

       if(strcmp(string3,"on")==0)
       printf("Server-On\n");
       else
       {
           printf("Server-off\n");
           exit(0);
       }

       close(pipe3[read_end]);
       close(pipe4[read_end]);
       close(pipe5[write_end]);

      
       
        write(pipe3[write_end],string1,sizeof(string1)+1);
        write(pipe4[write_end],string2,sizeof(string2)+1);


       read(pipe5[read_end],string3,sizeof(string3));

       if(strcmp(string3,"correct")!=0)
            {
                printf("Invalid Login!! Exiting Program\n");
                exit(0);
            }
        printf("Login Successful\n");
        int ch=0;
       printf("Enter ch:0 for sending file and 1 for receving file:\n");
       scanf("%d",&ch); 
        while(ch!=0 && ch!=1)
        {
            printf("Invalid Choice,Enter again:\n");
       scanf("%d",&ch); 
        }

      write(pipe6[write_end],&ch,sizeof(ch));




       

       
       
       
    }

}
void pre_process()
{
    status1=pipe(pipe1);
    status2=pipe(pipe2);
    pipe(pipe3);
       pipe(pipe4);
       pipe(pipe5);
       pipe(pipe6);
    error_print(status1,status2);
    process();
}

int main()
{
    pre_process();
    return 0;
}
