#include <stdlib.h>
#include <stdio.h>
#include <hardware.h>

void printdevice(int);

int main()
{
    int n = connectedhardwaredevices();

    if (n > 0)
    {
        printdevice(0);

        setdispcur(0);
    }

    return EXIT_SUCCESS;
}

void printdevice(int a)
{
    device d;

    getdeviceinformations(a, &d);

    printf("ID:           %x%x", d.id[1], d.id[0]); // Must use arrays instead of long :(
    printf("Version:      %x", d.version);
    printf("Manufacturer: %x%x", d.manufacturer[1], d.manufacturer[0]);
}
