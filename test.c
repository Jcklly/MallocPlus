#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"
#include <string.h>
#include <time.h>


int main(){
	
	char* test = (char*)malloc(4);

	if(test != NULL) {
		strcpy(test, "ok");
	} else {	
		printf("test = NULL\n");
	}

	char* test2 = malloc(14);
	if(test2 != NULL) {
		strcpy(test2, "testing");
	} else {
		printf("test2 = NULL\n");
	}

	char* test3 = malloc(4);
	if(test3 != NULL) {
		strcpy(test3, "lol");
	} else {
		printf("test3 = NULL\n");
	}

	char* test4 = malloc(3);
	if(test4 != NULL) {
		strcpy(test4, "hm");
	} else {
		printf("test4 = NULL\n");
	}		


	printP();


		// Testing free().
	free(test);
	free(test2);
	free(test3);
	free(test4);
		
	int * x;
	free(x);
	printf("\n\n\n");

	printP();
	
//	char* b = malloc(4);
//	strcpy(b, "oka");	
//	printP();	
//	free(b);

//	char* b = malloc(16);
//	strcpy(b, "yes yes yes yes");


//	char* a = malloc(1);
//	free(a);
//	a = malloc(1);
//	strcpy(a, "ok");

//	printf("\n\n\n");
//	printP();


/*
	int a = 4;
	int b = 6 | 1;
	int c = ((a) | (b));

	printf("c: %d\n", c);
	printf("alloc: %d\n", (a & ~0x1));
	printf("size: %d\n", (b & (~0x1)));




//	short n = 4088;
//	printf("size_t: %d\n", sizeof(n));
*/

/*
struct timeval tv, tz;

double array[100];
int i = 0;
int j = 0;
double time;
char* test1;

//for(i = 0; i < 100; i++) {
while(i < 100) {
	j = 0;
	gettimeofday(&tv, NULL);
//	for(j = 0; j < 150; j++) {
	while(j < 150) {	
		test1 = malloc(1);
		free(test1);
		++j;	
	}
	gettimeofday(&tz, NULL);
	
//	printf("Total: %f\n", (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 + (double) (tv2.tv_sec - tv1.tv_sec) );
	time = (double)(tz.tv_usec - tv.tv_usec) / 1000000 + (double)(tz.tv_sec - tv.tv_sec);
	printf("Time[%d]: %f\n", i, time);
	array[i] = time;	
	++i;
}

double average = 0.0;
i = 0;
while(i < 100) {
average = average + array[i];
++i;
}
average = (double)average/100;

printf("Average: %f\n", average*1000000);


*/
	
	return 0;

}

