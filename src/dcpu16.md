%{
enum {RGA=0, RGB=1, RGC=2, RGX=3, RGY=4, RGZ=5};

#include "c.h"

#define TMP_REG 0x3E    
#define VAR_REG (0x3E ^ TMP_REG)

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
static int memop(Node, int);
static int ncmemop(Node, int);
static int sametree(Node, Node);

static void pushstack(int);
static void popstack(int);

// Local vars here

static Symbol reg[32];
static Symbol regw;

const char hexdigits[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

%}

%start stmt
%term CNSTF1=1041
%term CNSTI1=1045
%term CNSTP1=1047
%term CNSTU1=1046
%term ARGB=41
%term ARGF1=1057
%term ARGI1=1061
%term ARGP1=1063
%term ARGU1=1062
%term ASGNB=57
%term ASGNF1=1073
%term ASGNI1=1077
%term ASGNP1=1079
%term ASGNU1=1078
%term INDIRB=73
%term INDIRF1=1089
%term INDIRI1=1093
%term INDIRP1=1095
%term INDIRU1=1094
%term CVFF1=1137
%term CVFI1=1141
%term CVIF1=1153
%term CVII1=1157
%term CVIU1=1158
%term CVPU1=1174
%term CVUI1=1205
%term CVUP1=1207
%term CVUU1=1206
%term NEGF1=1217
%term NEGI1=1221
%term CALLB=217
%term CALLF1=1233
%term CALLI1=1237
%term CALLP1=1239
%term CALLU1=1238
%term CALLV=216
%term RETF1=1265
%term RETI1=1269
%term RETP1=1271
%term RETU1=1270
%term RETV=248
%term ADDRGP1=1287
%term ADDRFP1=1303
%term ADDRLP1=1319
%term ADDF1=1329
%term ADDI1=1333
%term ADDP1=1335
%term ADDU1=1334
%term SUBF1=1345
%term SUBI1=1349
%term SUBP1=1351
%term SUBU1=1350
%term LSHI1=1365
%term LSHU1=1366
%term MODI1=1381
%term MODU1=1382
%term RSHI1=1397
%term RSHU1=1398
%term BANDI1=1413
%term BANDU1=1414
%term BCOMI1=1429
%term BCOMU1=1430
%term BORI1=1445
%term BORU1=1446
%term BXORI1=1461
%term BXORU1=1462
%term DIVF1=1473
%term DIVI1=1477
%term DIVU1=1478
%term MULF1=1489
%term MULI1=1493
%term MULU1=1494
%term EQF1=1505
%term EQI1=1509
%term EQU1=1510
%term GEF1=1521
%term GEI1=1525
%term GEU1=1526
%term GTF1=1537
%term GTI1=1541
%term GTU1=1542
%term LEF1=1553
%term LEI1=1557
%term LEU1=1558
%term LTF1=1569
%term LTI1=1573
%term LTU1=1574
%term NEF1=1585
%term NEI1=1589
%term NEU1=1590
%term JUMPV=584
%term LABELV=600
%term VREGP=711

%term LOADB=233
%term LOADF1=1249
%term LOADP1=1255
%term LOADI1=1253
%term LOADU1=1254

%%

reg:    LOADF1(reg) "?SET %c, %0\n" move(a)
reg:    LOADI1(reg) "?SET %c, %0\n" move(a)
reg:    LOADU1(reg) "?SET %c, %0\n" move(a)
reg:    LOADP1(reg) "?SET %c, %0\n" move(a)

reg:    INDIRF1(VREGP)  "# read register\n"
reg:    INDIRI1(VREGP)  "# read register\n"
reg:    INDIRU1(VREGP)  "# read register\n"
reg:    INDIRP1(VREGP)  "# read register\n"

stmt:   ASGNF1(VREGP,reg)   "# write register\n"
stmt:   ASGNI1(VREGP,reg)   "# write register\n"
stmt:   ASGNU1(VREGP,reg)   "# write register\n"
stmt:   ASGNP1(VREGP,reg)   "# write register\n"

stmt:   reg ""

con:    CNSTF1  "#" 1
con:    CNSTI1  "#" 1
con:    CNSTU1  "%a" 1
con:    CNSTP1  "%a" 1

acon:   CNSTU1  "%a" 1
acon:   CNSTP1  "%a" 1

addr:   acon            "%0"
addr:   ADDI1(reg,acon) "%1+%0"
addr:   reg             "%0"
addr:   ADDRGP1         "%a" 1
addr:   ADDRFP1         "#" 1
addr:   ADDRLP1         "#" 1

reg:    con "SET %c, %0\n" 1
reg:    mem "SET %c, %0\n" 1
reg:    addr "SET %c, %0\n" 1

mem:    INDIRF1(addr)   "[%0]"
mem:    INDIRI1(addr)   "[%0]"
mem:    INDIRU1(addr)   "[%0]"
mem:    INDIRP1(addr)   "[%0]"

bval:   reg     "%0"
bval:   con     "%0"
bval:   mem     "%0"

stmt:   ASGNF1(addr,bval)   "SET [%0], %1\n" 1
stmt:   ASGNI1(addr,bval)   "SET [%0], %1\n" 1
stmt:   ASGNU1(addr,bval)   "SET [%0], %1\n" 1
stmt:   ASGNP1(addr,bval)   "SET [%0], %1\n" 1

reg:    BCOMI1(bval)                "SET %c, 0xffff\nXOR %c, %0\n" 3
reg:    BCOMU1(bval)                "SET %c, 0xffff\nXOR %c, %0\n" 3
stmt:   ASGNI1(addr,BCOMI1(bval))   "SET [%0], 0xffff\nXOR [%0], %1\n" 3
stmt:   ASGNU1(addr,BCOMU1(bval))   "SET [%0], 0xffff\nXOR [%0], %1\n" 3

reg:    CVFI1(bval)                 "SET %c, %0\nSHR %c, 8\n" 4
stmt:   ASGNI1(addr,CVFI1(bval))    "SET [%0], %1\nSHR [%0], 8\n" 4

reg:    CVIF1(bval)                 "SET %c, %0\nSHL %c, 8\n" 4
reg:    CVIU1(bval)                 "SET %c, %0\n" 1
stmt:   ASGNF1(addr,CVIF1(bval))    "SET [%0], %1\nSHL [%0], 8\n" 4
stmt:   ASGNU1(addr,CVIF1(bval))    "SET [%0], %1\n" 1

reg:    CVUI1(bval)                 "SET %c, %0\n" 1
reg:    CVUP1(bval)                 "SET %c, %0\n" 1
stmt:   ASGNI1(addr,CVUI1(bval))    "SET [%0], %1\n" 1
stmt:   ASGNP1(addr,CVUP1(bval))    "SET [%0], %1\n" 1

reg:    CVPU1(bval)                 "SET %c, %0\n" 1
stmt:   ASGNU1(addr,CVPU1(bval))    "SET [%0], %1\n" 1

reg:    NEGF1(bval)                 "SET %c, 0\nSUB %c, %0\n" 4
reg:    NEGI1(bval)                 "SET %c, 0\nSUB %c, %0\n" 4
stmt:   ASGNF1(addr,NEGI1(bval))    "SET [%0], 0\nSUB [%0], %1\n" 4
stmt:   ASGNI1(addr,NEGI1(bval))    "SET [%0], 0\nSUB [%0], %1\n" 4

reg:    ADDF1(bval,bval)                "?SET %c, %0\nADD %c, %1\n" 3
reg:    ADDI1(bval,bval)                "?SET %c, %0\nADD %c, %1\n" 3
reg:    ADDU1(bval,bval)                "?SET %c, %0\nADD %c, %1\n" 3
reg:    ADDP1(bval,bval)                "?SET %c, %0\nADD %c, %1\n" 3
stmt:   ASGNF1(addr,ADDF1(bval,bval))   "ADD [%0], %2\n" memop(a, 2) 
stmt:   ASGNI1(addr,ADDI1(bval,bval))   "ADD [%0], %2\n" memop(a, 2)
stmt:   ASGNU1(addr,ADDU1(bval,bval))   "ADD [%0], %2\n" memop(a, 2)
stmt:   ASGNP1(addr,ADDP1(bval,bval))   "ADD [%0], %2\n" memop(a, 2)
stmt:   ASGNF1(addr,ADDF1(bval,bval))   "SET [%0], %1\nADD [%0], %2\n" ncmemop(a, 3)
stmt:   ASGNI1(addr,ADDI1(bval,bval))   "SET [%0], %1\nADD [%0], %2\n" ncmemop(a, 3)
stmt:   ASGNU1(addr,ADDU1(bval,bval))   "SET [%0], %1\nADD [%0], %2\n" ncmemop(a, 3)
stmt:   ASGNP1(addr,ADDP1(bval,bval))   "SET [%0], %1\nADD [%0], %2\n" ncmemop(a, 3)
stmt:   ASGNF1(addr,ADDF1(bval,bval))   "SET [__scratch], %2\nSET [%0], %1\nADD [%0], [__scratch]\n" 6
stmt:   ASGNI1(addr,ADDI1(bval,bval))   "SET [__scratch], %2\nSET [%0], %1\nADD [%0], [__scratch]\n" 6
stmt:   ASGNU1(addr,ADDU1(bval,bval))   "SET [__scratch], %2\nSET [%0], %1\nADD [%0], [__scratch]\n" 6
stmt:   ASGNP1(addr,ADDP1(bval,bval))   "SET [__scratch], %2\nSET [%0], %1\nADD [%0], [__scratch]\n" 6

reg:    BANDI1(bval,bval)               "?SET %c, %0\nAND %c, %1\n" 2
reg:    BANDU1(bval,bval)               "?SET %c, %0\nAND %c, %1\n" 2
stmt:   ASGNI1(addr,BANDI1(bval,bval))  "AND [%0], %2\n" memop(a, 1)
stmt:   ASGNU1(addr,BANDU1(bval,bval))  "AND [%0], %2\n" memop(a, 1)
stmt:   ASGNI1(addr,BANDI1(bval,bval))  "SET [%0], %1\nAND [%0], %2\n" ncmemop(a, 2)
stmt:   ASGNU1(addr,BANDU1(bval,bval))  "SET [%0], %1\nAND [%0], %2\n" ncmemop(a, 2)
stmt:   ASGNI1(addr,BANDI1(bval,bval))  "SET [__scratch], %2\nSET [%0], %1\nAND [%0], [__scratch]\n" 3
stmt:   ASGNU1(addr,BANDU1(bval,bval))  "SET [__scratch], %2\nSET [%0], %1\nAND [%0], [__scratch]\n" 3

reg:    BORI1(bval,bval)                "?SET %c, %0\nBOR %c, %1\n" 2
reg:    BORU1(bval,bval)                "?SET %c, %0\nBOR %c, %1\n" 2
stmt:   ASGNI1(addr,BORI1(bval,bval))   "BOR [%0], %2\n" memop(a, 1)
stmt:   ASGNU1(addr,BORU1(bval,bval))   "BOR [%0], %2\n" memop(a, 1)
stmt:   ASGNI1(addr,BORI1(bval,bval))   "SET [%0], %1\nBOR [%0], %2\n" ncmemop(a, 2)
stmt:   ASGNU1(addr,BORU1(bval,bval))   "SET [%0], %1\nBOR [%0], %2\n" ncmemop(a, 2)
stmt:   ASGNI1(addr,BORI1(bval,bval))   "SET [__scratch], %2\nSET [%0], %1\nBOR [%0], [__scratch]\n" 3
stmt:   ASGNU1(addr,BORU1(bval,bval))   "SET [__scratch], %2\nSET [%0], %1\nBOR [%0], [__scratch]\n" 3

reg:    BXORI1(bval,bval)               "?SET %c, %0\nXOR %c, %1\n" 2
reg:    BXORU1(bval,bval)               "?SET %c, %0\nXOR %c, %1\n" 2
stmt:   ASGNI1(addr,BXORI1(bval,bval))  "XOR [%0], %2\n" memop(a, 1)
stmt:   ASGNU1(addr,BXORU1(bval,bval))  "XOR [%0], %2\n" memop(a, 1)
stmt:   ASGNI1(addr,BXORI1(bval,bval))  "SET [%0], %1\nXOR [%0], %2\n" ncmemop(a, 2)
stmt:   ASGNU1(addr,BXORU1(bval,bval))  "SET [%0], %1\nXOR [%0], %2\n" ncmemop(a, 2)
stmt:   ASGNI1(addr,BXORI1(bval,bval))  "SET [__scratch], %2\nSET [%0], %1\nXOR [%0], [__scratch]\n" 3
stmt:   ASGNU1(addr,BXORU1(bval,bval))  "SET [__scratch], %2\nSET [%0], %1\nXOR [%0], [__scratch]\n" 3

reg:    DIVF1(bval,bval)                "?SET %c, %0\nDIV %c, %1\n" 4 
reg:    DIVI1(bval,bval)                "?SET %c, %0\nDIV %c, %1\n" 4
reg:    DIVU1(bval,bval)                "?SET %c, %0\nDIV %c, %1\n" 4
stmt:   ASGNF1(addr,DIVF1(bval,bval))   "DIV [%0], %2\n" memop(a, 3)
stmt:   ASGNI1(addr,DIVI1(bval,bval))   "DIV [%0], %2\n" memop(a, 3)
stmt:   ASGNU1(addr,DIVU1(bval,bval))   "DIV [%0], %2\n" memop(a, 3)
stmt:   ASGNF1(addr,DIVF1(bval,bval))   "SET [%0], %1\nDIV [%0], %2\n" ncmemop(a, 4) 
stmt:   ASGNI1(addr,DIVI1(bval,bval))   "SET [%0], %1\nDIV [%0], %2\n" ncmemop(a, 4)
stmt:   ASGNU1(addr,DIVU1(bval,bval))   "SET [%0], %1\nDIV [%0], %2\n" ncmemop(a, 4)
stmt:   ASGNF1(addr,DIVF1(bval,bval))   "SET [__scratch], %2\nSET [%0], %1\nDIV [%0], [__scratch]\n" 5
stmt:   ASGNI1(addr,DIVI1(bval,bval))   "SET [__scratch], %2\nSET [%0], %1\nDIV [%0], [__scratch]\n" 5
stmt:   ASGNU1(addr,DIVU1(bval,bval))   "SET [__scratch], %2\nSET [%0], %1\nDIV [%0], [__scratch]\n" 5

reg:    LSHI1(bval,bval)                "?SET %c, %0\nSHL: %c, %0\n" 3
reg:    LSHU1(bval,bval)                "?SET %c, %0\nSHL: %c, %0\n" 3
stmt:   ASGNI1(addr,LSHI1(bval,bval))   "SHL: [%0], %2\n" memop(a, 2)
stmt:   ASGNU1(addr,LSHU1(bval,bval))   "SHL: [%0], %2\n" memop(a, 2)
stmt:   ASGNI1(addr,LSHI1(bval,bval))   "SET [%0], %1\nSHL: [%0], %2\n" ncmemop(a, 3)
stmt:   ASGNU1(addr,LSHU1(bval,bval))   "SET [%0], %1\nSHL: [%0], %2\n" ncmemop(a, 3)
stmt:   ASGNI1(addr,LSHI1(bval,bval))   "SET [__scratch], %2\nSET [%0], %1\nSHL: [%0], [__scratch]\n" 4
stmt:   ASGNU1(addr,LSHU1(bval,bval))   "SET [__scratch], %2\nSET [%0], %1\nSHL: [%0], [__scratch]\n" 4

reg:    MODI1(bval,bval)                "?SET %c, %0\nMOD %c, %1\n" 4
reg:    MODU1(bval,bval)                "?SET %c, %0\nMOD %c, %1\n" 4
stmt:   ASGNI1(addr,MODI1(bval,bval))   "MOD [%0], %2\n" memop(a, 3)
stmt:   ASGNU1(addr,MODU1(bval,bval))   "MOD [%0], %2\n" memop(a, 3)
stmt:   ASGNI1(addr,MODI1(bval,bval))   "SET [%0], %1\nMOD [%0], %2\n" ncmemop(a, 4)
stmt:   ASGNU1(addr,MODU1(bval,bval))   "SET [%0], %1\nMOD [%0], %2\n" ncmemop(a, 4)
stmt:   ASGNI1(addr,MODI1(bval,bval))   "SET [__scratch], %2\nSET [%0], %1\nMOD [%0], [__scratch]\n" 5
stmt:   ASGNU1(addr,MODU1(bval,bval))   "SET [__scratch], %2\nSET [%0], %1\nMOD [%0], [__scratch]\n" 5

reg:    MULF1(bval,bval)                "?SET %c, %0\nMUL %c, %1\nSET [__scratch], O\nSHR %c, 8\nSHL [__scratch], 8\nADD %c, X\n" 12
reg:    MULI1(bval,bval)                "?SET %c, %0\nMUL %c, %1\n" 3
reg:    MULU1(bval,bval)                "?SET %c, %0\nMUL %c, %1\n" 3
stmt:   ASGNF1(addr,MULF1(bval,bval))   "MUL [%0], %2\nSET [__scratch], O\nSHR [%0], 8\nSHL [__scratch], 8\nADD [%0], [__scratch]\n" memop(a, 11)
stmt:   ASGNI1(addr,MULI1(bval,bval))   "MUL [%0], %2\n" memop(a, 2)
stmt:   ASGNU1(addr,MULU1(bval,bval))   "MUL [%0], %2\n" memop(a, 2)
stmt:   ASGNF1(addr,MULF1(bval,bval))   "SET [%0], %1\nMUL [%0], %2\nSET [__scratch], O\nSHR [%0], 8\nSHL [__scratch], 8\nADD [%0], [__scratch]\n" ncmemop(a, 12)
stmt:   ASGNI1(addr,MULI1(bval,bval))   "SET [%0], %1\nMUL [%0], %2\n" ncmemop(a, 3)
stmt:   ASGNU1(addr,MULU1(bval,bval))   "SET [%0], %1\nMUL [%0], %2\n" ncmemop(a, 3)
stmt:   ASGNF1(addr,MULF1(bval,bval))   "SET [1+__scratch], %2\nSET [%0], %1\nMUL [%0], [1+__scratch]\nSET [__scratch], O\nSHR [%0], 8\nSHL [__scratch], 8\nADD [%0], [__scratch]\n" 15
stmt:   ASGNI1(addr,MULI1(bval,bval))   "SET [__scratch], %2\nSET [%0], %1\nMUL [%0], [__scratch]\n" 4
stmt:   ASGNU1(addr,MULU1(bval,bval))   "SET [__scratch], %2\nSET [%0], %1\nMUL [%0], [__scratch]\n" 4

reg:    RSHI1(bval,bval)                "?SET %c, %0\nSHR: %c, %0\n" 3
reg:    RSHU1(bval,bval)                "?SET %c, %0\nSHR: %c, %0\n" 3
stmt:   ASGNI1(addr,RSHI1(bval,bval))   "SHR: %0, %2\n" memop(a, 2)
stmt:   ASGNU1(addr,RSHU1(bval,bval))   "SHR: %0, %2\n" memop(a, 2)
stmt:   ASGNI1(addr,RSHI1(bval,bval))   "SET [%0], %1\nSHR: %0, %2\n" ncmemop(a, 3)
stmt:   ASGNU1(addr,RSHU1(bval,bval))   "SET [%0], %1\nSHR: %0, %2\n" ncmemop(a, 3)
stmt:   ASGNI1(addr,RSHI1(bval,bval))   "SET [__scratch], %2\nSET [%0], %1\nSHR: [%0], [__scratch]\n" 4
stmt:   ASGNU1(addr,RSHU1(bval,bval))   "SET [__scratch], %2\nSET [%0], %1\nSHR: [%0], [__scratch]\n" 4

reg:    SUBF1(bval,bval)                "?SET %c, %0\nSUB %c, %1\n" 3
reg:    SUBI1(bval,bval)                "?SET %c, %0\nSUB %c, %1\n" 3
reg:    SUBU1(bval,bval)                "?SET %c, %0\nSUB %c, %1\n" 3
reg:    SUBP1(bval,bval)                "?SET %c, %0\nSUB %c, %1\n" 3
stmt:   ASGNF1(addr,SUBF1(bval,bval))   "SUB [%0], %2\n" memop(a, 2)
stmt:   ASGNI1(addr,SUBI1(bval,bval))   "SUB [%0], %2\n" memop(a, 2)
stmt:   ASGNU1(addr,SUBU1(bval,bval))   "SUB [%0], %2\n" memop(a, 2)
stmt:   ASGNP1(addr,SUBP1(bval,bval))   "SUB [%0], %2\n" memop(a, 2)
stmt:   ASGNF1(addr,SUBF1(bval,bval))   "SET [%0], %1\nSUB: [%0], %2\n" ncmemop(a, 3)
stmt:   ASGNI1(addr,SUBI1(bval,bval))   "SET [%0], %1\nSUB: [%0], %2\n" ncmemop(a, 3)
stmt:   ASGNU1(addr,SUBU1(bval,bval))   "SET [%0], %1\nSUB: [%0], %2\n" ncmemop(a, 3)
stmt:   ASGNP1(addr,SUBP1(bval,bval))   "SET [%0], %1\nSUB: [%0], %2\n" ncmemop(a, 3)
stmt:   ASGNF1(addr,SUBF1(bval,bval))   "SET [__scratch], %2\nSET [%0], %1\nSUB: [%0], [__scratch]\n" 4
stmt:   ASGNI1(addr,SUBI1(bval,bval))   "SET [__scratch], %2\nSET [%0], %1\nSUB: [%0], [__scratch]\n" 4
stmt:   ASGNU1(addr,SUBU1(bval,bval))   "SET [__scratch], %2\nSET [%0], %1\nSUB: [%0], [__scratch]\n" 4
stmt:   ASGNP1(addr,SUBP1(bval,bval))   "SET [__scratch], %2\nSET [%0], %1\nSUB: [%0], [__scratch]\n" 4

stmt:   EQF1(bval,bval) "IFE %0, %1\nSET PC, %a\n" 4 
stmt:   EQI1(bval,bval) "IFE %0, %1\nSET PC, %a\n" 4
stmt:   EQU1(bval,bval) "IFE %0, %1\nSET PC, %a\n" 4

stmt:   GEF1(bval,bval) "IFG %0, %1\nSET PC, %a\nIFE %0, %1\nSET PC, %a\n" 6 
stmt:   GEI1(bval,bval) "IFG %0, %1\nSET PC, %a\nIFE %0, %1\nSET PC, %a\n" 6
stmt:   GEU1(bval,bval) "IFG %0, %1\nSET PC, %a\nIFE %0, %1\nSET PC, %a\n" 6

stmt:   GTF1(bval,bval) "IFG %0, %1\nSET PC, %a\n" 4 
stmt:   GTI1(bval,bval) "IFG %0, %1\nSET PC, %a\n" 4
stmt:   GTU1(bval,bval) "IFG %0, %1\nSET PC, %a\n" 4

stmt:   LEF1(bval,bval) "IFG %1, %0\nSET PC, %a\nIFE %0, %1\nSET PC, %a\n" 6 
stmt:   LEI1(bval,bval) "IFG %1, %0\nSET PC, %a\nIFE %0, %1\nSET PC, %a\n" 6
stmt:   LEU1(bval,bval) "IFG %1, %0\nSET PC, %a\nIFE %0, %1\nSET PC, %a\n" 6

stmt:   LTF1(bval,bval) "IFG %1, %0\nSET PC, %a\n" 4 
stmt:   LTI1(bval,bval) "IFG %1, %0\nSET PC, %a\n" 4
stmt:   LTU1(bval,bval) "IFG %1, %0\nSET PC, %a\n" 4

stmt:   NEF1(bval,bval) "IFN %0, %1\nSET PC, %a\n" 4 
stmt:   NEI1(bval,bval) "IFN %0, %1\nSET PC, %a\n" 4
stmt:   NEU1(bval,bval) "IFN %0, %1\nSET PC, %a\n" 4

stmt:   ARGF1(bval)                 "$SET PUSH, %0\n" 1
stmt:   ARGI1(bval)                 "$SET PUSH, %0\n" 1
stmt:   ARGU1(bval)                 "$SET PUSH, %0\n" 1
stmt:   ARGP1(bval)                 "$SET PUSH, %0\n" 1
stmt:   ASGNB(addr,INDIRB(addr))    "# block assign\n" 1

reg:    CALLF1(addr)    "^JSR %0\n" 2
reg:    CALLI1(addr)    "^JSR %0\n" 2
reg:    CALLU1(addr)    "^JSR %0\n" 2
reg:    CALLP1(addr)    "^JSR %0\n" 2
stmt:   CALLV(addr)     "^JSR %0\n" 2

stmt:   RETF1(reg) "# return float\n" 2
stmt:   RETI1(reg) "# return int\n" 2
stmt:   RETU1(reg) "# return uint\n" 2
stmt:   RETP1(reg) "# return ptr\n" 2

stmt:   JUMPV(addr) "SET PC, %0\n" 1

stmt:   LABELV  ":%a\n"

%%

static void progbeg(int argc, char *argv[]) {
    {
        union {
            char c;
            int i;
        } u;
        u.i = 0;
        u.c = 1;
        swap = ((int)(u.i == 1)) != IR->little_endian;
    }
    parseflags(argc,argv);

    //put both ints and floats into IREG set
    reg[RGA] = mkreg("A",RGA,1,IREG);
    reg[RGB] = mkreg("B",RGB,1,IREG);
    reg[RGC] = mkreg("C",RGC,1,IREG);
    reg[RGX] = mkreg("X",RGX,1,IREG);
    reg[RGY] = mkreg("Y",RGY,1,IREG);
    reg[RGZ] = mkreg("Z",RGZ,1,IREG);
    
    regw = mkwildcard(reg);
    
    tmask[IREG] = TMP_REG;
    vmask[IREG] = VAR_REG;
    tmask[FREG] = 0;
    vmask[FREG] = 0;

    print(";\n;DCPU-16 ASM Generated by LCC 4.2 (dcpu16-lcc v0.1)\n;\n");
    print("JSR _main\n");
    print(":__crash\n");
    print("SET PC, __crash\n");
}

static Symbol rmap(int opk) {
    switch (optype(opk)) {
    case B:
    case P:
    case I:
    case U:
    case F:
        return regw;
    default:
        return 0;
    }
}

static void segment(int n) {
}

static void progend(void) {
    print(":__scratch\n");
}

static void target(Node p) {
/*
    debug({
        fprintf(stderr, "target called on %x (%s)\n", p, opname(p->op));
        if (p->syms[RX])
            fprintf(stderr, "    sclass: %d, name: %s\n", p->syms[RX]->sclass, p->syms[RX]->name);           
        if (p->kids[0]) {
            fprintf(stderr, "    %x (%s)\n", p->kids[0], opname(p->kids[0]->op));
            if (p->kids[0]->syms[RX])
                fprintf(stderr, "        sclass: %d, name: %s\n", p->kids[0]->syms[RX]->sclass, p->kids[0]->syms[RX]->name);
        }
        if (p->kids[1]) {
            fprintf(stderr, "    %x (%s)\n", p->kids[1], opname(p->kids[1]->op));
            if (p->kids[1]->syms[RX])
                fprintf(stderr, "        sclass: %d, name: %s\n", p->kids[1]->syms[RX]->sclass, p->kids[1]->syms[RX]->name);
        }
    });
*/
    assert(p);
    switch (specific(p->op)) {
        case RET+F:
        case RET+I:
        case RET+U:
        case RET+P:
            rtarget(p, 0, reg[RGA]);
            break;
        case CALL+F:
        case CALL+I:
        case CALL+U:
        case CALL+P:
            setreg(p, reg[RGA]);
            break;
        
               
    }

/*
    debug({
        fprintf(stderr, "target returning on %x (%s)\n", p, opname(p->op));
        if (p->syms[RX])
            fprintf(stderr, "    sclass: %d, name: %s\n", p->syms[RX]->sclass, p->syms[RX]->name);           
        if (p->kids[0]) {
            fprintf(stderr, "    %x (%s)\n", p->kids[0], opname(p->kids[0]->op));
            if (p->kids[0]->syms[RX])
                fprintf(stderr, "        sclass: %d, name: %s\n", p->kids[0]->syms[RX]->sclass, p->kids[0]->syms[RX]->name);
        }
        if (p->kids[1]) {
            fprintf(stderr, "    %x (%s)\n", p->kids[1], opname(p->kids[1]->op));
            if (p->kids[1]->syms[RX])
                fprintf(stderr, "        sclass: %d, name: %s\n", p->kids[1]->syms[RX]->sclass, p->kids[1]->syms[RX]->name);
        }
    });
*/
}

static void clobber(Node p) {
    int opsz;
    assert(p);
        
    opsz = opsize(p->op);
    switch (specific(p->op)) {
        case MUL+F:
            if (opsz == 1)
                spill(1<<RGX, IREG, p);
            break;
    }
}


static void emit2(Node p) {
    int localoffset;
    int argoffset;
    long intval;
    long double fltval;
    int op = specific(p->op);
    int opsz = opsize(p->op);

    switch(op) {
        case CNST+F:
            fltval = p->syms[0]->u.c.v.d;
            if ( fltval < 0 )
                emithex((short)(fltval*256));
            else
                printf("%d", (short)(fltval*256));
            break;
        case CNST+I:
            intval = p->syms[0]->u.c.v.i;
            if ( intval < 0 )
                emithex((short)intval);                
            else
                print("%d", intval);
            break;
        case ARG+F: case ARG+I: case ARG+U: case ARG+P:
            break;
        case CALL+F: case CALL+I: case CALL+U: case CALL+P:
            argoffset = p->syms[0]->u.c.v.i;
            popstack(argoffset);
            break;
        case ADDRL+P:
            localoffset = p->syms[0]->x.offset + maxoffset;
            if ( localoffset )
                print("%d+J", localoffset);
            else
                print("J");
            break;
        case ADDRF+P:
            print("%d+J", p->syms[0]->x.offset);
            break;
    }
}

static void emithex(short i) {
    printf("0x%c%c%c%c", hexdigits[i >> 12 & 0x000f], hexdigits[i >> 8 & 0x000f], hexdigits[i >> 4 & 0x000f], hexdigits[i & 0x000f]);
}

static void doarg(Node p) {
    assert(p && p->syms[0]);
    debug(fprintf(stderr, "doarg called %ld\n", p->syms[0]->u.c.v.i));
    mkactual(1, p->syms[0]->u.c.v.i);
    debug(fprintf(stderr, "doarg done with argoffset=%d\n", argoffset));
}

static void blkfetch(int k, int off, int reg, int tmp) {}
static void blkstore(int k, int off, int reg, int tmp) {}
static void blkloop(int dreg, int doff, int sreg, int soff,int size, int tmps[]) {}

static void local(Symbol p) {
    debug(fprintf(stderr, "local called on '%s'\n", p->name));
    if (askregvar(p,(*IR->x.rmap)(ttob(p->type)))==0) {
        mkauto(p);
    }
}

static void function(Symbol f, Symbol caller[], Symbol callee[], int n) {
    int i,nreg,nfreg,nargs;
    long fused;
    Symbol fs;
    
    usedmask[IREG] = 0;
    usedmask[FREG] = 0;
    freemask[IREG] = TMP_REG | VAR_REG | (1<<RGA);
    freemask[FREG] = 0;

    maxargoffset = 0;
    offset = maxoffset = 0;

    for (i=0; callee[i]; i++) {
        Symbol p = callee[i];
        Symbol q = caller[i];
        assert(q);
        p->x.offset = q->x.offset = offset;
        p->x.name = q->x.name = stringf("%d",p->x.offset);
        p->sclass = q->sclass = AUTO;
        offset += roundup(q->type->size,q->type->align);
    }

    debug(fprintf(stderr, "function: calling gencode\n"));

    gencode(caller, callee);

    offset = maxoffset + 2;
    if (f->type->size > 1) {
        offset += f->type->size;
    }

    for (i=0; callee[i]; i++) {
        Symbol p = callee[i];
        Symbol q = caller[i];
        assert(q);
        p->x.offset = q->x.offset = offset;
        p->x.name = q->x.name = stringf("%d",p->x.offset);
        p->sclass = q->sclass = AUTO;
        offset += roundup(q->type->size,q->type->align);
    }

    // prologue
    print(":%s ;maxoffset: %d maxargoffset: %d\n", f->x.name, maxoffset, maxargoffset);
    print("SET PUSH, J\n");

    //push locals
    pushstack(maxoffset);

    print("SET J, SP\n");

    emitcode();

    //epilogue

    //pop locals
    popstack(maxoffset);

    print("SET J, POP\n");
    print("SET PC, POP\n");
}

static void defsymbol(Symbol p) {
    debug({
        if (p->type)
            fprintf(stderr, "defsymbol called on %s %d\n", p->name, p->type->op);
        else
            fprintf(stderr, "defsymbol called on %s %d\n", p->name, p->scope);

    });
    if (p->scope >= LOCAL && p->sclass == STATIC)
        p->x.name = stringf("_%d", genlabel(1));
    else if (p->generated)
        p->x.name = stringf("_L%s", p->name);
    else if (p->scope == GLOBAL || p->sclass == EXTERN)
        p->x.name = stringf("_%s",p->name);
    else if (p->scope == CONSTANTS && (isint(p->type) || isptr(p->type)) && p->name[0] == '0' && p->name[1] == 'x')
        p->x.name = stringf("_%s", &p->name[2]);
    else
        p->x.name = p->name;
}

static void address(Symbol q, Symbol p, long n) {
        if (p->scope == GLOBAL || p->sclass == STATIC || p->sclass == EXTERN)
                q->x.name = stringf("%s%s%D", p->x.name, n >= 0 ? "+" : "", n);
        else {
                assert(n <= INT_MAX && n >= INT_MIN);
                q->x.offset = p->x.offset + n;
                q->x.name = stringd(q->x.offset);
        }
}

static void defconst(int suffix, int size, Value v) {
    if (suffix == F && size == 1) {
        if ( v.d < 0 ) {
            print("DAT ");
            emithex((short)(v.d*256));
            print(" ;%f\n", v.d);
        }
        else {
            print("DAT %d ;%f\n", (short)(v.d*256), v.d);
        }
    }
    else if (suffix == I && size == 1) {
        if (v.i < 0 ) {
            print("DAT ");
            emithex((short)v.i);
            print(" ;%d\n", v.i);
        }
        else {
            print("DAT %d\n");
        }
    }
    else if (suffix == U && size == 1) {
        print("DAT %d\n", (unsigned)v.u);
    }
    else if (suffix == P && size == 1) {
        print("DAT %d\n", (unsigned)v.p);
    }
    else assert(0);
}

static void defaddress(Symbol p) {
    print("DAT %s\n", p->x.name);
}

static void defstring(int n, char *str) {
    int i;
    for ( i = 0; i < n; i++ ) {
        short v = (short)(*(str+i));
        print("DAT ");
        emithex(v);
        print(" ;%c\n", *(str+i));
    }
}

static void export(Symbol p) {
    debug(fprintf(stderr, "export called\n"));
}

static void import(Symbol p) {
    debug(fprintf(stderr, "import called\n"));
}

static void global(Symbol p) {
    //assert(p->type->align == 1);
    print(":%s\n", p->x.name);
}

static void space(int n) {
    int i;
    for (i = 0; i < n; i++)
        print("DAT 0\n", n);
}

static void pushstack(int n) {
    if (n > 1)
        print("SUB SP, %d\n", n);
    else if (n == 1)
        print("SET PUSH, 0\n");
}

static void popstack(int n) {
    if (n > 2)
        print("ADD SP, %d\n", n);
    else if (n == 2)
        print("SET POP, POP\n", n);
    else if (n == 1)
        print("SET POP, SP\n");
}

static int memop(Node p, int defaultcost) {
    assert(p);
    assert(generic(p->op) == ASGN);
    assert(p->kids[0]);
    assert(p->kids[1]);

    if (generic(p->kids[1]->kids[0]->op) == INDIR && sametree(p->kids[0], p->kids[1]->kids[0]->kids[0]))
        return defaultcost;
    else
        return LBURG_MAX;
}

static int ncmemop(Node p, int defaultcost) {
    assert(p);
    assert(generic(p->op) == ASGN);
    assert(p->kids[0]);
    assert(p->kids[1]);
  
    if (generic(p->kids[1]->kids[1]->op) == INDIR && sametree(p->kids[0], p->kids[1]->kids[1]->kids[0]))
        return LBURG_MAX;

    return defaultcost;
}

static int sametree(Node p, Node q) {
        return p == NULL && q == NULL
        || p && q && p->op == q->op && p->syms[0] == q->syms[0]
                && sametree(p->kids[0], q->kids[0])
                && sametree(p->kids[1], q->kids[1]);
}

Interface dcpu16IR = {
        1, 1, 0,  /* char */
        1, 1, 0,  /* short */
        1, 1, 0,  /* int */
        2, 2, 0,  /* long */
        4, 4, 0,  /* long long */
        1, 1, 0,  /* float */
        2, 2, 0,  /* double */
        4, 4, 0,  /* long double */
        1, 1, 0,  /* T * */
        0, 1, 0,  /* struct */
        0,        /* little_endian */
        1,        /* mulops_calls */
        0,        /* wants_callb */
        0,        /* wants_argb */
        0,        /* left_to_right */
        0,        /* wants_dag */
        1,        /* unsigned_char */
        16,       /* width */
        address,
        blockbeg,
        blockend,
        defaddress,
        defconst,
        defstring,
        defsymbol,
        emit,
        export,
        function,
        gen,
        global,
        import,
        local,
        progbeg,
        progend,
        segment,
        space,
        0, 0, 0, 0, 0, 0, 0,
        {1, rmap,
            blkfetch, blkstore, blkloop,
            _label,
            _rule,
            _nts,
            _kids,
            _string,
            _templates,
            _isinstruction,
            _ntname,
            emit2,
            doarg,
            target,
            clobber,
}
};
static char rcsid[] = "$Id: $";
