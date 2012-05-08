#include <stdlib.h>
#include <stdio.h>
#include <hardware.h>
#include <color.h>
#include <driver-hmd.h>
#include <random.h>

int main()
{
    int r;
    srand(0x2266);
    r = rand();
    printf("Rand: %d\n", r);
    r = rand();
    printf("Rand: %d\n", r);

    return EXIT_SUCCESS;
}
