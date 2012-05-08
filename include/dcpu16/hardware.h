#ifndef __HARDWARE
#define __HARDWARE

// Types
typedef struct
{
    unsigned int id[2];
    unsigned int version;
    unsigned int manufacturer[2];
} device;

// Methods
extern int connectedhardwaredevices();
extern void getdeviceinformations(int, device*);
extern void triggerhardwareinterrupt(int);

#endif
