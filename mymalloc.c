#include <stdlib.h>
#include <stdio.h>

void* mymalloc(size_t s, char* file, size_t line) {
	

	printf("mymalloc\n");
	return NULL;
}

void* myfree(void* p, char* file, size_t line) {

	printf("myfree\n");
	return NULL;
}
