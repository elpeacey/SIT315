#include <iostream>
#include <time.h>
#include <thread>
#include <stdlib.h>
#include <omp.h>

using namespace std;

#define N 1000

const int MAX = 8;

int startArrayA[N][N];
int startArrayB[N][N];
int endArray[N][N];
thread T[N];

//intialises array using random values of size N
void intialise(int array[N][N]) {
	cout<<"intialising array... ";
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			array[i][j] = rand() % ((100 - 1) + 1) + 1;
		}
	}
	cout<<"complete"<<endl;
}	

//print array to the console
void print(int array[N][N]){
	cout <<"[";
	for (int i = 0; i < N; i++) {
		cout << "[";
		for (int j = 0; j < N; j++) {
			cout << array[i][j];
			std::cout << " ";
		}
		std::cout << "]\n";
	}
	std::cout << "]\n\n";
}		

//multiply the matricies sequentially
void Sequential()
{
    cout << "Matrix Multiplication... ";

	clock_t beginTime = clock(); //Start timer

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

	clock_t endTime = clock(); //End timer

	cout << "Complete" << endl;

	double elapsedTime = double(endTime - beginTime)/ CLOCKS_PER_SEC;

	cout << "Processing Time: " << elapsedTime << " secs" << endl;
	cout << " " << endl;
}

//multiply matricies using threads
void *Threaded(void* arg)
{
    int num = 0; 
  
    for (int i = num * N / MAX; i < (num + 1) * N / MAX; i++)  
        for (int j = 0; j < N; j++)  
            for (int k = 0; k < N; k++)  
                endArray[i][j] += startArrayA[i][k] * startArrayB[k][j];
    
}

void OpenMP()
{
    cout<<"OpenMP Matrix Multiplication with " << MAX << " threads... ";
	clock_t beginTime = clock(); //Start timer

    //Matrix Multiplication using OpenMP parallel for loop
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
    
    clock_t endTime = clock(); //Timer Stops

    cout << "Complete" << endl;

    double timeElapsed = double(endTime - beginTime) / CLOCKS_PER_SEC;

    cout << "Processing Time: " << timeElapsed << " secs" << endl;
    cout << " " << endl;

}

int main()
{
    srand(time(NULL));
    
	cout<<"Array size (N x N) is: "<<N<<endl;
	intialise(startArrayA);
	intialise(startArrayB);

	Sequential();

	cout << "Threaded Matrix Multiplication...";

    clock_t beginTime = clock(); //Timer begins

    pthread_t threads[MAX]; 
  
    for (int i = 0; i < MAX; i++) { 
        int* k;
        pthread_create(&threads[i], NULL, Threaded, (void *)(k)); 
    } 
  
    // joining and waiting for all threads to complete 
    for (int i = 0; i < MAX; i++)  
        pthread_join(threads[i], NULL);   

    clock_t endTime = clock();//Stopping the timer
    cout << "Complete" << endl;

    double elapsedTime = double(endTime - beginTime) / CLOCKS_PER_SEC;

    cout << "Processing Time: " << elapsedTime << " secs" << endl;
    cout << " " << endl;

	OpenMP();

	return 0;
}
