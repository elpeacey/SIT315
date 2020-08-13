#include <random>
#include <sys/time.h>
#include <pthread.h> 

using namespace std;

#define N 100000  
int array[N];
int THREADS = 8;
int val;
int step = 0;

//Initialise array with random values
void initialiseArray(int array[N])
{
	srand (time(NULL));
	printf("Using Array of size: %d", N);
	printf("\nInitialising Array... ");
	for (int i = 0 ; i < N; i++){
		array[i] = rand() % ((100 - 1) + 1) + 1;
	}
	printf("Complete");

}		

//void printArray(int array[LENGTH]){
//	cout<<"[";
//	for (int i = 0 ; i < LENGTH ; i++){
//		printf(array[i], ", ");
//	}
//	printf("]\n");
//}			

int part(int array[], int start, int end) 
{
    int pivot = array[end];
    int index = start;
    int temp;
 
    for(int i = start; i < end; i++)
    {
        if(array[i] <= pivot)
        {
            temp = array[i];
            array[i] = array[index];
            array[index] = temp;
            index++;
        }
    }

    temp = array[end];
    array[end] = array[index];
    array[index] = temp;

    return index;
}

void quickSort(int array[], int start, int end)
{
    if(start < end)
    {
        int element = part(array, start, end);
        quickSort(array, start, element - 1);
        quickSort(array, element + 1, end);
    }
}

void* threadedQuickSort(void *threadid)
{
	long num = step++;
	
 	int start = num * N/THREADS;
 	int end = start + N/THREADS - 1;

    if(start < end)
    {
        int element = part(array, start, end);
        quickSort(array, start, element - 1);
        quickSort(array, element + 1, end);
    }

    return 0;
}


void pthreadQS()
{
	pthread_t threads[THREADS];

    int p = part(array, 0, N - 1);			

    for (long num = 0; num < THREADS; num++) 
    { 
        int* k; 
        pthread_create(&threads[num], NULL, threadedQuickSort, (void*)(k)); 
    } 

    for (long num = 0; num < THREADS; num++) 
        pthread_join(threads[num], NULL); 
}		

int main(int argc, char *argv[])
{
	struct timeval timecheck;

	initialiseArray(array);

	printf("\nSequential QuickSort Processing Time: ");

	gettimeofday(&timecheck, NULL);

	long startTime = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec /1000;

	quickSort(array, 0, N - 1);

	gettimeofday(&timecheck, NULL);
	long endTime = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec /1000;

	long elapsedTime = endTime - startTime;
	printf("%d ms \n", elapsedTime);

	
	initialiseArray(array);

	printf("\npthread QuickSort Processing Time: ");

	gettimeofday(&timecheck, NULL);

	startTime = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec /1000;

	pthreadQS();
	

	gettimeofday(&timecheck, NULL);
	endTime = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec /1000;

	elapsedTime = endTime - startTime;
	printf("%d ms", elapsedTime);

	return 0;
}
