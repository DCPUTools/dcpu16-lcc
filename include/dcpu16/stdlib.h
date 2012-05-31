#ifndef __STDLIB
#define __STDLIB
#include <stddef.h>

// Constants
#define FALSE        0
#define false        0
#define TRUE         1
#define true         1

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

// Types
#ifndef __BOOLEAN
#define __BOOLEAN
typedef unsigned bool;
#endif

// Methods
extern void* malloc(size_t size);
extern void free(void* ptr);
extern void memmove(int src, int dest, size_t length);

extern int getmem(unsigned index);
extern void putmem(unsigned index, int value);
extern void* getpointer(unsigned index);

extern void jump(void* pointer);

#endif
