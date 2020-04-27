#include <stdio.h>
#include "globals.h"
#include "sensor.h"
#include "filter.h"
#include "utils.h"
#include "test.h"
#include <omp.h>

int GLOBAL_DEBUG = 0;
int GLOBAL_TEST = 0;
unsigned long int GLOBAL_COUNT = 0;
int GLOBAL_SAMPLE_RATE = 250;
int GLOBAL_SENSOR_ACTIVE = 1;
char GLOBAL_SENSOR_INPUT[] = "../Testfiles/ECG900K.txt";
char GLOBAL_SENSOR_INPUT_A[] = "../Testfiles/ECG.txt";

unsigned long int global_count(void) {
	return GLOBAL_COUNT++;
}

static FILE* file;
int getNextData() {
	int value;

	if (!file)
		file = fopen(GLOBAL_SENSOR_INPUT, "r");

	if (GLOBAL_SENSOR_ACTIVE = fscanf(file, "%d", &value) != EOF)
		return value;

	fclose(file);
	return 0;
}
int getNextData_A() {
	int value;

	if (!file)
		file = fopen(GLOBAL_SENSOR_INPUT_A, "r");

	if (GLOBAL_SENSOR_ACTIVE = fscanf(file, "%d", &value) != EOF)
		return value;

	fclose(file);
	return 0;
}
//Main program
int main(void)
{
	for (int i = 0; i < 900000;i++) {
		//Next value from the sensor
		int next = getNextData();
		//Data after filtering
		int filteret = filter(next);
		//Detection function - returns 1 if Rpeak detected
		int detected = detection(filteret);
		//Increment global count variable
		global_count();
	}
	printf("\nFILE 2\n");
	for (int i = 0; i < 900000; i++) {
		//Next value from the sensor
		int next = getNextData_A();
		//Data after filtering
		int filteret = filter(next);
		//Detection function - returns 1 if Rpeak detected
		int detected = detection(filteret);
		//Increment global count variable
		global_count();
	}

	if (GLOBAL_TEST) testResults(); //Print test results

	return 0;
}

