#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"

void* mymalloc(size_t s, char* file, size_t line) {
	
		// Checks if it's the first time malloc has been called.		
	

	if(((header*)&myblock[0])->aSize <= 0) {
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
	int i = 0;


//	ptr = &myblock[i];
//	sizeT = ((header*)ptr)->aSize;
//	printf("%d\n", sizeT);	


	while(i < 500) {
			// Takes the total size from header and breaks it down to allocate size and the bit.
			// If bit is 0, then the space is free, otherwise it is taken.
		ptr = &myblock[i];
		sizeT = ((header*)ptr) -> aSize;
		sizeA = GETS(sizeT);
		bit = GETA(sizeT);
		

//		printf("%d\n", i);

		if(s == 1 || s == 2 || s == 3) {
			s = 4;
		}	

		reSize = padding((int)s);	
		if((bit == 0) && (sizeA >= (int)reSize)) {
			rPtr = &myblock[i + 4];


//			printf("%d\n", ((header*)ptr)->aSize);
//			printf("reSize: %d\n", reSize);
			((header*)ptr)->aSize = (reSize | 1);

//			printf("%d\n", ((header*)ptr)->aSize);
//			printf("reSize: %d\n", reSize);

			newSize = sizeA - reSize;	
			header* head = (header*)(&myblock[i + reSize + 4]);
			head->aSize = ((newSize) | (0));
	
			break;
			
		} else {
//			printf("bit: %d\n", bit);
//			printf("sizeA: %d\n", sizeA);
//			printf("reSize: %d\n", reSize);
		
//			printf("else: \n");
			i = 4 + sizeA;
		}



	}



//	printf("SIZE: %d\n", GETS(a));
//	printf("%p\n", &((header*)ptr)->aSize);	


	return rPtr;
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
	
/*
	int i = 0;
	while(i < 4088) {
		myblock[i] = '0';
		++i;
	}
*/

	header* head = (header*)(&myblock[0]);
	head->aSize = ((4092) | (0));


//	printf("myblock[3]: %d\n", ((header*)head)->aSize);

//	printf("HEAD: %p\n", &head->aSize);
//	printf("T: %p\n", &t->aSize);
	
}

void printP() {

	char* ptr = &myblock[0];
	
	int i = 0;

//		printf("[ %d ]\n", GETS(((header*)ptr)->aSize));
	for(i = 0; i < 50; i++) {				
	ptr = &myblock[i];
		printf("[ %d ]\n", GETS(((header*)ptr)->aSize));
	}

}


void printH() {

	int i;
	for(i = 0; i < 100; i++) {
		printf("[ %c ]\n", myblock[i]);
	}
	
}
