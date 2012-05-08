#include <stdlib.h>
#include <stdio.h>

void listener(int);

int main()
{
    setinterruptlistener(&listener);

    return EXIT_SUCCESS;
}

void listener(int code)
{
    printf("Code: %d\n", code);
}
