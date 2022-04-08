module Camera (
		//////////// CAMERA //////////
		inout 		          		CAMERA_I2C_SCL,
		inout 		          		CAMERA_I2C_SDA,
		output		          		CAMERA_PWDN_n,
		output		          		MIPI_CS_n,
		inout 		          		MIPI_I2C_SCL,
		inout 		          		MIPI_I2C_SDA,
		output		          		MIPI_MCLK,
		input 		          		MIPI_PIXEL_CLK,
		input 		     [9:0]		MIPI_PIXEL_D,
		input 		          		MIPI_PIXEL_HS,
		input 		          		MIPI_PIXEL_VS,
		output		          		MIPI_REFCLK,
		output		          		MIPI_RESET_n,
		
		//////////// CLOCK //////////
		input 						CLOCK_50,
		input 		          		CLOCK2_50,
		input 		          		CLOCK3_50,
		// output unsigned [9:0]	 	LEDR,
		input unsigned [3:0] 		KEY,
		input unsigned [9:0] 		SW,

		output [11:0]	 			pixel_out,
		output 						pixel_valid,
		input 						waitreq,
		input 						save_frame

		//////////// SDRAM //////////
		// output unsigned [12:0] DRAM_ADDR,
		// output unsigned [1:0] DRAM_BA,
		// output DRAM_CAS_N,
		// output DRAM_CKE,
		// output DRAM_CLK,
		// output DRAM_CS_N,
		// inout unsigned [15:0] DRAM_DQ,
		// output DRAM_RAS_N,
		// output DRAM_WE_N,
		// output Temp_SDRAM_DQM
	);
	
	//=============================================================================
	// REG/WIRE declarations
	//=============================================================================
	wire        READ_Request ;

	wire [7:0] 	RED   ; 
	wire [7:0] 	GREEN  ; 
	wire [7:0] 	BLUE 		 ; 

	wire        CAMERA_MIPI_RELAESE ;
	wire        MIPI_BRIDGE_RELEASE ;  

	wire 		MIPI_PIXEL_CLK_;
	
    reg [18:0] 	pixel_count;
    reg [5:0] 	frame_count;
	reg 		frames;

	wire 		RESET_N;
	wire 		RESET_KEY;
	wire		DLY_RST_0;
	wire		DLY_RST_1;
	wire		DLY_RST_2;
	
	//=======================================================
	// Structural coding
	//=======================================================

	assign READ_Request = 1'b1;
	assign MIPI_PIXEL_CLK_ = MIPI_PIXEL_CLK;
	
	//------ MIPI BRIGE & CAMERA RESET  --
	assign RESET_KEY 	  = KEY[0];
	assign MIPI_RESET_n   = RESET_N;
	assign CAMERA_PWDN_n  = 1; 
	assign MIPI_CS_n      = 0; 
	 
	//----- RESET RELAY  --		
	RESET_DELAY u2	(	
		.iRST  ( RESET_KEY ),
		.iCLK  ( CLOCK2_50 ),	
		.oRST_0( DLY_RST_0 ),
		.oRST_1( DLY_RST_1 ),
		.oRST_2( DLY_RST_2 ),				
		.oREADY( RESET_N)
	);

	//------ MIPI BRIGE & CAMERA SETTING  --  
	MIPI_BRIDGE_CAMERA_Config    cfin(
		.RESET_N           ( RESET_N ), 
		.CLK_50            ( CLOCK2_50 ), 
		.MIPI_I2C_SCL      ( MIPI_I2C_SCL ), 
		.MIPI_I2C_SDA      ( MIPI_I2C_SDA ), 
		.MIPI_I2C_RELEASE  ( MIPI_BRIDGE_RELEASE ),  
		.CAMERA_I2C_SCL    ( CAMERA_I2C_SCL ),
		.CAMERA_I2C_SDA    ( CAMERA_I2C_SDA ),
		.CAMERA_I2C_RELAESE( CAMERA_MIPI_RELAESE )
	);
		 
	//------MIPI / VGA REF CLOCK  --
	pll_test ref(
		.refclk   ( CLOCK3_50  ),   
		.rst      ( 1'b0 ),     
		.outclk_0 ( MIPI_REFCLK )//20m
	);
	
	// assign LEDR = {D8M_CK_HZ, D8M_CK_HZ2, D8M_CK_HZ3, 5'h0, CAMERA_MIPI_RELAESE, MIPI_BRIDGE_RELEASE};

    wire [23:0] RGB_data;
    // wire [25:0] SDRAM_in, SDRAM_out;
    assign RGB_data = {RED, GREEN, BLUE};

    parameter VIDEO_W	= 640;
    parameter VIDEO_H	= 480;

	wire [9:0] LUT_MIPI_PIXEL_D;
	wire LUT_MIPI_PIXEL_VS, LUT_MIPI_PIXEL_HS;
	
	assign LUT_MIPI_PIXEL_D = MIPI_PIXEL_D[9:0];
	assign LUT_MIPI_PIXEL_VS = MIPI_PIXEL_VS;
	assign LUT_MIPI_PIXEL_HS = MIPI_PIXEL_HS;

	//--LED DISPLAY--
	wire D8M_CK_HZ, D8M_CK_HZ2, D8M_CK_HZ3;
	CLOCKMEM  ck1 ( .CLK(MIPI_REFCLK   )   ,.CLK_FREQ  (20000000  ) , . CK_1HZ (D8M_CK_HZ  )  );//20MHZ
	CLOCKMEM  ck2 ( .CLK(MIPI_PIXEL_CLK_)   ,.CLK_FREQ  (25000000  ) , . CK_1HZ (D8M_CK_HZ2  )  );//25MHZ
	
	//------ FIFO CONTROL --
    wire fifo_w_full, fifo_r_empty;
	wire [11:0] fifo_in;
	assign fifo_in = {LUT_MIPI_PIXEL_VS, LUT_MIPI_PIXEL_HS, LUT_MIPI_PIXEL_D};
	assign pixel_valid = ~fifo_r_empty;

	//------ FIFO --
    pixel_fifo2 pixel_fifo_inst(
        // write
        .wrclk(MIPI_PIXEL_CLK),
        .wrreq(save_frame),
        .data(fifo_in),
        .wrfull(fifo_w_full),
        
        // read
        .rdclk(CLOCK_50),
        .rdreq(~waitreq & ~fifo_r_empty),
        .q(pixel_out),
        .rdempty(fifo_r_empty)
    );	


endmodule