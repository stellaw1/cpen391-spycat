#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>

#define H2F_BRIDGE_BASE 							( 0x00000000 )
#define H2F_BRIDGE_SPAN 							( 0x3FFFFFFF )
#define H2F_BRIDGE_MASK 							( H2F_BRIDGE_SPAN )

#define HW_REGS_BASE 								( 0xff200000 )
#define HW_REGS_SPAN 								( 0x00200000 )
#define HW_REGS_MASK 								( HW_REGS_SPAN - 1 )

#define FIFO_BASE            						( 0xC0000000 )
#define FIFO_SPAN            						( 0x00001000 )

#define CAMERA_BASE 								( 0x02000000 )
#define CAMERA_WIDTH 								( 640 )
#define CAMERA_HEIGHT								( 480 )

#define EXTRA_MASK							        ( 0xFF000000 )
#define RED_MASK							        ( 0x00FF0000 )
#define GREEN_MASK							        ( 0x0000FF00 )
#define BLUE_MASK							        ( 0x000000FF )

#define READ_FIFO_FILL_LEVEL  (*FIFO_read_status_ptr)
#define READ_FIFO_FULL		  ((*(FIFO_read_status_ptr+1)) & 1 )
#define READ_FIFO_EMPTY	      ((*(FIFO_read_status_ptr+1)) & 2 )
#define FIFO_READ            (*(FIFO_read_ptr))

////////////////////////////////////
// HPS TO FPGA
////////////////////////////////////
#define FPGA_PIO_WRITE								( 0x40 )

////////////////////////////////////
// FPGA TO HPS
////////////////////////////////////
#define FIFO_READ_PTR_OFFSET						( 0x10 )
#define FIFO_READ_REG_OFFSET						( 0x100 )

void * lw_bridge_vbase;
volatile unsigned int * lw_pio_ptr = NULL ;
volatile unsigned int * FIFO_read_status_ptr = NULL ;

// HPS_to_FPGA FIFO write address
// main bus addess 0x0000_0000
void *h2p_virtual_base;
volatile unsigned int * FIFO_read_ptr = NULL ;

int main(int argc, char **argv)
{
	int fd;

	// setup lw bridge
	// Open memory as if it were a device for read and write access
	if( ( fd = open( "/dev/mem", ( O_RDWR | O_SYNC ) ) ) == -1 ) {
		printf( "ERROR: could not open \"/dev/mem\"...\n" );
		return( 1 );
	}

	lw_bridge_vbase = mmap( NULL, HW_REGS_SPAN, ( PROT_READ | PROT_WRITE ),
	MAP_SHARED, fd, HW_REGS_BASE );

	if( lw_bridge_vbase == MAP_FAILED ) {
		printf( "ERROR: mmap() failed...\n" );
		close( fd );
		return(1);
	}

	// FIFO write addr 
	h2p_virtual_base = mmap( NULL, FIFO_SPAN, ( PROT_READ | PROT_WRITE ), MAP_SHARED, fd, FIFO_BASE); 	
	
	if( h2p_virtual_base == MAP_FAILED ) {
		printf( "ERROR: mmap2() failed...\n" );
		close( fd );
		return(1);
	}
    // Get the address that maps to the FIFO read/write ports

	lw_pio_ptr =(unsigned int *)(lw_bridge_vbase + FPGA_PIO_WRITE); 					// PP output from HPS to FPGA
	FIFO_read_status_ptr =(unsigned int *)(lw_bridge_vbase + FIFO_READ_REG_OFFSET); 	// FIFO status ptr
	FIFO_read_ptr = (unsigned int *)(h2p_virtual_base + FIFO_READ_PTR_OFFSET);  		// FIFO read ptr

	// reset the state machine on FPGA
	*(lw_pio_ptr) = 0x0;

	// setup output file
	FILE *output;

    /* open the file */
    output = fopen("./output.txt", "w");
    if(output == NULL) {
		printf("failed to open output file");
	}

	// flush fifo
	printf("flushing FIFO, fill level: %d\n\r", READ_FIFO_FILL_LEVEL) ;
	while(READ_FIFO_FILL_LEVEL > 0) {			
		printf("flushed: %x, fill: %d\n\r", FIFO_READ, READ_FIFO_FILL_LEVEL) ;
	}

	int img[CAMERA_HEIGHT*CAMERA_WIDTH];
	int i;

	printf("starting transmission\n\r") ;
	// start receiving image
	*(lw_pio_ptr) = 0x1;

	for (i=0; i < CAMERA_HEIGHT*CAMERA_WIDTH; i++) {
		while (READ_FIFO_EMPTY) {}
		img[i] = FIFO_READ;
	}
	
	// stop receiving
	*(lw_pio_ptr) = 0x0;
	printf("finished transmission\n\r") ;

	for (i=0; i < CAMERA_HEIGHT*CAMERA_WIDTH; i++) {
		int c = img[i];
		int extra = (c & EXTRA_MASK) >> 24;
		int r = (c & RED_MASK) >> 16;
		int g = (c & GREEN_MASK) >> 8;
		int b = c & BLUE_MASK;
		fprintf(output, "%d, %d, %d, %d \n", r, g, b, extra);
	}

    /* close the file */
	fclose(output);

	return 0;
}