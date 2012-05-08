#include <dcpulib.h>
#include <color.h>

#ifndef _H_TEST
#define _H_TEST

#define TEST 25

#if TEST == 15

#define TEST2 12

#else

#define TEST2 13

#endif

#endif

int main()
{
    int i = TEST;
    int j = TEST2;
    boolean b = TRUE;

    return EXIT_SUCCESS;
}
