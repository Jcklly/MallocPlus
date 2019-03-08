#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "mymalloc.h"

double testA(); // Allocates 1 byte and immediately free - 150 times
double testB(); // Allocates 1 byte 150 times, Every 50 byte chucnks, free 50 pointers 1 by 1
double testC(); // Choose Between 1 byte or freeing a pointer, until allocated 50 times
double testD(); // Choose between malloc or free, if malloc then Randomly choose a 1-64 byte size; Do this until malloc 50 times
void testE();
double average(double*);


int main() {

	int i = 0;
	double A[100];
	double B[100];
	double C[100];
	double D[100];
//	double E[100];
//	double F[100];


	srand(time(NULL));

	while(i < 100) {
		A[i] = testA();
		++i;
	}
	i = 0;
	while(i < 100) {
		B[i] = testB();
		++i;
	}
	i = 0;
	while(i < 100) {
		C[i] = testC();
		++i;
	}
	i = 0;
	while(i < 100) {
		D[i] = testD();
		++i;
	}

		// Prints out mean runtime after 100 iterations of each test case
	printf("A: %f Microseconds\n", average(A));
	printf("B: %f Microseconds\n", average(B));
	printf("C: %f Microseconds\n", average(C));
	printf("D: %f Microseconds\n", average(D));

	return 0;
}

double average(double* array) {

	int i = 0;
	double num = 0.0;

	while(i < 100) {
		num += (double)array[i];
		++i;
	}

	return ((num/(double)100)*1000000);

}

	// Allocates 1 byte and immediately free - 150 times
double testA() {

	int i, j;
	void *p;

	struct timeval start, stop;
	gettimeofday(&start, NULL);

	for (i = 0; i < 150; i++) {
	p = (void*)malloc(1);
	free(p);
	}

	gettimeofday(&stop, NULL);
	double ms = (double)(stop.tv_sec - start.tv_sec) * 1000000 + (double)(stop.tv_usec - start.tv_usec) / 1000000;

	return ms;

}


	// Allocates 1 byte 150 times, every 50 byte cunks, free 50 pointers
double testB() {

    int i,j,ip = 0;
    void *p_array[50];

    struct timeval start, stop;
    gettimeofday(&start, NULL);

    for (i = 0; i < 150; i++) {
        p_array[ip] = (void*)malloc(1);
        ip++;

        if (i == 49 || i == 99 || i == 149) {
            for (j = 0; j < 50; j++) {
                free(p_array[j]);
            }

	    ip = 0;
        }
    }

    gettimeofday(&stop, NULL);
    double ms = (double)(stop.tv_sec - start.tv_sec) * 1000000 + (double)(stop.tv_usec - start.tv_usec) / 1000000;

    return ms;
}


double testC() {
    int malloc_count = 0;
    void *p_array[50];
    int size = 0;
    int i;

    struct timeval start, stop;
    gettimeofday(&start, NULL);

    while (malloc_count < 50) {
       int isMalloc = rand() % 2;

       if (isMalloc || size == 0) {
           p_array[size] =  malloc(1);
           size++;
           malloc_count++;

       } else { // isFree
            int random_index = rand() % size;
            free(p_array[random_index]);

            if (random_index < size - 1) {
                p_array[random_index] = p_array[size - 1];
            }

            p_array[size - 1] = 0;
            size--;
       }
    }

    for (i = 0; i < size; i++) {
        myfree(p_array[i], "TEST_C_FREE", i);
    }

    gettimeofday(&stop, NULL);
    double ms = (double)(stop.tv_sec - start.tv_sec) * 1000000 + (double)(stop.tv_usec - start.tv_usec) / 1000000;
    return ms;
}


double testD() {

	int malloc_count, total_allocated_bytes, i, randomSize, isMalloc;
	malloc_count = total_allocated_bytes = i = randomSize = isMalloc = 0;
	int allocated_bytes[50]; // Used to track the amount of bytes allocated
	char* p_array[50] = {NULL};
	char* m;

	struct timeval start, stop;
	gettimeofday(&start, NULL);

	i = 0;
	while(malloc_count < 50) {

		isMalloc = rand() % 2;
		if(isMalloc && total_allocated_bytes < 4092) {
			randomSize = padding((rand() % 64));		
			m = malloc(randomSize);
			if(m == NULL) {
				continue;
			} else {		
				p_array[i] = m;
				total_allocated_bytes = total_allocated_bytes + (randomSize + 2);
				allocated_bytes[i] = total_allocated_bytes;
				++i;
				++malloc_count;
			}
		} else {
			if(i == 0) {
				continue;
			} else { 
				free(p_array[i-1]);
				p_array[i-1] = NULL;
				if(total_allocated_bytes >= allocated_bytes[i-1]) {
					total_allocated_bytes = total_allocated_bytes - allocated_bytes[i-1];
				} else {
					total_allocated_bytes = allocated_bytes[i-1] - total_allocated_bytes;
				}
				--i;
//				--malloc_count;
			}
		}
	}

		// Free's any leftover pointers	
	for(i = 0; i < 50; i++) {
		if(p_array[i] == NULL) {
			break;
		}
		free(p_array[i]);
	}

	gettimeofday(&stop, NULL);
	double ms = (double)(stop.tv_sec - start.tv_sec) * 1000000 + (double)(stop.tv_usec - start.tv_usec) / 1000000;
	return ms;
}

void testE() { // Subtest for D; Able to allocate the max possible bytes in D can but doesn't recieve saturation error?
    int i;
    void *arr_p[50];

    for (i = 0; i < 50; i++) {
        arr_p[i] = mymalloc(64, "TEST_E_MALLOC", i);
    }

    for (i = 0; i < 50; i++) {
        myfree(arr_p[i], "TEST_E_FREE", i);
    }
    
}
