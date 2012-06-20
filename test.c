#include <stdio.h>
#include <stdlib.h>
#include <hardware.h>
#include <color.h>
#include <driver-hmd.h>
#include <random.h>
#include <time.h>
#include "test.h"

static unsigned a = 0;
unsigned b = 0;

void test(int y, int z, int i, int j)
{
    unsigned c, x;

    asm("SET A, [%a]");
    asm("SET B, [%b]");
    asm("SET C, [%c]");
    asm("SET X, [%x]");
    asm("SET Y, [%y]");
    asm("SET Z, [%z]");
    asm("SET I, [%i]");
    asm("SET J, [%j]");
}

void main()
{
    test(1,2,3,4);
}
