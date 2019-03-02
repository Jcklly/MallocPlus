#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"


int main(){
	
//	init();

	size_t a = 10;
	int* test = malloc(a);
	
	printH();


/*
	int a = 3636;
	int b = 1;
	int c = ((a) | (b));

	printf("%d\n", c);
	printf("alloc: %d\n", (c & 0x1));
	printf("size: %d\n", (c & (~0x3)));
*/
	
	return 0;

}

