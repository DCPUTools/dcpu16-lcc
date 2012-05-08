#ifndef __STDLIB
#define __STDLIB

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
extern void* malloc(unsigned);          //returns NULL if no free block can be found.
extern void free(void*);

extern int getmem(unsigned index);
extern void putmem(unsigned index, int value);

extern void setinterruptlistener(void* pointer);
extern void* getinterruptlistener();
extern void triggerinterrupt(int code);

extern void jump(void* pointer);

#endif
