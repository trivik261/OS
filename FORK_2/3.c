#include<stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <unistd.h> 
int main() 
{ 
	long long int i=0;
	int x=getpid();
	
	while(fork()>0)
		i++;
	
	if(getpid() == x)
		printf("Maximum fork count: %lld\n",i);

	return 0; 
} 

