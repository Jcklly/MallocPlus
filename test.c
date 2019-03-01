#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"

int main(){

	size_t a = 10;

	int* test = malloc(a);
	int* test2 = free(a);
	

	return 0;

}
