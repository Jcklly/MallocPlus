#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"
#include <string.h>

int main(){
	
	char* test = (char*)malloc(4);
	strcpy(test, "ok");

	char* test2 = malloc(16);
	strcpy(test2, "test test testy");

	char* test3 = malloc(4);
	strcpy(test3, "lol");

	char* test4 = malloc(3);
	strcpy(test4, "hm");

//	printf("%c\n", test2[10]);
		
	printH();

	
	
	free(test);

/*
	int a = 16;
	int b = 1;
	int c = ((a) | (b));

	printf("c: %d\n", c);
	printf("alloc: %d\n", (c & 0x1));
	printf("size: %d\n", (c & (~0x3)));

*/	
	return 0;

}

