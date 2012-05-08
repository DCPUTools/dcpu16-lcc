#ifndef DRIVER_HDD_H_
#define DRIVER_HDD_H_

// Constants
#define QUERY_MEDIA_PRESENT         0x0000
#define QUERY_MEDIA_PARAMETERS      0x0001
#define QUERY_DEVICE_FLAGS          0x0002
#define UPDATE_DEVICE_FLAGS         0x0003
#define QUERY_INTERRUPT_TYPE        0x0004
#define SET_INTERRUPT_MESSAGE       0x0005
#define READ_SECTORS                0x0010
#define WRITE_SECTORS               0x0011
#define QUERY_MEDIA_QUALITY         0xFFFF

#define TYPE_NONE                   0x0000
#define TYPE_MEDIA_STATUS           0x0001
#define TYPE_READ_COMPLETE          0x0002
#define TYPE_WRITE_COMPLETE         0x0003

#define QUALITY_AUTHENTIC           0x7FFF
#define QUALITY_OTHER               0xFFFF

#define DRIVE_ERROR_NONE            0x0000
#define DRIVE_ERROR_NO_MEDIA        0x0001
#define DRIVE_ERROR_INVALID_SECTOR  0x0002
#define DRIVE_ERROR_PENDING         0x0003

// Types
typedef struct {
    int words_per_sector;
    int sectors_num;
    int writeable;
} drive;

// Methods
extern int mediapresent();
extern void mediaparameters(drive);

#endif
