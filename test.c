#include <stdlib.h>
#include <stdio.h>
#include <hardware.h>
#include <color.h>
#include <driver-hmd.h>
#include <random.h>

void listener(int);

int main()
{
    setinterruptlistener(&listener);

    return EXIT_SUCCESS;
}

void listener(int code)
{

}
