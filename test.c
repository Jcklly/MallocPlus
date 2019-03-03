#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"
#include <string.h>

int main(){
	
//	char* test = malloc(4);
//	strcpy(test, "ok");

//	char* test2 = malloc(16);
//	strcpy(test2, "test test testy");

//	char* test3 = malloc(4);
//	strcpy(test3, "lol");



//	printf("%c\n", test2[10]);
		
//	printP();


	int a = 16;
	int b = 1;
	int c = ((a) | (b));

	printf("c: %d\n", c);
	printf("alloc: %d\n", (c & 0x1));
	printf("size: %d\n", (c & (~0x3)));

	
	return 0;

}

