# MallocPlus
Reimplementation of standard C library's version of Malloc and Free. Making it smarter and less prone to segmentation faulting.
## Note: There is a predefinined space limit of 4096 bytes. This is set in the header file and can be increased/decreased.
## Also, this allocation follows a first-fit approach, but coalescing is done after every free to help with fragmentation.

# Commands
- Copy Makefile, memgrind.c, mymalloc.c, and mymalloc.h files into current project directory.
- Edit the `Makefile` with whichever program you want to run it with. (Replace memgrind.c with your own program)
- In your main program, import the header file using `#include "mymalloc.h"`.

That's it! The program will automatically replace all calls to malloc and free with the versions created in the program here.
