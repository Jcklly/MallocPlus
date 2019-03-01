
#include <stdio.h>


	// Replaces all calls to malloc to mymalloc and free to myfree 
#define malloc( x ) mymalloc(x, __FILE__, __LINE__)
#define free( x ) myfree(x, __FILE__, __LINE__)


	// Declare the size of the heap
#define HSIZE 4096


	// Declare static char array which will be representing our heap
static char myblock[HSIZE];


	// Function signatures for mymalloc and myfree
void* mymalloc(size_t, char*, size_t);
void* myfree(void*, char*, size_t);




