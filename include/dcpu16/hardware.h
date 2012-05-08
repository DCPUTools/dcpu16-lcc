#ifndef __HARDWARE
#define __HARDWARE

// Types
typedef struct
{
    unsigned int id;
    unsigned int version;
    unsigned int manufacturer;
} device;

// Methods
extern int connectedhardwaredevices();
extern void getdeviceinformations(int, device*);
extern void triggerhardwareinterrupt(int);

#endif
