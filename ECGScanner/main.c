#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "globals.h"
#include "sensor.h"
#include "filter.h"
#include "utils.h"
#include "test.h"
#include <omp.h>
#define MAX_FILE_NAME  100


int fsize() {
	FILE* fp;
	int count = 0;  // Line counter (result) 
	char filename[MAX_FILE_NAME];
	char c;
	fp = fopen(GLOBAL_SENSOR_INPUT, "r");
	if (fp == NULL)
	{
		printf("Could not open file %s", filename);
		return 0;
	}

	for (c = getc(fp); c != EOF; c = getc(fp))
		if (c == '\n')
			count = count + 1;

	// Close the file 
	fclose(fp);
	return count + 1;
}


//Main program
int main(void)
{
	
	int sizeoffile = fsize();
	//Loop that holds program alive
	//as long as the sensor is getting data
	double start = omp_get_wtime();
	printf("RUN\n");
	int i;
#pragma omp parallel for num_threads(4) schedule(guided)
	for (i = 0; i < sizeoffile; i++)
	{
		//Next value from the sensor
		int next = getNextData();
#pragma omp critical
		{
			//Data after filtering
			int filteret = filter(next);
			//Detection function - returns 1 if Rpeak detected
			int detected = detection(filteret);
			//Increment global count variable
			global_count();
		}
	}
	double end = omp_get_wtime();
	printf("Execution time = %f", end - start);
	printf("\n Number of Frequencies Scanned : %d", sizeoffile);
	getchar();
	return 0;
}
