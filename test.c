#include <dcpulib.h>
#include <color.h>

void listener(int code);

int main()
{
    setinterruptlistener(&listener);
    triggerinterrupt(21);

    return EXIT_SUCCESS;
}

void listener(int code)
{
    printf("Code: %d\n", code);
}
