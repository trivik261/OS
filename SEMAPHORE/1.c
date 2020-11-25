#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#define SHARED 1

sem_t empty,full,lock;
int data;


void *producer()
{
int p_no;

printf("\nNew Producer id :%ld\n",pthread_self()); //print thread id
for(p_no=1;p_no<7;p_no++)
{
sem_wait(&empty);
//entry-section
       sem_wait(&lock);
           //cs start
                    //assume data to the new producer no
                   data=p_no;
           //cs end
       sem_post(&lock);
//exit section
sem_post(&full);
printf("\033[1;31m");//Display in red
printf("\nProduced Data: %d\n",data);
}
}
void *consumer()
{
int c_no, total=0;

printf("\n New Consumer id : %ld\n",pthread_self());
for(c_no=1;c_no<7;c_no++)
{
sem_wait(&full);
//entry-section
       sem_wait(&lock);
              //cs start
                     total=total+data;
             //cs end
       sem_post(&lock);
//exit section
sem_post(&empty);
printf("\033[1;33m");//Display in yellow
printf("\nConsumed Data: %d\n",data);
}
printf("\nThe total Consumed Data is %d\n",total);
}

//empty to check whether buffer is empty;default 1
//full to check whether buffer is full;default 0
//lock is mutext lock;default 1

int main()
{
    pthread_t p1,c1;
    sem_init(&empty,SHARED,1);
    sem_init(&full,SHARED,0);
    sem_init(&lock,SHARED,1);

    pthread_create(&p1,NULL,producer,NULL);
    pthread_create(&c1,NULL,consumer,NULL);

    pthread_join(p1,NULL);
    pthread_join(c1,NULL);

    printf("Simulation Stopped!\n");

}