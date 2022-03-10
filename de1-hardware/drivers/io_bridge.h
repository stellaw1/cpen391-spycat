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
#define TOUCHSCREEN_PADDR_ReceiverFifo 				    (0xFF210230)
#define TOUCHSCREEN_PADDR_TransmitterFifo				(0xFF210230)
#define TOUCHSCREEN_PADDR_InterruptEnableReg 			(0xFF210232)
#define TOUCHSCREEN_PADDR_InterruptIdentificationReg 	(0xFF210234)
#define TOUCHSCREEN_PADDR_FifoControlReg 				(0xFF210234)
#define TOUCHSCREEN_PADDR_LineControlReg 				(0xFF210236)
#define TOUCHSCREEN_PADDR_ModemControlReg				(0xFF210238)
#define TOUCHSCREEN_PADDR_LineStatusReg 				(0xFF21023A)
#define TOUCHSCREEN_PADDR_ModemStatusReg 				(0xFF21023C)
#define TOUCHSCREEN_PADDR_ScratchReg 					(0xFF21023E)
#define TOUCHSCREEN_PADDR_DivisorLatchLSB 				(0xFF210230)
#define TOUCHSCREEN_PADDR_DivisorLatchMSB 				(0xFF210232)

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

/*
 * Set the virtual addresses for hardware up
 */
void io_bridge_init();

/**
 * free up the virtual addresses
 */
void io_bridge_deallocate();

#endif
