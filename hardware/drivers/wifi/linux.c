#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>

#define HW_REGS_BASE 							( 0xff200000 )
#define HW_REGS_SPAN 							( 0x00200000 )
#define HW_REGS_MASK 							( HW_REGS_SPAN - 1 )

#define Wifi_ReceiverFifo						(volatile unsigned char *)(virtual_base + ((0xFF210200)&(HW_REGS_MASK)))
#define Wifi_TransmitterFifo					(volatile unsigned char *)(virtual_base + ((0xFF210200)&(HW_REGS_MASK)))
#define Wifi_InterruptEnableReg					(volatile unsigned char *)(virtual_base + ((0xFF210202)&(HW_REGS_MASK)))
#define Wifi_InterruptIdentificationReg			(volatile unsigned char *)(virtual_base + ((0xFF210204)&(HW_REGS_MASK)))
#define Wifi_FifoControlReg						(volatile unsigned char *)(virtual_base + ((0xFF210204)&(HW_REGS_MASK)))
#define Wifi_LineControlReg						(volatile unsigned char *)(virtual_base + ((0xFF210206)&(HW_REGS_MASK)))
#define Wifi_ModemControlReg					(volatile unsigned char *)(virtual_base + ((0xFF210208)&(HW_REGS_MASK)))
#define Wifi_LineStatusReg						(volatile unsigned char *)(virtual_base + ((0xFF21020A)&(HW_REGS_MASK)))
#define Wifi_ModemStatusReg						(volatile unsigned char *)(virtual_base + ((0xFF21020C)&(HW_REGS_MASK)))
#define Wifi_ScratchReg							(volatile unsigned char *)(virtual_base + ((0xFF21020E)&(HW_REGS_MASK)))
#define Wifi_DivisorLatchLSB					(volatile unsigned char *)(virtual_base + ((0xFF210200)&(HW_REGS_MASK)))
#define Wifi_DivisorLatchMSB					(volatile unsigned char *)(virtual_base + ((0xFF210202)&(HW_REGS_MASK)))

#define Wifi_LineControlReg_WordLengthSelect0 0
#define Wifi_LineControlReg_WordLengthSelect1 1
#define Wifi_LineControlReg_DivisorLatchAccessBit 7

#define Wifi_FifoControlReg_ReceiveFIFOReset 1
#define Wifi_FifoControlReg_TransmitFIFOReset 2

#define Wifi_LineStatusReg_DataReady 0
#define Wifi_LineStatusReg_TransmitterHoldingRegister 5

void * virtual_base;

void init_wifi_ports(void)
{
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

int lua_command_stars(char * str, char * res) {
	int i;

	int bytes_received = 0;
	printf("executing %s\n", str);

	char star = '*';
	int star_count = 0;

	while (*str) {
		put_char_wifi(*str);
		str++;

		for(i=0; i<1000; i++) {
			if(wifi_test_for_received_data() == 1) {
				char c = get_char_wifi();

				if (c == star) { // Start counting * characters
					star_count++;

					if (star_count == 4) { // break if we received the last * character
						res[bytes_received] = '\0';

						return bytes_received;
					}
				} else { // reset the star counter
					while(star_count > 0) {
						res[bytes_received++] = star;
						star_count--;
					}
					res[bytes_received++] = c;
				}
			}
		}
	}

	for(i=0; i<30000000; i++) { // start the timeout counter
		if(wifi_test_for_received_data() == 1) {
			char c = get_char_wifi();

			if (c == star) { // start counting stars
				star_count++;
				if (star_count == 4) { // stop receiving data because last star is received
					res[bytes_received] = '\0';

					return bytes_received;
				}
			} else { // reset the star counter
				while(star_count > 0) {
					res[bytes_received++] = star;
					star_count--;
				}
				res[bytes_received++] = c;
			}

			i = 0; // reset the timeout timer if we received data
		}
	}
	
	res[bytes_received] = '\0';

	return bytes_received;
}

int lua_command_no_stars_short(char * str, char * res) {
	return lua_command_no_stars(str, res, 20000000);
}

void do_file(void)
{
	char * command = "dofile(\"wifi.lua\")\r\n";
	char buf[1024] = "";
	int bytes_received = lua_command_no_stars_short(command, buf);

	printf("bytes received: %d\n", bytes_received);
	printf("%s\n", buf);
}

int init_wifi(void)
{
	init_wifi_ports();
	flush_wifi();
	do_file();
	return 0;
}

int hello_world(void)
{
	char * command = "hello_world()\r\n";

	char buf[1024] = "";
	int bytes_received = lua_command_no_stars_short(command, buf);

	printf("bytes received: %d\n", bytes_received);
	printf("%s\n", buf);

	return 0;
}

int main(int argc, char **argv)
{

	int fd;

	// setup lw bridge
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

    printf("Start Wifi Setup \n");
	init_wifi();
    printf("Finish Wifi Setup \n");

    printf("Start Hello World \n");
	hello_world();
    printf("Finish Hello World \n");

	return 0;
}