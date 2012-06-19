%{
#include "dcpu16.i.h"
%}

%start stmt
%term CNSTF1=1041
%term CNSTI1=1045
%term CNSTI2=2069
%term CNSTP1=1047
%term CNSTU1=1046
%term CNSTU2=2070

%term ARGB=41
%term ARGF1=1057
%term ARGI1=1061
%term ARGP1=1063
%term ARGU1=1062
%term ARGU2=2086

%term ASGNB=57
%term ASGNF1=1073
%term ASGNI1=1077
%term ASGNI2=2101
%term ASGNP1=1079
%term ASGNU1=1078
%term ASGNU2=2102

%term INDIRB=73
%term INDIRF1=1089
%term INDIRI1=1093
%term INDIRI2=2117
%term INDIRP1=1095
%term INDIRU1=1094
%term INDIRU2=2118

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
%term LOADI2=2277
%term LOADU1=1254

%%

reg:    LOADF1(reg) "?SET %c, %0\n" move(a)
reg:    LOADI1(reg) "?SET %c, %0\n" move(a)
reg:    LOADI2(reg) "?SET %c, %0\n" move(a)
reg:    LOADU1(reg) "?SET %c, %0\n" move(a)
reg:    LOADP1(reg) "?SET %c, %0\n" move(a)

reg:    INDIRF1(VREGP)  "# read register\n"
reg:    INDIRI1(VREGP)  "# read register\n"
reg:    INDIRI2(VREGP)  "# read register\n"
reg:    INDIRU1(VREGP)  "# read register\n"
reg:    INDIRU2(VREGP)  "# read register\n"
reg:    INDIRP1(VREGP)  "# read register\n"

stmt:   ASGNF1(VREGP,reg)   "# write register\n"
stmt:   ASGNI1(VREGP,reg)   "# write register\n"
stmt:   ASGNI2(VREGP,reg)   "# write register\n"
stmt:   ASGNU1(VREGP,reg)   "# write register\n"
stmt:   ASGNU2(VREGP,reg)   "# write register\n"
stmt:   ASGNP1(VREGP,reg)   "# write register\n"

stmt:   reg ""

con:    CNSTF1  "#" 1
con:    CNSTI1  "#" 1
con:	CNSTI2  "#" 1
con:    CNSTU1  "%a" 1
con:    CNSTU2  "%a" 1
con:    CNSTP1  "%a" 1

acon:   CNSTU1  "%a" 1
acon:   CNSTP1  "%a" 1

saddr:   acon            "%0"
saddr:   reg             "%0"
saddr:   ADDRGP1         "%a"
caddr:   ADDRFP1         "#" 1
caddr:   ADDRLP1         "#" 1

addr:   ADDI1(reg,acon) "%1+%0"
addr:   ADDP1(reg,acon) "%1+%0"
addr:   saddr           "%0"
addr:   caddr           "%0"
    
reg:    con     "SET %c, %0\n" 1
reg:    mem     "SET %c, %0\n" 1
reg:    saddr   "SET %c, %0\n" 1
reg:    ADDRLP1 "#\n" 2

mem:    INDIRF1(addr)   "[%0]"
mem:    INDIRI1(addr)   "[%0]"
mem:    INDIRI2(addr)   "[%0]"
mem:    INDIRU1(addr)   "[%0]"
mem:    INDIRU2(addr)   "[%0]"
mem:    INDIRP1(addr)   "[%0]"

bval:   reg     "%0"
bval:   con     "%0"
bval:   mem     "%0"

cm:     con     "%0"
cm:     mem     "%0"

stmt:   ASGNF1(addr,bval)               "SET [%0], %1\n" 1
stmt:   ASGNI1(addr,bval)               "SET [%0], %1\n" 1
stmt:   ASGNI2(addr,bval)               "SET [%0], %1\n" 1
stmt:   ASGNU1(addr,bval)               "SET [%0], %1\n" 1
stmt:   ASGNU2(addr,bval)               "SET [%0], %1\n" 1
stmt:   ASGNP1(addr,bval)               "SET [%0], %1\n" 1

reg:    BCOMI1(cm)                      "SET %c, 0xffff\nXOR %c, %0\n" 3
reg:    BCOMU1(cm)                      "SET %c, 0xffff\nXOR %c, %0\n" 3
reg:    BCOMI1(reg)                     "SET %c, 0xffff\nXOR %c, %0\n" regopu(a, 3)
reg:    BCOMU1(reg)                     "SET %c, 0xffff\nXOR %c, %0\n" regopu(a, 3)
reg:    BCOMI1(reg)                     "SET I, %0\nSET %c, 0xffff\nXOR %c, I\n" 4
reg:    BCOMU1(reg)                     "SET I, %0\nSET %c, 0xffff\nXOR %c, I\n" 4
stmt:   ASGNI1(addr,BCOMI1(bval))       "SET [%0], 0xffff\nXOR [%0], %1\n" memopu(a, 3)
stmt:   ASGNI2(addr,BCOMI1(bval))       "SET [%0], 0xffff\nXOR [%0], %1\n" memopu(a, 3)
stmt:   ASGNU1(addr,BCOMU1(bval))       "SET [%0], 0xffff\nXOR [%0], %1\n" memopu(a, 3)
stmt:   ASGNU2(addr,BCOMU1(bval))       "SET [%0], 0xffff\nXOR [%0], %1\n" memopu(a, 3)
stmt:   ASGNI1(addr,BCOMI1(mem))        "SET I, %1\nSET [%0], 0xffff\nXOR [%0], I\n" 4
stmt:   ASGNI2(addr,BCOMI1(mem))        "SET I, %1\nSET [%0], 0xffff\nXOR [%0], I\n" 4
stmt:   ASGNU1(addr,BCOMU1(mem))        "SET I, %1\nSET [%0], 0xffff\nXOR [%0], I\n" 4
stmt:   ASGNU2(addr,BCOMU1(mem))        "SET I, %1\nSET [%0], 0xffff\nXOR [%0], I\n" 4
                                        
reg:    CVFI1(bval)                     "?SET %c, %0\nSHR %c, 8\n" 4
stmt:   ASGNI1(addr,CVFI1(bval))        "SET [%0], %1\nSHR [%0], 8\n" 4
stmt:   ASGNI2(addr,CVFI1(bval))        "SET [%0], %1\nSHR [%0], 8\n" 4
                                        
reg:    CVIF1(bval)                     "?SET %c, %0\nSHL %c, 8\n" 4
reg:    CVIU1(bval)                     "?SET %c, %0\n" 1
stmt:   ASGNF1(addr,CVIF1(bval))        "SET [%0], %1\nSHL [%0], 8\n" 4
stmt:   ASGNU1(addr,CVIF1(bval))        "SET [%0], %1\n" 1
stmt:   ASGNU2(addr,CVIF1(bval))        "SET [%0], %1\n" 1
                                        
reg:    CVUI1(bval)                     "?SET %c, %0\n" 1
reg:    CVUP1(bval)                     "?SET %c, %0\n" 1
stmt:   ASGNI1(addr,CVUI1(bval))        "SET [%0], %1\n" 1
stmt:   ASGNI2(addr,CVUI1(bval))        "SET [%0], %1\n" 1
stmt:   ASGNP1(addr,CVUP1(bval))        "SET [%0], %1\n" 1
                                        
reg:    CVPU1(bval)                     "?SET %c, %0\n" 1
stmt:   ASGNU1(addr,CVPU1(bval))        "SET [%0], %1\n" 1
stmt:   ASGNU2(addr,CVPU1(bval))        "SET [%0], %1\n" 1
                                        
reg:    NEGF1(cm)                       "SET %c, 0\nSUB %c, %0\n" 4
reg:    NEGI1(cm)                       "SET %c, 0\nSUB %c, %0\n" 4
reg:    NEGF1(reg)                      "SET %c, 0\nSUB %c, %0\n" regopu(a, 4)
reg:    NEGI1(reg)                      "SET %c, 0\nSUB %c, %0\n" regopu(a, 4)
reg:    NEGF1(reg)                      "SET I, %0\nSET %c, 0\nSUB %c, I\n" 5
reg:    NEGI1(reg)                      "SET I, %0\nSET %c, 0\nSUB %c, I\n" 5
stmt:   ASGNF1(addr,NEGF1(bval))        "SET [%0], 0\nSUB [%0], %1\n" memopu(a, 4)
stmt:   ASGNI1(addr,NEGI1(bval))        "SET [%0], 0\nSUB [%0], %1\n" memopu(a, 4)
stmt:   ASGNI2(addr,NEGI1(bval))        "SET [%0], 0\nSUB [%0], %1\n" memopu(a, 4)
stmt:   ASGNF1(addr,NEGF1(mem))         "SET I, %1\nSET [%0], 0\nSUB [%0], I\n" 5
stmt:   ASGNI1(addr,NEGI1(mem))         "SET I, %1\nSET [%0], 0\nSUB [%0], I\n" 5
stmt:   ASGNI2(addr,NEGI1(mem))         "SET I, %1\nSET [%0], 0\nSUB [%0], I\n" 5

reg:    ADDF1(reg,cm)                   "?SET %c, %0\nADD %c, %1\n" 3
reg:    ADDI1(reg,cm)                   "?SET %c, %0\nADD %c, %1\n" 3
reg:    ADDU1(reg,cm)                   "?SET %c, %0\nADD %c, %1\n" 3
reg:    ADDP1(reg,cm)                   "?SET %c, %0\nADD %c, %1\n" 3
reg:    ADDF1(reg,reg)                  "?SET %c, %0\nADD %c, %1\n" ncregop(a, 3)
reg:    ADDI1(reg,reg)                  "?SET %c, %0\nADD %c, %1\n" ncregop(a, 3)
reg:    ADDU1(reg,reg)                  "?SET %c, %0\nADD %c, %1\n" ncregop(a, 3)
reg:    ADDP1(reg,reg)                  "?SET %c, %0\nADD %c, %1\n" ncregop(a, 3)
reg:    ADDF1(bval,reg)                 "SET I, %1\nSET %c, %0\nADD %c, I\n" 4
reg:    ADDI1(bval,reg)                 "SET I, %1\nSET %c, %0\nADD %c, I\n" 4
reg:    ADDU1(bval,reg)                 "SET I, %1\nSET %c, %0\nADD %c, I\n" 4
reg:    ADDP1(bval,reg)                 "SET I, %1\nSET %c, %0\nADD %c, I\n" 4
reg:    ADDP1(bval,reg)                 "SET I, %1\nSET %c, %0\nADD %c, I\n" 4
stmt:   ASGNF1(addr,ADDF1(bval,bval))   "ADD [%0], %2\n" memop(a, 2) 
stmt:   ASGNI1(addr,ADDI1(bval,bval))   "ADD [%0], %2\n" memop(a, 2)
stmt:   ASGNI2(addr,ADDI1(bval,bval))   "ADD [%0], %2\n" memop(a, 2)
stmt:   ASGNU1(addr,ADDU1(bval,bval))   "ADD [%0], %2\n" memop(a, 2)
stmt:   ASGNU2(addr,ADDU1(bval,bval))   "ADD [%0], %2\n" memop(a, 2)
stmt:   ASGNP1(addr,ADDP1(bval,bval))   "ADD [%0], %2\n" memop(a, 2)
stmt:   ASGNF1(addr,ADDF1(bval,bval))   "SET [%0], %1\nADD [%0], %2\n" ncmemop(a, 3)
stmt:   ASGNI1(addr,ADDI1(bval,bval))   "SET [%0], %1\nADD [%0], %2\n" ncmemop(a, 3)
stmt:   ASGNI2(addr,ADDI1(bval,bval))   "SET [%0], %1\nADD [%0], %2\n" ncmemop(a, 3)
stmt:   ASGNU1(addr,ADDU1(bval,bval))   "SET [%0], %1\nADD [%0], %2\n" ncmemop(a, 3)
stmt:   ASGNU2(addr,ADDU1(bval,bval))   "SET [%0], %1\nADD [%0], %2\n" ncmemop(a, 3)
stmt:   ASGNP1(addr,ADDP1(bval,bval))   "SET [%0], %1\nADD [%0], %2\n" ncmemop(a, 3)
stmt:   ASGNF1(addr,ADDF1(bval,mem))    "SET I, %2\nSET [%0], %1\nADD [%0], I\n" 6
stmt:   ASGNI1(addr,ADDI1(bval,mem))    "SET I, %2\nSET [%0], %1\nADD [%0], I\n" 6
stmt:   ASGNI2(addr,ADDI1(bval,mem))    "SET I, %2\nSET [%0], %1\nADD [%0], I\n" 6
stmt:   ASGNU1(addr,ADDU1(bval,mem))    "SET I, %2\nSET [%0], %1\nADD [%0], I\n" 6
stmt:   ASGNU2(addr,ADDU1(bval,mem))    "SET I, %2\nSET [%0], %1\nADD [%0], I\n" 6
stmt:   ASGNP1(addr,ADDP1(bval,mem))    "SET I, %2\nSET [%0], %1\nADD [%0], I\n" 6

reg:    BANDI1(reg,cm)                  "?SET %c, %0\nAND %c, %1\n" 2
reg:    BANDU1(reg,cm)                  "?SET %c, %0\nAND %c, %1\n" 2
reg:    BANDI1(reg,reg)                 "?SET %c, %0\nAND %c, %1\n" ncregop(a, 2)
reg:    BANDU1(reg,reg)                 "?SET %c, %0\nAND %c, %1\n" ncregop(a, 2)
reg:    BANDI1(bval,reg)                "SET I, %1\nSET %c, %0\nAND %c, I\n" 3
reg:    BANDU1(bval,reg)                "SET I, %1\nSET %c, %0\nAND %c, I\n" 3
stmt:   ASGNI1(addr,BANDI1(bval,bval))  "AND [%0], %2\n" memop(a, 1)
stmt:   ASGNI2(addr,BANDI1(bval,bval))  "AND [%0], %2\n" memop(a, 1)
stmt:   ASGNU1(addr,BANDU1(bval,bval))  "AND [%0], %2\n" memop(a, 1)
stmt:   ASGNU2(addr,BANDU1(bval,bval))  "AND [%0], %2\n" memop(a, 1)
stmt:   ASGNI1(addr,BANDI1(bval,bval))  "SET [%0], %1\nAND [%0], %2\n" ncmemop(a, 2)
stmt:   ASGNI2(addr,BANDI1(bval,bval))  "SET [%0], %1\nAND [%0], %2\n" ncmemop(a, 2)
stmt:   ASGNU1(addr,BANDU1(bval,bval))  "SET [%0], %1\nAND [%0], %2\n" ncmemop(a, 2)
stmt:   ASGNU2(addr,BANDU1(bval,bval))  "SET [%0], %1\nAND [%0], %2\n" ncmemop(a, 2)
stmt:   ASGNI1(addr,BANDI1(bval,mem))   "SET I, %2\nSET [%0], %1\nAND [%0], I\n" 3
stmt:   ASGNI2(addr,BANDI1(bval,mem))   "SET I, %2\nSET [%0], %1\nAND [%0], I\n" 3
stmt:   ASGNU1(addr,BANDU1(bval,mem))   "SET I, %2\nSET [%0], %1\nAND [%0], I\n" 3
stmt:   ASGNU2(addr,BANDU1(bval,mem))   "SET I, %2\nSET [%0], %1\nAND [%0], I\n" 3

reg:    BORI1(bval,cm)                  "?SET %c, %0\nBOR %c, %1\n" 2
reg:    BORU1(bval,cm)                  "?SET %c, %0\nBOR %c, %1\n" 2
reg:    BORI1(bval,reg)                 "?SET %c, %0\nBOR %c, %1\n" ncregop(a, 2)
reg:    BORU1(bval,reg)                 "?SET %c, %0\nBOR %c, %1\n" ncregop(a, 2)
reg:    BORI1(bval,reg)                 "SET I, %1\nSET %c, %0\nBOR %c, I\n" 3
reg:    BORU1(bval,reg)                 "SET I, %1\nSET %c, %0\nBOR %c, I\n" 3
stmt:   ASGNI1(addr,BORI1(bval,bval))   "BOR [%0], %2\n" memop(a, 1)
stmt:   ASGNI2(addr,BORI1(bval,bval))   "BOR [%0], %2\n" memop(a, 1)
stmt:   ASGNU1(addr,BORU1(bval,bval))   "BOR [%0], %2\n" memop(a, 1)
stmt:   ASGNU2(addr,BORU1(bval,bval))   "BOR [%0], %2\n" memop(a, 1)
stmt:   ASGNI1(addr,BORI1(bval,bval))   "SET [%0], %1\nBOR [%0], %2\n" ncmemop(a, 2)
stmt:   ASGNI2(addr,BORI1(bval,bval))   "SET [%0], %1\nBOR [%0], %2\n" ncmemop(a, 2)
stmt:   ASGNU1(addr,BORU1(bval,bval))   "SET [%0], %1\nBOR [%0], %2\n" ncmemop(a, 2)
stmt:   ASGNU2(addr,BORU1(bval,bval))   "SET [%0], %1\nBOR [%0], %2\n" ncmemop(a, 2)
stmt:   ASGNI1(addr,BORI1(bval,mem))    "SET I, %2\nSET [%0], %1\nBOR [%0], I\n" 3
stmt:   ASGNI2(addr,BORI1(bval,mem))    "SET I, %2\nSET [%0], %1\nBOR [%0], I\n" 3
stmt:   ASGNU1(addr,BORU1(bval,mem))    "SET I, %2\nSET [%0], %1\nBOR [%0], I\n" 3
stmt:   ASGNU2(addr,BORU1(bval,mem))    "SET I, %2\nSET [%0], %1\nBOR [%0], I\n" 3

reg:    BXORI1(bval,cm)                 "?SET %c, %0\nXOR %c, %1\n" 2
reg:    BXORU1(bval,cm)                 "?SET %c, %0\nXOR %c, %1\n" 2
reg:    BXORI1(bval,reg)                "?SET %c, %0\nXOR %c, %1\n" ncregop(a, 2)
reg:    BXORU1(bval,reg)                "?SET %c, %0\nXOR %c, %1\n" ncregop(a, 2)
reg:    BXORI1(bval,reg)                "SET I, %1\nSET %c, %0\nXOR %c, I\n" 3
reg:    BXORU1(bval,reg)                "SET I, %1\nSET %c, %0\nXOR %c, I\n" 3
stmt:   ASGNI1(addr,BXORI1(bval,bval))  "XOR [%0], %2\n" memop(a, 1)
stmt:   ASGNI2(addr,BXORI1(bval,bval))  "XOR [%0], %2\n" memop(a, 1)
stmt:   ASGNU1(addr,BXORU1(bval,bval))  "XOR [%0], %2\n" memop(a, 1)
stmt:   ASGNU2(addr,BXORU1(bval,bval))  "XOR [%0], %2\n" memop(a, 1)
stmt:   ASGNI1(addr,BXORI1(bval,bval))  "SET [%0], %1\nXOR [%0], %2\n" ncmemop(a, 2)
stmt:   ASGNI2(addr,BXORI1(bval,bval))  "SET [%0], %1\nXOR [%0], %2\n" ncmemop(a, 2)
stmt:   ASGNU1(addr,BXORU1(bval,bval))  "SET [%0], %1\nXOR [%0], %2\n" ncmemop(a, 2)
stmt:   ASGNU2(addr,BXORU1(bval,bval))  "SET [%0], %1\nXOR [%0], %2\n" ncmemop(a, 2)
stmt:   ASGNI1(addr,BXORI1(bval,mem))   "SET I, %2\nSET [%0], %1\nXOR [%0], I\n" 3
stmt:   ASGNI2(addr,BXORI1(bval,mem))   "SET I, %2\nSET [%0], %1\nXOR [%0], I\n" 3
stmt:   ASGNU1(addr,BXORU1(bval,mem))   "SET I, %2\nSET [%0], %1\nXOR [%0], I\n" 3
stmt:   ASGNU2(addr,BXORU1(bval,mem))   "SET I, %2\nSET [%0], %1\nXOR [%0], I\n" 3

reg:    DIVF1(reg,cm)                   "?SET %c, %0\nDIV %c, %1\n" 4
reg:    DIVI1(reg,cm)                   "?SET %c, %0\nDIV %c, %1\n" 4
reg:    DIVU1(reg,cm)                   "?SET %c, %0\nDIV %c, %1\n" 4
reg:    DIVF1(reg,reg)                  "?SET %c, %0\nDIV %c, %1\n" ncregop(a, 4)
reg:    DIVI1(reg,reg)                  "?SET %c, %0\nDIV %c, %1\n" ncregop(a, 4)
reg:    DIVU1(reg,reg)                  "?SET %c, %0\nDIV %c, %1\n" ncregop(a, 4)
reg:    DIVF1(bval,reg)                 "SET I, %1\nSET %c, %0\nDIV %c, I\n" 5
reg:    DIVI1(bval,reg)                 "SET I, %1\nSET %c, %0\nDIV %c, I\n" 5
reg:    DIVU1(bval,reg)                 "SET I, %1\nSET %c, %0\nDIV %c, I\n" 5
stmt:   ASGNF1(addr,DIVF1(bval,bval))   "DIV [%0], %2\n" memop(a, 3)
stmt:   ASGNI1(addr,DIVI1(bval,bval))   "DIV [%0], %2\n" memop(a, 3)
stmt:   ASGNI2(addr,DIVI1(bval,bval))   "DIV [%0], %2\n" memop(a, 3)
stmt:   ASGNU1(addr,DIVU1(bval,bval))   "DIV [%0], %2\n" memop(a, 3)
stmt:   ASGNU2(addr,DIVU1(bval,bval))   "DIV [%0], %2\n" memop(a, 3)
stmt:   ASGNF1(addr,DIVF1(bval,bval))   "SET [%0], %1\nDIV [%0], %2\n" ncmemop(a, 4) 
stmt:   ASGNI1(addr,DIVI1(bval,bval))   "SET [%0], %1\nDIV [%0], %2\n" ncmemop(a, 4)
stmt:   ASGNI2(addr,DIVI1(bval,bval))   "SET [%0], %1\nDIV [%0], %2\n" ncmemop(a, 4)
stmt:   ASGNU1(addr,DIVU1(bval,bval))   "SET [%0], %1\nDIV [%0], %2\n" ncmemop(a, 4)
stmt:   ASGNU2(addr,DIVU1(bval,bval))   "SET [%0], %1\nDIV [%0], %2\n" ncmemop(a, 4)
stmt:   ASGNF1(addr,DIVF1(bval,mem))    "SET I, %2\nSET [%0], %1\nDIV [%0], I\n" 5
stmt:   ASGNI1(addr,DIVI1(bval,mem))    "SET I, %2\nSET [%0], %1\nDIV [%0], I\n" 5
stmt:   ASGNI2(addr,DIVI1(bval,mem))    "SET I, %2\nSET [%0], %1\nDIV [%0], I\n" 5
stmt:   ASGNU1(addr,DIVU1(bval,mem))    "SET I, %2\nSET [%0], %1\nDIV [%0], I\n" 5
stmt:   ASGNU2(addr,DIVU1(bval,mem))    "SET I, %2\nSET [%0], %1\nDIV [%0], I\n" 5

reg:    LSHI1(reg,cm)                   "?SET %c, %0\nSHL %c, %1\n" 3
reg:    LSHU1(reg,cm)                   "?SET %c, %0\nSHL %c, %1\n" 3
reg:    LSHI1(reg,reg)                  "?SET %c, %0\nSHL %c, %1\n" ncregop(a, 3)
reg:    LSHU1(reg,reg)                  "?SET %c, %0\nSHL %c, %1\n" ncregop(a, 3)
reg:    LSHI1(bval,reg)                 "SET I, %1\nSET %c, %0\nSHL %c, I\n" 4
reg:    LSHU1(bval,reg)                 "SET I, %1\nSET %c, %0\nSHL %c, I\n" 4
stmt:   ASGNI1(addr,LSHI1(bval,bval))   "SHL [%0], %2\n" memop(a, 2)
stmt:   ASGNI2(addr,LSHI1(bval,bval))   "SHL [%0], %2\n" memop(a, 2)
stmt:   ASGNU1(addr,LSHU1(bval,bval))   "SHL [%0], %2\n" memop(a, 2)
stmt:   ASGNU2(addr,LSHU1(bval,bval))   "SHL [%0], %2\n" memop(a, 2)
stmt:   ASGNI1(addr,LSHI1(bval,bval))   "SET [%0], %1\nSHL [%0], %2\n" ncmemop(a, 3)
stmt:   ASGNI2(addr,LSHI1(bval,bval))   "SET [%0], %1\nSHL [%0], %2\n" ncmemop(a, 3)
stmt:   ASGNU1(addr,LSHU1(bval,bval))   "SET [%0], %1\nSHL [%0], %2\n" ncmemop(a, 3)
stmt:   ASGNU2(addr,LSHU1(bval,bval))   "SET [%0], %1\nSHL [%0], %2\n" ncmemop(a, 3)
stmt:   ASGNI1(addr,LSHI1(bval,mem))    "SET I, %2\nSET [%0], %1\nSHL [%0], I\n" 4
stmt:   ASGNI2(addr,LSHI1(bval,mem))    "SET I, %2\nSET [%0], %1\nSHL [%0], I\n" 4
stmt:   ASGNU1(addr,LSHU1(bval,mem))    "SET I, %2\nSET [%0], %1\nSHL [%0], I\n" 4
stmt:   ASGNU2(addr,LSHU1(bval,mem))    "SET I, %2\nSET [%0], %1\nSHL [%0], I\n" 4

reg:    MODI1(reg,cm)                   "?SET %c, %0\nMOD %c, %1\n" 4
reg:    MODU1(reg,cm)                   "?SET %c, %0\nMOD %c, %1\n" 4
reg:    MODI1(reg,reg)                  "?SET %c, %0\nMOD %c, %1\n" ncregop(a, 4)
reg:    MODU1(reg,reg)                  "?SET %c, %0\nMOD %c, %1\n" ncregop(a, 4)
reg:    MODI1(bval,reg)                 "?SET %c, %0\nSET I, %1\nMOD %c, I\n" 5
reg:    MODU1(bval,reg)                 "?SET %c, %0\nSET I, %1\nMOD %c, I\n" 5
stmt:   ASGNI1(addr,MODI1(bval,bval))   "MOD [%0], %2\n" memop(a, 3)
stmt:   ASGNI2(addr,MODI1(bval,bval))   "MOD [%0], %2\n" memop(a, 3)
stmt:   ASGNU1(addr,MODU1(bval,bval))   "MOD [%0], %2\n" memop(a, 3)
stmt:   ASGNU2(addr,MODU1(bval,bval))   "MOD [%0], %2\n" memop(a, 3)
stmt:   ASGNI1(addr,MODI1(bval,bval))   "SET [%0], %1\nMOD [%0], %2\n" ncmemop(a, 4)
stmt:   ASGNI2(addr,MODI1(bval,bval))   "SET [%0], %1\nMOD [%0], %2\n" ncmemop(a, 4)
stmt:   ASGNU1(addr,MODU1(bval,bval))   "SET [%0], %1\nMOD [%0], %2\n" ncmemop(a, 4)
stmt:   ASGNU2(addr,MODU1(bval,bval))   "SET [%0], %1\nMOD [%0], %2\n" ncmemop(a, 4)
stmt:   ASGNI1(addr,MODI1(bval,mem))    "SET I, %2\nSET [%0], %1\nMOD [%0], I\n" 5
stmt:   ASGNI2(addr,MODI1(bval,mem))    "SET I, %2\nSET [%0], %1\nMOD [%0], I\n" 5
stmt:   ASGNU1(addr,MODU1(bval,mem))    "SET I, %2\nSET [%0], %1\nMOD [%0], I\n" 5
stmt:   ASGNU2(addr,MODU1(bval,mem))    "SET I, %2\nSET [%0], %1\nMOD [%0], I\n" 5

reg:    MULF1(reg,cm)                   "?SET %c, %0\nMUL %c, %1\nSET I, EX\nSHR %c, 8\nSHL I, 8\nADD %c, X\n" 12
reg:    MULI1(reg,cm)                   "?SET %c, %0\nMUL %c, %1\n" 3
reg:    MULU1(reg,cm)                   "?SET %c, %0\nMUL %c, %1\n" 3
reg:    MULF1(reg,reg)                  "?SET %c, %0\nMUL %c, %1\nSET I, EX\nSHR %c, 8\nSHL I, 8\nADD %c, X\n" ncregop(a, 12)
reg:    MULI1(reg,reg)                  "?SET %c, %0\nMUL %c, %1\n" ncregop(a, 3)
reg:    MULU1(reg,reg)                  "?SET %c, %0\nMUL %c, %1\n" ncregop(a, 3)
reg:    MULF1(bval,reg)                 "SET [_scratch0], %1\nSET %c, %0\nMUL %c, [_scratch0]\nSET I, EX\nSHR %c, 8\nSHL I, 8\nADD %c, I\n" 13
reg:    MULI1(bval,reg)                 "SET I, %1\nSET %c, %0\nMUL %c, I\n" 4
reg:    MULU1(bval,reg)                 "SET I, %1\nSET %c, %0\nMUL %c, I\n" 4
stmt:   ASGNF1(addr,MULF1(bval,bval))   "MUL [%0], %2\nSET I, EX\nSHR [%0], 8\nSHL I, 8\nADD [%0], I\n" memop(a, 11)
stmt:   ASGNI1(addr,MULI1(bval,bval))   "MUL [%0], %2\n" memop(a, 2)
stmt:   ASGNI2(addr,MULI1(bval,bval))   "MUL [%0], %2\n" memop(a, 2)
stmt:   ASGNU1(addr,MULU1(bval,bval))   "MUL [%0], %2\n" memop(a, 2)
stmt:   ASGNU2(addr,MULU1(bval,bval))   "MUL [%0], %2\n" memop(a, 2)
stmt:   ASGNF1(addr,MULF1(bval,bval))   "SET [%0], %1\nMUL [%0], %2\nSET I, EX\nSHR [%0], 8\nSHL I, 8\nADD [%0], I\n" ncmemop(a, 12)
stmt:   ASGNI1(addr,MULI1(bval,bval))   "SET [%0], %1\nMUL [%0], %2\n" ncmemop(a, 3)
stmt:   ASGNI2(addr,MULI1(bval,bval))   "SET [%0], %1\nMUL [%0], %2\n" ncmemop(a, 3)
stmt:   ASGNU1(addr,MULU1(bval,bval))   "SET [%0], %1\nMUL [%0], %2\n" ncmemop(a, 3)
stmt:   ASGNU2(addr,MULU1(bval,bval))   "SET [%0], %1\nMUL [%0], %2\n" ncmemop(a, 3)
stmt:   ASGNF1(addr,MULF1(bval,mem))    "SET [_scratch0], %2\nSET [%0], %1\nMUL [%0], [_scratch0]\nSET I, EX\nSHR [%0], 8\nSHL I, 8\nADD [%0], I\n" 13
stmt:   ASGNI1(addr,MULI1(bval,mem))    "SET I, %2\nSET [%0], %1\nMUL [%0], I\n" 4
stmt:   ASGNI2(addr,MULI1(bval,mem))    "SET I, %2\nSET [%0], %1\nMUL [%0], I\n" 4
stmt:   ASGNU1(addr,MULU1(bval,mem))    "SET I, %2\nSET [%0], %1\nMUL [%0], I\n" 4
stmt:   ASGNU2(addr,MULU1(bval,mem))    "SET I, %2\nSET [%0], %1\nMUL [%0], I\n" 4

reg:    RSHI1(reg,cm)                   "?SET %c, %0\nSHR %c, %1\n" 3
reg:    RSHU1(reg,cm)                   "?SET %c, %0\nASR %c, %1\n" 3
reg:    RSHI1(reg,reg)                  "?SET %c, %0\nSHR %c, %1\n" ncregop(a, 3)
reg:    RSHU1(reg,reg)                  "?SET %c, %0\nASR %c, %1\n" ncregop(a, 3)
reg:    RSHI1(bval,reg)                 "SET I, %1\nSET %c, %0\nSHR %c, I\n" 4
reg:    RSHU1(bval,reg)                 "SET I, %1\nASR %c, %0\nSHR %c, I\n" 4
stmt:   ASGNI1(addr,RSHI1(bval,bval))   "SHR [%0], %2\n" memop(a, 2)
stmt:   ASGNI2(addr,RSHI1(bval,bval))   "SHR [%0], %2\n" memop(a, 2)
stmt:   ASGNU1(addr,RSHU1(bval,bval))   "ASR [%0], %2\n" memop(a, 2)
stmt:   ASGNU2(addr,RSHU1(bval,bval))   "SHR [%0], %2\n" memop(a, 2)
stmt:   ASGNI1(addr,RSHI1(bval,bval))   "SET [%0], %1\nSHR [%0], %2\n" ncmemop(a, 3)
stmt:   ASGNI2(addr,RSHI1(bval,bval))   "SET [%0], %1\nSHR [%0], %2\n" ncmemop(a, 3)
stmt:   ASGNU1(addr,RSHU1(bval,bval))   "SET [%0], %1\nASR [%0], %2\n" ncmemop(a, 3)
stmt:   ASGNU2(addr,RSHU1(bval,bval))   "SET [%0], %1\nSHR [%0], %2\n" ncmemop(a, 3)
stmt:   ASGNI1(addr,RSHI1(bval,mem))    "SET I, %2\nSET [%0], %1\nSHR [%0], I\n" 4
stmt:   ASGNI2(addr,RSHI1(bval,mem))    "SET I, %2\nSET [%0], %1\nSHR [%0], I\n" 4
stmt:   ASGNU1(addr,RSHU1(bval,mem))    "SET I, %2\nSET [%0], %1\nASR [%0], I\n" 4
stmt:   ASGNU2(addr,RSHU1(bval,mem))    "SET I, %2\nSET [%0], %1\nSHR [%0], I\n" 4

reg:    SUBF1(reg,cm)                   "?SET %c, %0\nSUB %c, %1\n" 3
reg:    SUBI1(reg,cm)                   "?SET %c, %0\nSUB %c, %1\n" 3
reg:    SUBU1(reg,cm)                   "?SET %c, %0\nSUB %c, %1\n" 3
reg:    SUBP1(reg,cm)                   "?SET %c, %0\nSUB %c, %1\n" 3
reg:    SUBF1(reg,reg)                  "?SET %c, %0\nSUB %c, %1\n" ncregop(a, 3)
reg:    SUBI1(reg,reg)                  "?SET %c, %0\nSUB %c, %1\n" ncregop(a, 3)
reg:    SUBU1(reg,reg)                  "?SET %c, %0\nSUB %c, %1\n" ncregop(a, 3)
reg:    SUBP1(reg,reg)                  "?SET %c, %0\nSUB %c, %1\n" ncregop(a, 3)
reg:    SUBF1(bval,reg)                 "SET I, %1\nSET %c, %0\nSUB %c, I\n" 4
reg:    SUBI1(bval,reg)                 "SET I, %1\nSET %c, %0\nSUB %c, I\n" 4
reg:    SUBU1(bval,reg)                 "SET I, %1\nSET %c, %0\nSUB %c, I\n" 4
reg:    SUBP1(bval,reg)                 "SET I, %1\nSET %c, %0\nSUB %c, I\n" 4
stmt:   ASGNF1(addr,SUBF1(bval,bval))   "SUB [%0], %2\n" memop(a, 2)
stmt:   ASGNI1(addr,SUBI1(bval,bval))   "SUB [%0], %2\n" memop(a, 2)
stmt:   ASGNI2(addr,SUBI1(bval,bval))   "SUB [%0], %2\n" memop(a, 2)
stmt:   ASGNU1(addr,SUBU1(bval,bval))   "SUB [%0], %2\n" memop(a, 2)
stmt:   ASGNU2(addr,SUBU1(bval,bval))   "SUB [%0], %2\n" memop(a, 2)
stmt:   ASGNP1(addr,SUBP1(bval,bval))   "SUB [%0], %2\n" memop(a, 2)
stmt:   ASGNF1(addr,SUBF1(bval,bval))   "SET [%0], %1\nSUB [%0], %2\n" ncmemop(a, 3)
stmt:   ASGNI1(addr,SUBI1(bval,bval))   "SET [%0], %1\nSUB [%0], %2\n" ncmemop(a, 3)
stmt:   ASGNI2(addr,SUBI1(bval,bval))   "SET [%0], %1\nSUB [%0], %2\n" ncmemop(a, 3)
stmt:   ASGNU1(addr,SUBU1(bval,bval))   "SET [%0], %1\nSUB [%0], %2\n" ncmemop(a, 3)
stmt:   ASGNU2(addr,SUBU1(bval,bval))   "SET [%0], %1\nSUB [%0], %2\n" ncmemop(a, 3)
stmt:   ASGNP1(addr,SUBP1(bval,bval))   "SET [%0], %1\nSUB [%0], %2\n" ncmemop(a, 3)
stmt:   ASGNF1(addr,SUBF1(bval,mem))    "SET I, %2\nSET [%0], %1\nSUB [%0], I\n" 4
stmt:   ASGNI1(addr,SUBI1(bval,mem))    "SET I, %2\nSET [%0], %1\nSUB [%0], I\n" 4
stmt:   ASGNI2(addr,SUBI1(bval,mem))    "SET I, %2\nSET [%0], %1\nSUB [%0], I\n" 4
stmt:   ASGNU1(addr,SUBU1(bval,mem))    "SET I, %2\nSET [%0], %1\nSUB [%0], I\n" 4
stmt:   ASGNU2(addr,SUBU1(bval,mem))    "SET I, %2\nSET [%0], %1\nSUB [%0], I\n" 4
stmt:   ASGNP1(addr,SUBP1(bval,mem))    "SET I, %2\nSET [%0], %1\nSUB [%0], I\n" 4

stmt:   EQF1(bval,bval)                 "IFE %0, %1\nSET PC, %a\n" 4 
stmt:   EQI1(bval,bval)                 "IFE %0, %1\nSET PC, %a\n" 4
stmt:   EQU1(bval,bval)                 "IFE %0, %1\nSET PC, %a\n" 4
                                        
stmt:   GEF1(bval,bval)                 "IFG %0, 0x7FFE\nSET PC, %a_nu\nIFG %1, 0x7FFE\nSET PC, %a\n:%a_nn\nIFG %0, %1\nSET PC, %a\nIFE %0, %1\nSET PC, %a\nSET PC, %a_done\n:%a_nu\nIFG %1, 0x7FFE \nSET PC, %a_nn\nSET PC, %a_done\n:%a_done\n" 15
stmt:   GEI1(bval,bval)                 "IFG %0, 0x7FFE\nSET PC, %a_nu\nIFG %1, 0x7FFE\nSET PC, %a\n:%a_nn\nIFG %0, %1\nSET PC, %a\nIFE %0, %1\nSET PC, %a\nSET PC, %a_done\n:%a_nu\nIFG %1, 0x7FFE \nSET PC, %a_nn\nSET PC, %a_done\n:%a_done\n" 15
stmt:   GEU1(bval,bval)                 "IFG %0, %1\nSET PC, %a\nIFE %0, %1\nSET PC, %a\n" 6
                                        
stmt:   GTF1(bval,bval)                 "IFG %0, 0x7FFE\nSET PC, %a_nu\nIFG %1, 0x7FFE\nSET PC, %a\n:%a_nn\nIFG %0, %1\nSET PC, %a\nSET PC, %a_done\n:%a_nu\nIFG %1, 0x7FFE\nSET PC, %a_nn\nSET PC, %a_done\n:%a_done\n" 13
stmt:   GTI1(bval,bval)                 "IFG %0, 0x7FFE\nSET PC, %a_nu\nIFG %1, 0x7FFE\nSET PC, %a\n:%a_nn\nIFG %0, %1\nSET PC, %a\nSET PC, %a_done\n:%a_nu\nIFG %1, 0x7FFE\nSET PC, %a_nn\nSET PC, %a_done\n:%a_done\n" 13
stmt:   GTU1(bval,bval)                 "IFG %0, %1\nSET PC, %a\n" 4
                                        
stmt:   LEF1(bval,bval)                 "IFG %1, 0x7FFE\nSET PC, %a_nu\nIFG %0, 0x7FFE\nSET PC, %a\n:%a_nn\nIFG %1, %0\nSET PC, %a\nIFE %1, %0\nSET PC, %a\nSET PC, %a_done\n:%a_nu\nIFG %0, 0x7FFE \nSET PC, %a_nn\nSET PC, %a_done\n:%a_done\n" 15
stmt:   LEI1(bval,bval)                 "IFG %1, 0x7FFE\nSET PC, %a_nu\nIFG %0, 0x7FFE\nSET PC, %a\n:%a_nn\nIFG %1, %0\nSET PC, %a\nIFE %1, %0\nSET PC, %a\nSET PC, %a_done\n:%a_nu\nIFG %0, 0x7FFE \nSET PC, %a_nn\nSET PC, %a_done\n:%a_done\n" 15
stmt:   LEU1(bval,bval)                 "IFG %1, %0\nSET PC, %a\nIFE %0, %1\nSET PC, %a\n" 6
                                        
stmt:   LTF1(bval,bval)                 "IFG %1, 0x7FFE\nSET PC, %a_nu\nIFG %0, 0x7FFE\nSET PC, %a\n:%a_nn\nIFG %1, %0\nSET PC, %a\nSET PC, %a_done\n:%a_nu\nIFG %0, 0x7FFE\nSET PC, %a_nn\nSET PC, %a_done\n:%a_done\n" 13
stmt:   LTI1(bval,bval)                 "IFG %1, 0x7FFE\nSET PC, %a_nu\nIFG %0, 0x7FFE\nSET PC, %a\n:%a_nn\nIFG %1, %0\nSET PC, %a\nSET PC, %a_done\n:%a_nu\nIFG %0, 0x7FFE\nSET PC, %a_nn\nSET PC, %a_done\n:%a_done\n" 13
stmt:   LTU1(bval,bval)                 "IFG %1, %0\nSET PC, %a\n" 4
                                        
stmt:   NEF1(bval,bval)                 "IFN %0, %1\nSET PC, %a\n" 4 
stmt:   NEI1(bval,bval)                 "IFN %0, %1\nSET PC, %a\n" 4
stmt:   NEU1(bval,bval)                 "IFN %0, %1\nSET PC, %a\n" 4

stmt:   ARGF1(reg)                      "#\n" a->x.argno < 3?0:LBURG_MAX
stmt:   ARGI1(reg)                      "#\n" a->x.argno < 3?0:LBURG_MAX
stmt:   ARGU1(reg)                      "#\n" a->x.argno < 3?0:LBURG_MAX
stmt:   ARGU2(reg)                      "#\n" a->x.argno < 3?0:LBURG_MAX
stmt:   ARGP1(reg)                      "#\n" a->x.argno < 3?0:LBURG_MAX
stmt:   ARGF1(bval)                     "#\n" 2
stmt:   ARGI1(bval)                     "#\n" 2
stmt:   ARGU1(bval)                     "#\n" 2
stmt:   ARGU2(bval)                     "#\n" 2
stmt:   ARGP1(bval)                     "#\n" 2
stmt:   ASGNB(reg,INDIRB(reg))          "# block assign\n" 1

reg:    CALLF1(addr)                    "#\n" 2
reg:    CALLI1(addr)                    "#\n" 2
reg:    CALLU1(addr)                    "#\n" 2
reg:    CALLP1(addr)                    "#\n" 2
stmt:   CALLV(addr)                     "#\n" 2

stmt:   RETF1(reg)                      "# return float\n" 2
stmt:   RETI1(reg)                      "# return int\n" 2
stmt:   RETU1(reg)                      "# return uint\n" 2
stmt:   RETP1(reg)                      "# return ptr\n" 2

stmt:   JUMPV(addr)                     "SET PC, %0\n" 1

stmt:   LABELV                          ":%a\n"

%%

#include "dcpu16.i.c"
