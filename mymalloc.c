#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"


	// Implementation of malloc.
void* mymalloc(size_t s, char* file, size_t line) {
	
		// Checks if it's the first time malloc has been called.		
	if( (((header*)&myblock[0])->aSize <= 0) || (((header*)&myblock[0])->aSize >= 4100) ) {
		init();
	}

	
		// Base case if size given is 0.
	if((int)s <= 0){
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
			fprintf(stderr, "Saturation of dynamic memory.\nFile: %s\nLine: %d\n", file, line);
			boolean = 1;
			rPtr = NULL;
			break;
		}

		if(s == 1 || s == 2 ) {
			s = 2;
		}	
		
			// if space is enough and is not allocated, set current head size to size of allocated, and turn
			// bit to 1. Then create a new header in front of newly allocated spot with updated info.
		reSize = padding((int)s);	
		if( (bit == 0) && (sizeA >= (int)reSize) ) {
			
			newSize = sizeA - reSize - METADATA;
			if(newSize == 0) {
				rPtr = &myblock[i + METADATA];
				reSize = reSize + 2;
				((header*)ptr)->aSize = (reSize | 1) ;
			} else {
				rPtr = &myblock[i + METADATA];
				((header*)ptr)->aSize = (reSize | 1);
			}

			if( (((header*)&myblock[i + reSize + METADATA])->aSize <= 0) ) {
				
				header* head = (header*)(&myblock[i + reSize + METADATA]);
				head->aSize = ((newSize) | (0));
					
			}
			break;
			
		} else {
			i = i + METADATA + sizeA;
		}
	}

	return rPtr;
}


	// Adds padding to input size so it is always divisible by 4.
int padding(int a) {
	int pad = 0;
	int div = a;
	
	while((div % 2) != 0) {
		++pad;
		div += pad;
		
	}

	return div;
}


	// Implementation of free.
void myfree(void* p, char* file, size_t line) {

	char* addr = NULL;
	int i, check1, check2;
	i = check1 = check2 = 0;


		// Checks if address is even a valid pointer. Test A.
	while(i < 4096) {
		if(p == &myblock[i]) {
			addr = &myblock[i-METADATA];
			check2 = 1;
			break;
		}	
		++i;
	}


		// Checks if pointer was even allocated by malloc. Test B.
	addr = p - METADATA;
	if(check2 == 1) {
		if( (((header*)addr)->aSize <= 0) || (((header*)addr)->aSize >= 4100) ) { 
			check1 = 1;
		} 
	}


		// Part of Test B.
	if( (i >= 4095) || (check1 == 1)) {
		fprintf(stderr, "Unable to free.\nFile: %s\nLine: %d\n", file, line);
	} else {

		int blockSize = GETS(((header*)addr)->aSize);
		int bit = GETA(((header*)addr)->aSize);
			
			// Checks if block is already freed. Redundant free. Test C.
		if(bit == 0) {
			fprintf(stderr, "Redundant calls to free of the same pointer.\nFile: %s\nLine: %d\n", file, line);
		} else {
			int clear = 0;

			while(clear < blockSize) {
				myblock[i + clear] = '\0';
				++clear;
			}
			
			((header*)addr)->aSize = ((blockSize) | (0));
			coalesce(p, i, blockSize);
		}
	}
}


	// Given a pointer, it's position in array, and it's blocksize, will coalesce to save space.
void coalesce(void* p, int position, int sFront) {
	
		// Declare Variables
	char* ptr = p + sFront;
	int i, bit, sizeA, block, currBlock, boolean;
	i = bit = sizeA = block = boolean = 0; 
	currBlock = sFront;

	block = GETS(((header*)ptr)->aSize);
	bit = GETA(((header*)ptr)->aSize);



		// Checks block IN FRONT of current block
	if((bit == 0) && (block != 0) ) {
		currBlock = currBlock + block + METADATA;
		((header*)ptr)->aSize = '\0';
		ptr = p - METADATA;
		((header*)ptr)->aSize = ( (currBlock) | (0) );
	}


		// Check block BEHIND current block		
	int before = -1;
	while(boolean == 0) {
		ptr = &myblock[i];
		currBlock = ((header*)ptr) -> aSize;
		sizeA = GETS(currBlock);

			// End of Array.
		if( sizeA == 0 ) {
			boolean = 1;
			break;
		}	
	

			// Size and bit of block before current block
		block = GETS(((header*)&myblock[before])->aSize);
		bit = GETA(((header*)&myblock[before])->aSize);
		if( ((p-METADATA) == ptr) && (bit == 0) && (before != -1) ) {

			block = block + sizeA + METADATA;
			((header*)&myblock[before])->aSize = ( (block) | (0) );
			((header*)ptr)->aSize = '\0';
			break;
		}
	
		before = i;
		i = i + METADATA + sizeA;	
	}


}


	// Initialize memory
void init() {

	header* head = (header*)(&myblock[0]);
	head->aSize = ((4092) | (0));
	
	header* foot = (header*)(&myblock[4094]);
	foot->aSize = ((0) | (1));
	
}




	// helper functions that print the array. REMOVE BEFORE SUBMITTING.
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
