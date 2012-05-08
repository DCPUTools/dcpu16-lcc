#ifndef __STDIO
#define __STDIO

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

#endif
