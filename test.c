#include <stdlib.h>
#include <stdio.h>
#include <hardware.h>
#include <color.h>
#include <driver-hmd.h>

void devices();
void drives();
void printdevice(int);

int main()
{
    while (TRUE)
    {
        int n = connectedhardwaredevices();

        printf("Connected devices: %d\n", n);
        printf("------------------\n");

        printdevice(1);
        setdispcur(0);
    }

    return EXIT_SUCCESS;
}

void devices()
{
    int n = connectedhardwaredevices();
    int i;

    for (i = 0; i < n; i++)
    {
        printdevice(i);
    }
}

void printdevice(int a)
{
    device d;

    getdeviceinformations(a, d);

    printf("Device ID:      0x%x\n", d.id);
    printf("Device version: 0x%x\n", d.version);
    printf("Device man.:    0x%x\n", d.manufacturer);
}

void drives()
{
    int i = mediapresent();

    if (i)
    {
        drive drive;

        mediaparameters(drive);

        printf("Drive!\n");
        printf("Word/sec    = %d\n", drive.words_per_sector);
        printf("Num sectors = %d\n", drive.sectors_num);
        printf("Writeable   = %d\n", drive.writeable);
    }
    else
    {
        printf("No drive!");
    }
}
