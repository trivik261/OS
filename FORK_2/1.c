#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include<time.h>

void orphan()
{
    pid_t pid;
    pid=fork();

    if(pid==0)
    {
        sleep(2);
        printf("\nOrphan Child Process Process!!!\n");
        sleep(3);
        _exit(0);
        

    }
    else
    {
        printf("Parent Process has been executed!!!\n");
        
        
    }
}
void zombie()
{
    pid_t pid;
    pid=fork();

    if(pid==0)
    {
        printf("Zombie Process!!!\n");
        _exit(0);
        

    }
    else
    {
        sleep(5);
        printf("Parent Process slept for 5 seconds!!!\n");
        
        
    }
}

int main()
{
    
    printf("Zombie Process Simulation:\n");
    zombie();

    printf("\nOrphan Process Simulation:\n");
    orphan();            
     
    
    return 0;
}