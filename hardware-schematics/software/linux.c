#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#define HW_REGS_BASE 							( 0xff200000 )
#define HW_REGS_SPAN 							( 0x00200000 )
#define HW_REGS_MASK 							( HW_REGS_SPAN - 1 )

#define Wifi_ReceiverFifoOffset 				(0x00010200)
#define Wifi_TransmitterFifoOffset 				(0x00010200)
#define Wifi_InterruptEnableRegOffset 			(0x00010202)
#define Wifi_InterruptIdentificationRegOffset 	(0x00010204)
#define Wifi_FifoControlRegOffset 				(0x00010204)
#define Wifi_LineControlRegOffset 				(0x00010206)
#define Wifi_ModemControlRegOffset 				(0x00010208)
#define Wifi_LineStatusRegOffset 				(0x0001020A)
#define Wifi_ModemStatusRegOffset 				(0x0001020C)
#define Wifi_ScratchRegOffset 					(0x0001020E)
#define Wifi_DivisorLatchLSBOffset				(0x00010200)
#define Wifi_DivisorLatchMSBOffset 				(0x00010202)

#define Wifi_LineControlReg_WordLengthSelect0 0
#define Wifi_LineControlReg_WordLengthSelect1 1
#define Wifi_LineControlReg_DivisorLatchAccessBit 7

#define Wifi_FifoControlReg_ReceiveFIFOReset 1
#define Wifi_FifoControlReg_TransmitFIFOReset 2

#define Wifi_LineStatusReg_DataReady 0
#define Wifi_LineStatusReg_TransmitterHoldingRegister 5

void * virtual_base = NULL;

volatile unsigned char *Wifi_ReceiverFifo = NULL;
volatile unsigned char *Wifi_TransmitterFifo = NULL;
volatile unsigned char *Wifi_InterruptEnableReg = NULL;
volatile unsigned char *Wifi_InterruptIdentificationReg = NULL;
volatile unsigned char *Wifi_FifoControlReg = NULL;
volatile unsigned char *Wifi_LineControlReg = NULL;
volatile unsigned char *Wifi_ModemControlReg = NULL;
volatile unsigned char *Wifi_LineStatusReg = NULL;
volatile unsigned char *Wifi_ModemStatusReg = NULL;
volatile unsigned char *Wifi_ScratchReg = NULL;
volatile unsigned char *Wifi_DivisorLatchLSB = NULL;
volatile unsigned char *Wifi_DivisorLatchMSB = NULL;

void init_wifi_serial()
{
	Wifi_ReceiverFifo =(unsigned short int *)(virtual_base + (( Wifi_ReceiverFifoOffset ) &
		(HW_REGS_MASK ) ));
	if (Wifi_ReceiverFifo == NULL) {
		printf("ERROR, Wifi_ReceiverFifo was not correctly defined. Try again");
	}

	Wifi_TransmitterFifo =(unsigned short int *)(virtual_base + (( Wifi_TransmitterFifoOffset ) &
		(HW_REGS_MASK ) ));
	if (Wifi_TransmitterFifo == NULL) {
		printf("ERROR, Wifi_TransmitterFifo was not correctly defined. Try again");
	}

	Wifi_InterruptEnableReg =(unsigned short int *)(virtual_base + (( Wifi_InterruptEnableRegOffset ) &
		(HW_REGS_MASK ) ));
	if (Wifi_InterruptEnableReg == NULL) {
		printf("ERROR, Wifi_InterruptEnableReg was not correctly defined. Try again");
	}

	Wifi_InterruptIdentificationReg =(unsigned short int *)(virtual_base + (( Wifi_InterruptIdentificationRegOffset ) &
		(HW_REGS_MASK ) ));
	if (Wifi_InterruptIdentificationReg == NULL) {
		printf("ERROR, Wifi_InterruptIdentificationReg was not correctly defined. Try again");
	}

	Wifi_FifoControlReg =(unsigned short int *)(virtual_base + (( Wifi_FifoControlRegOffset ) &
		(HW_REGS_MASK ) ));
	if (Wifi_FifoControlReg == NULL) {
		printf("ERROR, Wifi_FifoControlReg was not correctly defined. Try again");
	}

	Wifi_LineControlReg =(unsigned short int *)(virtual_base + (( Wifi_LineControlRegOffset ) &
		(HW_REGS_MASK ) ));
	if (Wifi_LineControlReg == NULL) {
		printf("ERROR, Wifi_LineControlReg was not correctly defined. Try again");
	}

	Wifi_ModemControlReg =(unsigned short int *)(virtual_base + (( Wifi_ModemControlRegOffset ) &
		(HW_REGS_MASK ) ));
	if (Wifi_ModemControlReg == NULL) {
		printf("ERROR, Wifi_ModemControlReg was not correctly defined. Try again");
	}

	Wifi_LineStatusReg =(unsigned short int *)(virtual_base + (( Wifi_LineStatusRegOffset ) &
		(HW_REGS_MASK ) ));
	if (Wifi_LineStatusReg == NULL) {
		printf("ERROR, Wifi_LineStatusReg was not correctly defined. Try again");
	}

	Wifi_ModemStatusReg =(unsigned short int *)(virtual_base + (( Wifi_ModemStatusRegOffset ) &
		(HW_REGS_MASK ) ));
	if (Wifi_ModemStatusReg == NULL) {
		printf("ERROR, Wifi_ModemStatusReg was not correctly defined. Try again");
	}

	Wifi_ScratchReg =(unsigned short int *)(virtual_base + (( Wifi_ScratchRegOffset ) &
		(HW_REGS_MASK ) ));
	if (Wifi_ScratchReg == NULL) {
		printf("ERROR, Wifi_ScratchReg was not correctly defined. Try again");
	}

	Wifi_DivisorLatchLSB =(unsigned short int *)(virtual_base + (( Wifi_DivisorLatchLSBOffset ) &
		(HW_REGS_MASK ) ));
	if (Wifi_DivisorLatchLSB == NULL) {
		printf("ERROR, Wifi_DivisorLatchLSB was not correctly defined. Try again");
	}

	Wifi_DivisorLatchMSB =(unsigned short int *)(virtual_base + (( Wifi_DivisorLatchMSBOffset ) &
		(HW_REGS_MASK ) ));
	if (Wifi_DivisorLatchMSB == NULL) {
		printf("ERROR, Wifi_DivisorLatchMSB was not correctly defined. Try again");
	}

 // set bit 7 of Line Control Register to 1, to gain access to the baud rate registers
    *Wifi_LineControlReg = 0x80;

 // set Divisor latch (LSB and MSB) with correct value for required baud rate
 // This is for baudrate of 9600
    *Wifi_DivisorLatchLSB = 0x1b;
    *Wifi_DivisorLatchMSB = 0x00;

 // Reset bits to 0
    *Wifi_LineControlReg = 0x00;

 // set bit 7 of Line control register back to 0 and
 // program other bits in that reg for 8 bit data, 1 stop bit, no parity etc
    *Wifi_LineControlReg = 0x03;

 // Reset the Fifo’s in the FiFo Control Reg by setting bits 1 & 2
    *Wifi_FifoControlReg = 0x06;

 // Now Clear all bits in the FiFo control registers
    *Wifi_FifoControlReg = 0x00;
}

int put_char_wifi(int c)
{
 // wait for Transmitter Holding Register bit (5) of line status register to be '1'
 // indicating we can write to the device
    while ((*Wifi_LineStatusReg & 0x20) != 0x20) {
    }

 // write character to Transmitter fifo register
    *Wifi_TransmitterFifo = c;

 // return the character we printed
    return c;
}

// the following function polls the UART to determine if any character
// has been received. It doesn't wait for one, or read it, it simply tests
// to see if one is available to read from the FIFO
int wifi_test_for_received_data(void)
{
 // if Wifi_LineStatusReg bit 0 is set to 1
 //return TRUE, otherwise return FALSE
    return ((*Wifi_LineStatusReg >> Wifi_LineStatusReg_DataReady) & 1) == 1;
}

int get_char_wifi( void )
{
 // wait for Data Ready bit (0) of line status register to be '1'
    while(!wifi_test_for_received_data()) {
    }

 // read new character from ReceiverFiFo register
 // return new character
    return *Wifi_ReceiverFifo;
}

//
// Remove/flush the UART receiver buffer by removing any unread characters
//
void flush_wifi(void)
{
 // while bit 0 of Line Status Register == ‘1’
 // read unwanted char out of fifo receiver buffer
    while(wifi_test_for_received_data()) {
        int read = *Wifi_ReceiverFifo;
        read += 1;
    }

    return; // no more characters so return
}

int lua_command_no_stars(char * str, char * res, int timeout) {
	int i;
	int bytes_received = 0;
	printf("executing %s\n", str);

	// Put the command into the buffer
	while (*str) {
		put_char_wifi(*str);
		str++;

		// Get any data that may be coming back after writing the last char
		for(i=0; i<1000; i++) {
			if(wifi_test_for_received_data() == 1) {
				res[bytes_received++] = get_char_wifi();
			}
		}
	}

	// Before the timeout expires, try to get data
	int j;
	for(j=0; j<timeout; j++){
		if(wifi_test_for_received_data() == 1) {
			res[bytes_received++] = get_char_wifi();
			j=0; // reset the timeout timer if you got data
		}
	}

	res[bytes_received] = '\0';

	return bytes_received;
}

int lua_command_no_stars_short(char * str, char * res) {
	return lua_command_no_stars(str, res, 200000);
}


void do_file(void)
{
	char * command = "dofile(\"hello.lua\")\r\n";
	char buf[1024] = "";
	lua_command_no_stars_short(command, buf);

	printf("%s\n", buf);
}

int init_wifi(void)
{
	init_wifi_serial(virtual_base);
	flush_wifi();
	do_file();
	return 0;
}

int main(int argc, char **argv)
{

	int fd;

	// Open memory as if it were a device for read and write access
	if( ( fd = open( "/dev/mem", ( O_RDWR | O_SYNC ) ) ) == -1 ) {
		printf( "ERROR: could not open \"/dev/mem\"...\n" );
		return( 1 );
	}

	// map 2Mbyte of memory starting at 0xFF200000 to user space
	virtual_base = mmap( NULL, HW_REGS_SPAN, ( PROT_READ | PROT_WRITE ),
	MAP_SHARED, fd, HW_REGS_BASE );

	if( virtual_base == MAP_FAILED ) {
		printf( "ERROR: mmap() failed...\n" );
		close( fd );
		return(1);
	}

	// if(!init_wifi()) {
	// 	return 0;
	// }
    printf("Finish Wifi Setup");

	return 0;
}