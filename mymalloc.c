#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"

/*	-- TO DO --
 *	1.) find way to have malloc work without i < 500. Need a way to know if it reaches the end.
 *	    Maybe add final footer to the end of the array?
 *	2.) myfree(). Given a memory address, simply go there and if there is something allocated free it. If not then...
 *	    After every free, coalesce.
 *	3.) coalescing(). After every every free, go through and see if there are any free chucks next to eachother.
 *	    If there are, then combine them into 1.  
 *	4.) Memgrind(). Should be simple enough program to code.
*/



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
	int sizeT, sizeA, bit, reSize, newSize, i;
	sizeT = sizeA = bit = reSize = newSize = i = 0;

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
		
			// if space is enough and is not allocated, set current head size to size of allocated, and turn
			// bit to 1. Then create a new header in front of newly allocated spot with updated info.
		reSize = padding((int)s);	
		if((bit == 0) && (sizeA >= (int)reSize)) {
			
			rPtr = &myblock[i + 4];
			((header*)ptr)->aSize = (reSize | 1);
			newSize = sizeA - reSize;
			if( ((header*)&myblock[i + reSize + 4])->aSize <= 0  ) {
	
				header* head = (header*)(&myblock[i + reSize + 4]);
				head->aSize = ((newSize) | (0));
		
			}
			break;
			
		} else {
			i = i + 4 + sizeA;
		}
	}

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

	printf("free: %p\n", p);
	return NULL;
}

	// Initialize memory
void init() {

	header* head = (header*)(&myblock[0]);
	head->aSize = ((4092) | (0));
	
}

void printP() {

	char* ptr = &myblock[0];

	int i = 0;
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
