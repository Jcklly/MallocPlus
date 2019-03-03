#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"

void* mymalloc(size_t s, char* file, size_t line) {
	
		// Checks if it's the first time malloc has been called.
	if(myblock[4] == '\0') {
		init();
	}

		// Base case if size given is 0.
	if(s == 0){
		return NULL;
	}

	char* ptr;
	void* rPtr;
	int sizeT = 0;

	int sizeA = 0;
	int bit = 0;
	int reSize = 0;
	int newSize = 0;
	int i = BLOCK;

	while(i < 500) {
			// Takes the total size from header and breaks it down to allocate size and the bit.
			// If bit is 0, then the space is free, otherwise it is taken.
		ptr = &myblock[i];
		sizeT = ((header*)ptr) -> aSize;
		sizeA = GETS(sizeT);
		bit = GETA(sizeT);
		

		if(s == 1 || s == 2 || s == 3) {
			s = 4;
		}	

	
		if((bit == 0) && (sizeA >= (int)s)) {
			rPtr = &myblock[i + 1];
			reSize =  padding((int)s);



//			printf("%d\n", ((header*)ptr)->aSize);
//			printf("reSize: %d\n", reSize);
			((header*)ptr)->aSize = (reSize | 1);

//			printf("%d\n", ((header*)ptr)->aSize);

			newSize = sizeA - reSize;	
			header* head = (header*)(&myblock[reSize + 1]);
			head->aSize = ((newSize) | (0));
			return rPtr;
			
		} else {
			i += sizeA;
		}



	}



//	printf("SIZE: %d\n", GETS(a));
//	printf("%p\n", &((header*)ptr)->aSize);	


	return NULL;
}



int padding(int a) {
	int pad = 0;
	int div = a;
	
	while((div % 4) != 0) {
		++pad;
		div += pad;
		
	}

	return div;
}


void* myfree(void* p, char* file, size_t line) {

	printf("myfree\n");
	return NULL;
}

	// Initialize memory
void init() {
	

	int i = 0;
	while(i < 4088) {
		myblock[i] = '0';
		++i;
	}


	header* head = (header*)(&myblock[BLOCK]);
	head->aSize = ((4092) | (0));


//	printf("myblock[3]: %d\n", ((header*)head)->aSize);

//	printf("HEAD: %p\n", &head->aSize);
//	printf("T: %p\n", &t->aSize);
	
}




void printH() {

	int i;
	for(i = 0; i < 100; i++) {
		printf("[ %c ]\n", myblock[i]);
	}
	
}
