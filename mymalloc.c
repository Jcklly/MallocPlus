#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"

void* mymalloc(size_t s, char* file, size_t line) {
	
		// Checks if it's the first time malloc has been called.
	if(myblock[3] == '\0') {
		init();
	}

		// Base case if size given is 0.
	if(s == 0){
		return NULL;
	}

	char* ptr = &myblock[BLOCK];	
	int a = ((header*)ptr)->aSize;
	printf("SIZE: %d\n", GETS(a));


//	printf("mymalloc\n");
	return NULL;
}

void* myfree(void* p, char* file, size_t line) {

	printf("myfree\n");
	return NULL;
}

	// Initialize memory
void init() {
	
	header* head = (header*)(&myblock[BLOCK]);
	head->aSize = ((4092) | (0));


//	printf("myblock[3]: %d\n", ((header*)head)->aSize);

//	printf("HEAD: %p\n", &head->aSize);
//	printf("T: %p\n", &t->aSize);
	
}




void printH() {

	int i;
	for(i = 0; i < 100; i++) {
		printf("[ %p ]\n", &myblock[i]);
	}
	
}
