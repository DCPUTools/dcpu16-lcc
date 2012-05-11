#ifndef __STDLIB
#define __STDLIB
#include <stddef.h>

// Constants
#ifndef NULL
#define NULL ((void*)0)
#endif

#define FALSE        0
#define TRUE         1

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

// Types
typedef unsigned boolean;

// Methods
extern void* malloc(int owner, size_t words);
extern void free(void*);
extern void memmove(int src, int dest, size_t length);

extern int getmem(unsigned index);
extern void putmem(unsigned index, int value);

extern void jump(void* pointer);

#define malloc(size) malloc(0x10c, size)

#endif
