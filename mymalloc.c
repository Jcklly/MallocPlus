#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"

/*	-- TO DO --
 * DONE	1.) find way to have malloc work without i < 500. Need a way to know if it reaches the end.
 *	    Maybe add final footer to the end of the array?
 *
 * DONE	2.) myfree(). Given a memory address, simply go there and if there is something allocated free it. If not then...
 *	    After every free, coalesce.
 *
 * 	3.) coalescing(). After every every free, go through and see if there are any free chucks next to eachother.
 *	    If there are, then combine them into 1.  
 *
 * 	4.) Memgrind(). Should be simple enough program to code.
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
	int sizeT, sizeA, bit, reSize, newSize, i, boolean;
	sizeT = sizeA = bit = reSize = newSize = i = boolean = 0;

	while(boolean == 0) {
			// Takes the total size from header and breaks it down to allocate size and the bit.
			// If bit is 0, then the space is free, otherwise it is taken.
		ptr = &myblock[i];
		sizeT = ((header*)ptr) -> aSize;
		sizeA = GETS(sizeT);
		bit = GETA(sizeT);

		
			// Catches saturation of dynamic memory. Returns NULL. Test A for malloc.
		if( sizeA == 0 ) {
			printf("Saturation of dynamic memory.\nFile: %s\nLine: %d\n", file, line);
			boolean = 1;
			rPtr = NULL;
			break;
		}

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


void myfree(void* p, char* file, size_t line) {

	char* addr = NULL;
	int i, check1, check2;
	i = check1 = check2 = 0;
	
		// Checks if pointer was even allocated by malloc. Test A.
	addr = p - 4;
	if(((header*)addr)->aSize <= 0) { 
		check1 = 1;
	} 

		// Checks if address is even a valid pointer. Test B.
	while(i < 4093) {
		if(p == &myblock[i]) {
			addr = &myblock[i-4];
			break;
		}	
		++i;
	}


	if( (i >= 4092) || (check1 == 1)) {
		printf("Unable to free.\nFile: %s\nLine: %d\n", file, line);
	} else {

		int blockSize = GETS(((header*)addr)->aSize);
		int bit = GETA(((header*)addr)->aSize);
			
			// Checks if block is already freed. Redundant free. Test C.
		if(bit == 0) {
			printf("Redundant calls to free of the same pointer.\nFile: %s\nLine: %d\n", file, line);
		} else {
			int clear = 0;
			while(clear < blockSize) {
				myblock[i + clear] = '\0';
				++clear;
			}
			
			((header*)addr)->aSize = ((blockSize) | (0));

		}
	}


//	printf("size: %d\n", GETS(((header*)addr)->aSize));
	
//	printf("free: %p\n", p);
}


void coalsce(void* p) {



}





	// Initialize memory
void init() {

	header* head = (header*)(&myblock[0]);
	head->aSize = ((4092) | (0));
	
	header* foot = (header*)(&myblock[4088]);
	foot->aSize = ((0) | (1));
	
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
	for(i = 0; i < 50; i++) {
		printf("[ %c ]\n", myblock[i]);
	}
	
}
