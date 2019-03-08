
#include <stdio.h>


	// Replaces all calls to malloc to mymalloc and free to myfree 
#define malloc( x ) mymalloc(x, __FILE__, __LINE__)
#define free( x ) myfree(x, __FILE__, __LINE__)


	// Declare the size of the heap
#define HSIZE 4096
#define METADATA 2


#define GETS(h) ((h) & (~0x1))
#define GETA(h) ((h) & (0x1))

	// Declare static char array which will be representing our heap
static char myblock[HSIZE];


typedef struct _HEADER {
	short aSize;
}header;



	// Function signatures for mymalloc and myfree
void* mymalloc(size_t, char*, size_t);
void myfree(void*, char*, size_t);
void init();
void printH();
int padding(int);
void printP();
void coalesce(void*, int, int);
