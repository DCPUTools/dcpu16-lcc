#ifndef DCPU16_H_
#define DCPU16_H_

enum {RGA=0, RGB=1, RGC=2, RGX=3, RGY=4, RGZ=5, RGI=6};

#include "c.h"

#define TMP_REG 0x38                //X, Y, Z
#define VAR_REG (0x38 ^ TMP_REG)    //nothing!

#define NODEPTR_TYPE Node
#define OP_LABEL(p) ((p)->op)
#define LEFT_CHILD(p) ((p)->kids[0])
#define RIGHT_CHILD(p) ((p)->kids[1])
#define STATE_LABEL(p) ((p)->x.state)
#ifdef NDEBUG
#undef NDEBUG
#endif

// Declare local routines to be used by IR record here
static void address(Symbol, Symbol, long);
static void blkfetch(int, int, int, int);
static void blkloop(int, int, int, int, int, int[]);
static void blkstore(int, int, int, int);
static void defaddress(Symbol);
static void defconst(int, int, Value);
static void defstring(int, char *);
static void defsymbol(Symbol);
static void doarg(Node);
static void emit2(Node);
static void dcpu_emit(Node p);
static void export(Symbol);
static void clobber(Node);
static void function(Symbol, Symbol [], Symbol [], int);
static void global(Symbol);
static void import(Symbol);
static void local(Symbol);
static void progbeg(int, char **);
static void progend(void);
static void segment(int);
static void space(int);
static void target(Node);
static void emithex(short);
static int addrgop(Node, int);
static int argop(Node, int);
static int ncregop(Node, int);
static int regopu(Node, int);
static int memop(Node, int);
static int memopu(Node, int);
static int ncmemop(Node, int);
static int sametree(Node, Node);

static void pushstack(int, const char*);
static void popstack(int, const char*);

// Local vars here

static Symbol reg[32];
static Symbol regw;
static short iscaddr = 1;

const char hexdigits[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

#endif
