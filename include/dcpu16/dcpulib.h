#ifndef __DCPULIB
#define __DCPULIB

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

extern int printf( const char*, ... );
extern char* itoa( int, char*, int );
extern char* utoa( unsigned, char*, int );
extern char* ftoa( float, char* );
extern unsigned putchar( unsigned );    //prints 1 character - high bits can be used for formatting
extern int puts( const char* );

extern unsigned* getdispcur();          //Get display cursor - returns a pointer between 0x8000 and 0x817f
extern unsigned* setdispcur(unsigned*); //Set display cursor

extern void* malloc(unsigned);          //returns NULL if no free block can be found.
extern void free(void*);

extern char getchar();

extern int getmem(unsigned index);
extern void putmem(unsigned index, int value);

#endif
