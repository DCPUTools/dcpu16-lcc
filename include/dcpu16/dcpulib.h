#ifndef __DCPULIB
#define __DCPULIB

// Constants
#define NULL         0

#define FALSE        0
#define TRUE         1

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

// Types
typedef unsigned boolean;

// Methods
extern int printf( const char*, ... );
extern char* itoa( int, char*, int );
extern char* utoa( unsigned, char*, int );
extern char* ftoa( float, char* );
extern unsigned putchar( unsigned );    //prints 1 character - high bits can be used for formatting
extern int puts( const char* );

extern void setcolor(unsigned int color);
extern void clearcolor();

extern unsigned* getdispcur();          //Get display cursor - returns a pointer between 0x8000 and 0x817f
extern unsigned* setdispcur(unsigned*); //Set display cursor

extern void* malloc(unsigned);          //returns NULL if no free block can be found.
extern void free(void*);

extern char getchar();

extern int getmem(unsigned index);
extern void putmem(unsigned index, int value);

extern void setinterruptlistener(void* pointer);
extern void* getinterruptlistener();
extern void triggerinterrupt(int code);

extern void jump(void* pointer);

#endif
