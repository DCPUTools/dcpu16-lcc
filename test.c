#include <stdlib.h>
#include <stdio.h>
#include <color.h>
#include <driver-hmd.h>

int main()
{
    int present = mediapresent();

    printf("Present? %d\n", present);
    if (present)
    {
        printf("Drive!\n");
    }
    else
    {
        printf("No drive!\n");
    }

    return EXIT_SUCCESS;
}
