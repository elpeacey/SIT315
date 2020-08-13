#include <fstream>
#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>
#include <omp.h>

using namespace std;

#define N 1000
#define THREADNO 8

int startArrayA[N][N];
int startArrayB[N][N];
int endArray[N][N];

int step = 0;

//intialises array using random values of size N
void intialise(int array[N][N]) {
	printf("\nIntialising array... ");
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			array[i][j] = rand() % ((100 - 1) + 1) + 1;
		}
	}
	printf("complete");
}	

//multiply the matricies sequentially
void Sequential()
{
    printf("\nMatrix Multiplication... ");

	//Matrix Multiplication
	int num;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			num = 0;
			for (int k = 0; k < N; k++)
			{
				num += startArrayA[i][k] * startArrayB[k][j];
			}
			endArray[i][j] = num;

		}
	}

	printf("Complete \n");

}

//multiply matricies using threads
void* Threaded(void* arg)
{
    int num = step++; 
  
    for (int i = num * N / N; i < (num + 1) * N / N; i++)  
        for (int j = 0; j < N; j++)  
            for (int k = 0; k < N; k++)  
                endArray[i][j] += startArrayA[i][k] * startArrayB[k][j]; 

	return 0;
} 

//multiply matricies using OpenMP
void OpenMP()
{
    printf("\nOpenMP Matrix Multiplication... ");

	#pragma omp parallel
	{
		#pragma omp for
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{	
				int num = 0;
				
				for (int k = 0; k < N; k++)
				{
					num += startArrayA[i][k] * startArrayB[k][j];
				}
				endArray[i][j] = num;
			}
		}
	}
    
    printf("Complete \n");
}

int main()
{
	struct timeval timecheck;
    srand(time(NULL));
    
	printf("\nArray size (N x N) is: %d", N);
	printf("\nNumber of threads is: %d", THREADNO, "\n");
	intialise(startArrayA);
	intialise(startArrayB);

	gettimeofday(&timecheck, NULL);
	long beginTime = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec /1000; //Start timer
	Sequential();
	gettimeofday(&timecheck, NULL);       
    long endTime = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec /1000; //Timer Stops
	long elapsedTime = endTime - beginTime;

    printf("Processing Time in ms: %d", elapsedTime, "\n");

	printf("\nThreaded Matrix Multiplication...");

	gettimeofday(&timecheck, NULL);
    beginTime = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec /1000; //Timer begins

    pthread_t threads[THREADNO]; 
    
    //Creating threads
    for (int i = 0; i < THREADNO; i++) 
    { 
        int* p; 
        pthread_create(&threads[i], NULL, Threaded, (void*)(p)); 
    } 
  
    //Joining threads
    for (int i = 0; i < THREADNO; i++)  
        pthread_join(threads[i], NULL);     
    
	gettimeofday(&timecheck, NULL);
    endTime = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec /1000;
    printf("Complete \n");

    elapsedTime = endTime - beginTime;

    printf("Processing Time in ms: %d", elapsedTime);

	gettimeofday(&timecheck, NULL);
	beginTime = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec /1000; //Start timer
	OpenMP();
	gettimeofday(&timecheck, NULL);       
    endTime = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec /1000; //Timer Stops
	elapsedTime = endTime - beginTime;

    printf("Processing Time in ms: %d", elapsedTime);

	return 0;
}