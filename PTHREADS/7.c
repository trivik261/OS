#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <limits.h>
#define MAX_TH 16
#define SQUARE_PTS 10000000

float randomGen()
{
	int x = rand();
	float y = x / (float)RAND_MAX;
	return y;
}

void *process(void *threadid)
{
	
	long longTid = (long)threadid;

	int tid = (int)longTid;

	float *circle_pts = (float *)malloc(sizeof(float));
	*circle_pts = 0;

	float total_iterations = SQUARE_PTS / MAX_TH;

	

	for (int i = 0; i < total_iterations; i++)
	{
		float x = randomGen();
		float y = randomGen();

		float result = sqrt((x * x) + (y * y));

		if (result < 1)
		{
			
			*circle_pts += 1;
		}
	}

	
	if (tid == 0)
	{
		float remainder = SQUARE_PTS % MAX_TH;

		for (int i = 0; i < remainder; i++)
		{
			float x = randomGen();
			float y = randomGen();

			float result = sqrt((x * x) + (y * y));

			if (result < 1)
			{
				
				*circle_pts += 1;
			}
		}
	}
	pthread_exit((void *)circle_pts); 
}

int main(int argc, char *argv[])
{
	pthread_t pth[MAX_TH];
	int rc;
	void *status;
	float tot_in = 0;

	for (long int t = 0; t < MAX_TH; t++)
	{
		rc = pthread_create(&pth[t], NULL, process, (void *)t);
		if (rc>0)
		{
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			exit(-1);
		}
	}

	for (long int t = 0; t < MAX_TH; t++)
	{
		pthread_join(pth[t], &status);
		tot_in += *(float *)status; 
	}
	printf("Value for Pi is %f \n", 4 * (tot_in / SQUARE_PTS));
	pthread_exit(NULL);
}
