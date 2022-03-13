#include "io_bridge.h"

static void wifi_io_bridge_init();
static void camera_io_bridge_init();
static void touchscreen_io_bridge_init();

int fd;
void *virtual_base;

/* Reference: https://www.ee.ryerson.ca/~courses/coe838/labs/HPS-FPGA-Interconnect.pdf */
int io_bridge_init() {
    int fd;

        // Open memory as if it were a device for read and write access
        if( ( fd = open( "/dev/mem", ( O_RDWR | O_SYNC ) ) ) == -1 ) {
                printf( "ERROR: could not open \"/dev/mem\"...\n" );
                return 0;
        }

        // map 2Mbyte of memory starting at 0xFF200000 to user space
        virtual_base = mmap( NULL, HW_REGS_SPAN, ( PROT_READ | PROT_WRITE ),
        MAP_SHARED, fd, HW_REGS_BASE );

        if( virtual_base == MAP_FAILED ) {
                printf( "ERROR: mmap() failed...\n" );
                close( fd );
                return 0;
        }
    wifi_io_bridge_init();
    camera_io_bridge_init();
    touchscreen_io_bridge_init();

    return 1;
}
/* Deallocate mapping*/
void io_bridge_deallocate() {
    if (munmap(virtual_base, HW_REGS_SPAN) != 0) {
        printf("~io_bridge_init: munmap() failed to deallocate mapping...\n");
    }
    if (fd >= 0) {
        close(fd);
        fd = -1;
    }
}
/* Set up vaddr for wifi module */
static void wifi_io_bridge_init() {
    /* todo */
}

/* Set up vaddr for camera module */
static void camera_io_bridge_init() {
    /* todo */
}

/* Set up vaddr for touch screen controller */
static void touchscreen_io_bridge_init() {
    TOUCHSCREEN_VADDR_ReceiverFifo =               (unsigned short int *) (virtual_base + (TOUCHSCREEN_PADDR_ReceiverFifo               & HW_REGS_MASK));
    TOUCHSCREEN_VADDR_TransmitterFifo =            (unsigned short int *) (virtual_base + (TOUCHSCREEN_PADDR_TransmitterFifo            & HW_REGS_MASK));
    TOUCHSCREEN_VADDR_InterruptEnableReg =         (unsigned short int *) (virtual_base + (TOUCHSCREEN_PADDR_InterruptEnableReg         & HW_REGS_MASK));
    TOUCHSCREEN_VADDR_InterruptIdentificationReg = (unsigned short int *) (virtual_base + (TOUCHSCREEN_PADDR_InterruptIdentificationReg & HW_REGS_MASK));
    TOUCHSCREEN_VADDR_FifoControlReg =             (unsigned short int *) (virtual_base + (TOUCHSCREEN_PADDR_FifoControlReg             & HW_REGS_MASK));
    TOUCHSCREEN_VADDR_LineControlReg =             (unsigned short int *) (virtual_base + (TOUCHSCREEN_PADDR_LineControlReg             & HW_REGS_MASK));
    TOUCHSCREEN_VADDR_ModemControlReg =            (unsigned short int *) (virtual_base + (TOUCHSCREEN_PADDR_ModemControlReg            & HW_REGS_MASK));
    TOUCHSCREEN_VADDR_LineStatusReg =              (unsigned short int *) (virtual_base + (TOUCHSCREEN_PADDR_LineStatusReg              & HW_REGS_MASK));
    TOUCHSCREEN_VADDR_ModemStatusReg =             (unsigned short int *) (virtual_base + (TOUCHSCREEN_PADDR_ModemStatusReg             & HW_REGS_MASK));
    TOUCHSCREEN_VADDR_ScratchReg =                 (unsigned short int *) (virtual_base + (TOUCHSCREEN_PADDR_ScratchReg                 & HW_REGS_MASK));
    TOUCHSCREEN_VADDR_DivisorLatchLSB =            (unsigned short int *) (virtual_base + (TOUCHSCREEN_PADDR_DivisorLatchLSB            & HW_REGS_MASK));
    TOUCHSCREEN_VADDR_DivisorLatchMSB =            (unsigned short int *) (virtual_base + (TOUCHSCREEN_PADDR_DivisorLatchMSB            & HW_REGS_MASK));
}
