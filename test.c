#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"
#include <string.h>

int main(){
	
	init();

	char* test = malloc(4);
	strcpy(test, "ok");


	char* test2 = malloc(4);
//	strcpy(test2, "lol");

	
	printH();


	int a = 4;
	int b = 1;
	int c = ((a) | (b));

//	printf("c: %d\n", c);
//	printf("alloc: %d\n", (c & 0x1));
//	printf("size: %d\n", (c & (~0x3)));

	
	return 0;

}

