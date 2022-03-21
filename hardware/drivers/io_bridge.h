/************************************************************************************
 * Setup virtual memories for accessing to the peripheral devices connected to DE1 
 * GPIOs
 * Introduce virtual addresses to process based on the physical addresses
 * 
 * - Wi-Fi Module
 * - GPIO Camera Module
 * - Touch Screen Controller
 ***********************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#ifndef IO_BRIDGE_H_ /* Include Guard */
#define IO_BRIDGE_H_

/* Refered to DE1-SoC User Manual */
#define HW_REGS_BASE ( 0xff200000 )
#define HW_REGS_SPAN ( 0x00200000 )
#define HW_REGS_MASK ( HW_REGS_SPAN - 1 )

/* Wi-Fi Module */

/* GPIO Camera Module */

/* Touch Screen Controller */
#define TOUCHSCREEN_PADDR_ReceiverFifo 				    (0x10230)
#define TOUCHSCREEN_PADDR_TransmitterFifo				(0x10230)
#define TOUCHSCREEN_PADDR_InterruptEnableReg 			(0x10232)
#define TOUCHSCREEN_PADDR_InterruptIdentificationReg 	(0x10234)
#define TOUCHSCREEN_PADDR_FifoControlReg 				(0x10234)
#define TOUCHSCREEN_PADDR_LineControlReg 				(0x10236)
#define TOUCHSCREEN_PADDR_ModemControlReg				(0x10238)
#define TOUCHSCREEN_PADDR_LineStatusReg 				(0x1023A)
#define TOUCHSCREEN_PADDR_ModemStatusReg 				(0x1023C)
#define TOUCHSCREEN_PADDR_ScratchReg 					(0x1023E)
#define TOUCHSCREEN_PADDR_DivisorLatchLSB 				(0x10230)
#define TOUCHSCREEN_PADDR_DivisorLatchMSB 				(0x10232)

volatile unsigned short int *TOUCHSCREEN_VADDR_ReceiverFifo;
volatile unsigned short int *TOUCHSCREEN_VADDR_TransmitterFifo;
volatile unsigned short int *TOUCHSCREEN_VADDR_InterruptEnableReg;
volatile unsigned short int *TOUCHSCREEN_VADDR_InterruptIdentificationReg;
volatile unsigned short int *TOUCHSCREEN_VADDR_FifoControlReg;
volatile unsigned short int *TOUCHSCREEN_VADDR_LineControlReg;
volatile unsigned short int *TOUCHSCREEN_VADDR_ModemControlReg;
volatile unsigned short int *TOUCHSCREEN_VADDR_LineStatusReg;
volatile unsigned short int *TOUCHSCREEN_VADDR_ModemStatusReg;
volatile unsigned short int *TOUCHSCREEN_VADDR_ScratchReg;
volatile unsigned short int *TOUCHSCREEN_VADDR_DivisorLatchLSB;
volatile unsigned short int *TOUCHSCREEN_VADDR_DivisorLatchMSB;

/* VGA Graphics Controller */
#define GraphicsCommandReg_PADDR                        (0x10000)
#define GraphicsStatusReg_PADDR                         (0x10000)
#define GraphicsX1Reg_PADDR                             (0x10002)
#define GraphicsY1Reg_PADDR                             (0x10004)
#define GraphicsX2Reg_PADDR                             (0x10006)
#define GraphicsY2Reg_PADDR                             (0x10008)
#define GraphicsColourReg_PADDR                         (0x1000E)
#define GraphicsBackGroundColourReg_PADDR               (0x10010)

volatile unsigned short int *GraphicsCommandReg;   		
volatile unsigned short int *GraphicsStatusReg;   		
volatile unsigned short int *GraphicsX1Reg;   			
volatile unsigned short int *GraphicsY1Reg;   			
volatile unsigned short int *GraphicsX2Reg;   			
volatile unsigned short int *GraphicsY2Reg;   			
volatile unsigned short int *GraphicsColourReg;   		
volatile unsigned short int *GraphicsBackGroundColourReg; 

/*
 * Set the virtual addresses for hardware up
 */
int io_bridge_init();

/**
 * free up the virtual addresses
 */
void io_bridge_deallocate();

#endif

