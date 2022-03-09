//////////////////////////////////////////////////////////////////////////////////
// Top level module
//////////////////////////////////////////////////////////////////////////////////

module spycat_computer (

    //   ///////// AUD /////////
    //   input              AUD_ADCDAT,
    //   inout              AUD_ADCLRCK,
    //   inout              AUD_BCLK,
    //   output             AUD_DACDAT,
    //   inout              AUD_DACLRCK,
    //   output             AUD_XCK,

    ///////// CLOCK2 /////////
    input              CLOCK2_50,

    ///////// CLOCK3 /////////
    input              CLOCK3_50,

    ///////// CLOCK4 /////////
    input              CLOCK4_50,

    ///////// CLOCK /////////
    input              CLOCK_50,

    ///////// DRAM /////////
    output      [12:0] DRAM_ADDR,
    output      [1:0]  DRAM_BA,
    output             DRAM_CAS_N,
    output             DRAM_CKE,
    output             DRAM_CLK,
    output             DRAM_CS_N,
    inout       [15:0] DRAM_DQ,
    output             DRAM_LDQM,
    output             DRAM_RAS_N,
    output             DRAM_UDQM,
    output             DRAM_WE_N,

    //   ///////// FAN /////////
    //   output             FAN_CTRL,

    ///////// FPGA /////////
    output             FPGA_I2C_SCLK,
    inout              FPGA_I2C_SDAT,

    ///////// GPIO /////////
    inout     [35:0]         GPIO_0,
    inout     [35:0]         GPIO_1,
 

    //   ///////// HEX0 /////////
    //   output      [6:0]  HEX0,
 
    //   ///////// HEX1 /////////
    //   output      [6:0]  HEX1,

    //   ///////// HEX2 /////////
    //   output      [6:0]  HEX2,

    //   ///////// HEX3 /////////
    //   output      [6:0]  HEX3,

    //   ///////// HEX4 /////////
    //   output      [6:0]  HEX4,

    //   ///////// HEX5 /////////
    //   output      [6:0]  HEX5,

    ///////// HPS /////////
    inout              HPS_CONV_USB_N,
    output      [14:0] HPS_DDR3_ADDR,
    output      [2:0]  HPS_DDR3_BA,
    output             HPS_DDR3_CAS_N,
    output             HPS_DDR3_CKE,
    output             HPS_DDR3_CK_N,
    output             HPS_DDR3_CK_P,
    output             HPS_DDR3_CS_N,
    output      [3:0]  HPS_DDR3_DM,
    inout       [31:0] HPS_DDR3_DQ,
    inout       [3:0]  HPS_DDR3_DQS_N,
    inout       [3:0]  HPS_DDR3_DQS_P,
    output             HPS_DDR3_ODT,
    output             HPS_DDR3_RAS_N,
    output             HPS_DDR3_RESET_N,
    input              HPS_DDR3_RZQ,
    output             HPS_DDR3_WE_N,
    output             HPS_ENET_GTX_CLK,
    inout              HPS_ENET_INT_N,
    output             HPS_ENET_MDC,
    inout              HPS_ENET_MDIO,
    input              HPS_ENET_RX_CLK,
    input       [3:0]  HPS_ENET_RX_DATA,
    input              HPS_ENET_RX_DV,
    output      [3:0]  HPS_ENET_TX_DATA,
    output             HPS_ENET_TX_EN,
    inout       [3:0]  HPS_FLASH_DATA,
    output             HPS_FLASH_DCLK,
    output             HPS_FLASH_NCSO,
    inout              HPS_GSENSOR_INT,
    inout              HPS_I2C1_SCLK,
    inout              HPS_I2C1_SDAT,
    inout              HPS_I2C2_SCLK,
    inout              HPS_I2C2_SDAT,
    inout              HPS_I2C_CONTROL,
    inout              HPS_KEY,
    inout              HPS_LED,
    inout              HPS_LTC_GPIO,
    output             HPS_SD_CLK,
    inout              HPS_SD_CMD,
    inout       [3:0]  HPS_SD_DATA,
    output             HPS_SPIM_CLK,
    input              HPS_SPIM_MISO,
    output             HPS_SPIM_MOSI,
    inout              HPS_SPIM_SS,
    input              HPS_UART_RX,
    output             HPS_UART_TX,
    input              HPS_USB_CLKOUT,
    inout       [7:0]  HPS_USB_DATA,
    input              HPS_USB_DIR,
    input              HPS_USB_NXT,
    output             HPS_USB_STP,

    //   ///////// IRDA /////////
    //   input              IRDA_RXD,
    //   output             IRDA_TXD,

    //   ///////// KEY /////////
    //   input       [3:0]  KEY,

    //   ///////// LEDR /////////
    //   output      [9:0]  LEDR,

    //   ///////// PS2 /////////
    //   inout              PS2_CLK,
    //   inout              PS2_CLK2,
    //   inout              PS2_DAT,
    //   inout              PS2_DAT2,

    //   ///////// SW /////////
    //   input       [9:0]  SW,

    //   ///////// TD /////////
    //   input              TD_CLK27,
    //   input      [7:0]  TD_DATA,
    //   input             TD_HS,
    //   output             TD_RESET_N,
    //   input             TD_VS,

    //   ///////// VGA /////////
    //   output      [7:0]  VGA_B,
    //   output             VGA_BLANK_N,
    //   output             VGA_CLK,
    //   output      [7:0]  VGA_G,
    //   output             VGA_HS,
    //   output      [7:0]  VGA_R,
    //   output             VGA_SYNC_N,
    //   output             VGA_VS
);

    wire RESET_L_WIRE;

	reg IO_ACK;	
	wire IO_IRQ_WIRE;
	wire unsigned [15:0] IO_Address_WIRE;
	wire IO_Bus_Enable_WIRE;
	wire unsigned [1:0] IO_Byte_Enable_WIRE;
	wire IO_RW_WIRE;
	wire unsigned [15:0] IO_Write_Data_WIRE;
	wire unsigned [15:0] IO_Read_Data_WIRE;

    ///////////////////////////////////////////////////////////////////////////////////////
    // u0 is an instanace of the QSYS generated computer
    // map its IO ports as described below
    ///////////////////////////////////////////////////////////////////////////////////////

    spycat_computer u0(
		.hps_io_hps_io_uart0_inst_RX,   (HPS_UART_RX),         //               hps_io.hps_io_uart0_inst_RX
		.hps_io_hps_io_uart0_inst_TX,   (HPS_UART_TX),         //                     .hps_io_uart0_inst_TX

        // IO bridge     
		.io_acknowledge  			    (IO_ACK),	
		.io_irq          			    (IO_IRQ_WIRE),
		.io_address      			    (IO_Address_WIRE),
		.io_bus_enable  			    (IO_Bus_Enable_WIRE),
		.io_byte_enable  			    (IO_Byte_Enable_WIRE),
		.io_rw           			    (IO_RW_WIRE),  
		.io_write_data   			    (IO_Write_Data_WIRE),                    
		.io_read_data    			    (IO_Read_Data_WIRE),

        // SDRAM
		.memory_mem_a,                  (HPS_DDR3_ADDR),         //               memory.mem_a
		.memory_mem_ba,                 (HPS_DDR3_BA),         //                     .mem_ba
		.memory_mem_ck,                 (HPS_DDR3_CK_P),         //                     .mem_ck
		.memory_mem_ck_n,               (HPS_DDR3_CK_N),         //                     .mem_ck_n
		.memory_mem_cke,                (HPS_DDR3_CKE),         //                     .mem_cke
		.memory_mem_cs_n,               (HPS_DDR3_CS_N),         //                     .mem_cs_n
		.memory_mem_ras_n,              (HPS_DDR3_RAS_N),         //                     .mem_ras_n
		.memory_mem_cas_n,              (HPS_DDR3_CAS_N),         //                     .mem_cas_n
		.memory_mem_we_n,               (HPS_DDR3_WE_N),         //                     .mem_we_n
		.memory_mem_reset_n,            (HPS_DDR3_RESET_N),         //                     .mem_reset_n
		.memory_mem_dq,                 (HPS_DDR3_DQ),         //                     .mem_dq
		.memory_mem_dqs,                (HPS_DDR3_DQS_P),         //                     .mem_dqs
		.memory_mem_dqs_n,              (HPS_DDR3_DQS_N),         //                     .mem_dqs_n
		.memory_mem_odt,                (HPS_DDR3_ODT),         //                     .mem_odt
		.memory_mem_dm,                 (HPS_DDR3_DM),         //                     .mem_dm
		.memory_oct_rzqin,              (HPS_DDR3_RZQ),         //                     .oct_rzqin
		.sdram_clk_clk,                 (DRAM_CLK),         //            sdram_clk.clk
		.system_pll_ref_clk_clk,        (CLOCK_50),         //   system_pll_ref_clk.clk
		.system_pll_ref_reset_reset     (0)         // system_pll_ref_reset.reset
	);

    OnChipSerialIO     SerialIOPorts (
            
        // Bridge Signals connecting to this component
        
        .Reset_L 						(RESET_L_WIRE),
        .Clock_50Mhz 					(CLOCK_50),
        .Address 						(IO_Address_WIRE),
        .DataIn 						(IO_Write_Data_WIRE[7:0]),
        .DataOut 						(IO_Read_Data_WIRE[7:0]),
        .IOSelect_H 					(IO_Bus_Enable_WIRE),
        .ByteSelect_L 				    (IO_LowerByte_Select_L_WIRE),
        .WE_L 							(IO_RW_WIRE),
        .IRQ_H 							(IO_IRQ_WIRE),
        
        // Real World Signals brought out to Header connections

        .RS232_RxData					(GPIO_1[29]),
        .RS232_TxData					(GPIO_1[27]),

        .TouchScreen_RxData 		    (GPIO_0[11]),
        .TouchScreen_TxData 		    (GPIO_0[10]),

        .WiFi_TXD					    (GPIO_1[35]),
        .WiFi_RXD					    (GPIO_1[33])
    );

    assign RESET_L_WIRE = 1'b1;

    // process to generate an acknowledge for the IO Bridge 1 clock cycle after bridge IO BUS ENABLE and then remove it 
    always@(posedge CLOCK_50)
    begin
        IO_ACK <= IO_Bus_Enable_WIRE;
    end
endmodule