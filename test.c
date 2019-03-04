#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"
#include <string.h>

int main(){

	
	char* test = (char*)malloc(4);

	if(test != NULL) {
		strcpy(test, "ok");
	} else {	
		printf("test = NULL\n");
	}

	char* test2 = malloc(8);
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


	printH();


		// Testing free().
	free(test3);
	free(test2);
	free(test);
	
//	char* a = malloc(4);
//	strcpy(a, "noo");


//	char* b = malloc(4);
//	strcpy(b, "oka");	
	
//	free(b);

//	char* b = malloc(16);
//	strcpy(b, "yes yes yes yes");


	printf("\n\n\n");
	printH();





/*
	int a = 0;
	int b = 1;
	int c = ((a) | (b));

	printf("c: %d\n", c);
	printf("alloc: %d\n", (c & 0x1));
	printf("size: %d\n", (c & (~0x3)));
*/
	
	return 0;

}

