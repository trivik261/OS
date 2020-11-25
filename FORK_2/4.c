#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<wait.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>

  char history[100][100];
  char pwd[1000];
  int ind;


void get_pwd()
{
   if(getcwd(pwd,sizeof(pwd))==NULL)
    {
        perror("getcwd() error");
    }
}

void print()
{
    

if(strcmp(history[ind],"history")==0)
    {

        for(int i=0;i<=ind;i++)
            printf("%s\n",history[i]);

        printf("\n");
    }
else if(history[ind][0]=='!')
    {
        ind-=1;
        int i=(int)history[ind][1];
        int j=ind;
        while(i!=0 && j>=0)
        {
            printf("%s\n",history[j]);

            j--;
            i--;
        }
    }
else if(strcmp(history[ind],"exit")==0)
{

    exit(0);

}

else 
{
    
char args[10][100]={0};
int no=0,k=0;



for(int i=0;i<strlen(history[ind]);i++)
{
    if(history[ind][i]!=' ')
        args[no][k]=history[ind][i];
    else
    {
        no++;
        k=-1;
    }
    k++;
    
}
no+=1;




char * cmd[no+1];
for(int i=0;i<=no;i++)
    {
        cmd[i]=args[i];
    }
cmd[no]=NULL;

if(strcmp(args[0],"cd")==0)
    {
        chdir(args[1]);
        return;
    }




pid_t pid=fork();

if(pid==-1)
   {
            printf("Unsuccessful Fork Call!!!\n");
   }
else if(pid==0)
     {       
        if(execvp(*cmd,cmd)==-1)
            printf("Exec Unsuccessful!!\n");
        exit(0);
        
    }
else
{
   
    wait(NULL);
    printf("\n");

}

    
}



    


    
}



int main()
{

  
    


 printf("-----------------------------------Virtual Shell(Press exit to close the shell)-----------------------------------:\n\n");


 while(ind<=100)
 {
     printf("Virtual_Shell:~");
     get_pwd();
     printf("%s@ ",pwd);
  //   printf("%d\n",ind);
     
     scanf("%[^\n]s",history[ind]);
     getchar();
   //  printf("%s",history[ind]);
     
     print();
     ind+=1;
     

}
    
return 0;
}