// Copyright (C) 2019  Intel Corporation. All rights reserved.
// Your use of Intel Corporation's design tools, logic functions 
// and other software and tools, and any partner logic 
// functions, and any output files from any of the foregoing 
// (including device programming or simulation files), and any 
// associated documentation or information are expressly subject 
// to the terms and conditions of the Intel Program License 
// Subscription Agreement, the Intel Quartus Prime License Agreement,
// the Intel FPGA IP License Agreement, or other applicable license
// agreement, including, without limitation, that your use is for
// the sole purpose of programming logic devices manufactured by
// Intel and sold by Intel or its authorized distributors.  Please
// refer to the applicable agreement for further details, at
// https://fpgasoftware.intel.com/eula.

// PROGRAM		"Quartus Prime"
// VERSION		"Version 19.1.0 Build 670 09/22/2019 Patches 0.09std,0.02std SJ Lite Edition"
// CREATED		"Tue Mar 08 20:36:10 2022"

module OnChipSerialIO(
	Reset_L,
	Clock_50Mhz,
	RS232_RxData,
	WE_L,
	IOSelect_H,
	ByteSelect_L,
	TouchScreen_RxData,
	WiFi_RXD,
	Address,
	DataIn,
	RS232_TxData,
	TouchScreen_TxData,
	IRQ_H,
	WiFi_TXD,
	DataOut
);


input wire	Reset_L;
input wire	Clock_50Mhz;
input wire	RS232_RxData;
input wire	WE_L;
input wire	IOSelect_H;
input wire	ByteSelect_L;
input wire	TouchScreen_RxData;
input wire	WiFi_RXD;
input wire	[15:0] Address;
input wire	[7:0] DataIn;
output wire	RS232_TxData;
output wire	TouchScreen_TxData;
output wire	IRQ_H;
output wire	WiFi_TXD;
output wire	[7:0] DataOut;

wire	[7:0] DataOut_Wifi;
wire	[7:0] DataOut_TouchScreen;
wire	[7:0] DataOut_RS;

wire	SYNTHESIZED_WIRE_0;
wire	SYNTHESIZED_WIRE_1;
wire	SYNTHESIZED_WIRE_2;
wire	SYNTHESIZED_WIRE_3;
wire	SYNTHESIZED_WIRE_46;
wire	SYNTHESIZED_WIRE_47;
wire	SYNTHESIZED_WIRE_48;
wire	SYNTHESIZED_WIRE_49;
wire	SYNTHESIZED_WIRE_50;
wire	SYNTHESIZED_WIRE_51;
wire	SYNTHESIZED_WIRE_20;
wire	SYNTHESIZED_WIRE_21;
wire	SYNTHESIZED_WIRE_52;
wire	SYNTHESIZED_WIRE_53;
wire	SYNTHESIZED_WIRE_54;
wire	SYNTHESIZED_WIRE_55;
wire	SYNTHESIZED_WIRE_56;
wire	SYNTHESIZED_WIRE_57;

assign	SYNTHESIZED_WIRE_49 = 0;
assign	SYNTHESIZED_WIRE_51 = 0;
assign	SYNTHESIZED_WIRE_53 = 0;
assign	SYNTHESIZED_WIRE_55 = 0;
assign	SYNTHESIZED_WIRE_57 = 0;

assign DataOut = DataOut_Wifi;

SerialIODecoder	IODecoder(
	.IOSelect_H(IOSelect_H),
	.ByteSelect_L(ByteSelect_L),
	.Address(Address),
	.RS232_Port_Enable(SYNTHESIZED_WIRE_52),
	.TouchScreen_Port_Enable(SYNTHESIZED_WIRE_47),
	.WiFi_Port_Enable(SYNTHESIZED_WIRE_50)
);


assign	SYNTHESIZED_WIRE_21 = SYNTHESIZED_WIRE_0 | SYNTHESIZED_WIRE_1 | SYNTHESIZED_WIRE_2 | SYNTHESIZED_WIRE_3;



gh_uart_16550_wb_wrapper	TouchScreen_UART(
	.wb_clk_i(Clock_50Mhz),
	.wb_rst_i(SYNTHESIZED_WIRE_46),
	.wb_stb_i(SYNTHESIZED_WIRE_47),
	.wb_cyc_i(SYNTHESIZED_WIRE_47),
	.wb_we_i(SYNTHESIZED_WIRE_48),
	.BR_clk(Clock_50Mhz),
	.sRX(TouchScreen_RxData),
	.CTSn(SYNTHESIZED_WIRE_49),
	.DSRn(SYNTHESIZED_WIRE_49),
	.RIn(SYNTHESIZED_WIRE_49),
	.DCDn(SYNTHESIZED_WIRE_49),
	.wb_adr_i(Address[3:1]),
	.wb_dat_i(DataIn),
	
	.sTX(TouchScreen_TxData),
	
	
	.IRQ(SYNTHESIZED_WIRE_2),
	
	.wb_dat_o(DataOut_TouchScreen)
);



gh_uart_16550_wb_wrapper	Wifi_UART(
	.wb_clk_i(Clock_50Mhz),
	.wb_rst_i(SYNTHESIZED_WIRE_46),
	.wb_stb_i(SYNTHESIZED_WIRE_50),
	.wb_cyc_i(SYNTHESIZED_WIRE_50),
	.wb_we_i(SYNTHESIZED_WIRE_48),
	.BR_clk(Clock_50Mhz),
	.sRX(WiFi_RXD),
	.CTSn(SYNTHESIZED_WIRE_51),
	.DSRn(SYNTHESIZED_WIRE_51),
	.RIn(SYNTHESIZED_WIRE_51),
	.DCDn(SYNTHESIZED_WIRE_51),
	.wb_adr_i(Address[3:1]),
	.wb_dat_i(DataIn),
	
	.sTX(WiFi_TXD),
	
	
	.IRQ(SYNTHESIZED_WIRE_20),
	
	.wb_dat_o(DataOut_Wifi)
);


assign	IRQ_H = SYNTHESIZED_WIRE_20 | SYNTHESIZED_WIRE_21;


gh_uart_16550_wb_wrapper	RS232_UART(
	.wb_clk_i(Clock_50Mhz),
	.wb_rst_i(SYNTHESIZED_WIRE_46),
	.wb_stb_i(SYNTHESIZED_WIRE_52),
	.wb_cyc_i(SYNTHESIZED_WIRE_52),
	.wb_we_i(SYNTHESIZED_WIRE_48),
	.BR_clk(Clock_50Mhz),
	.sRX(RS232_RxData),
	.CTSn(SYNTHESIZED_WIRE_53),
	.DSRn(SYNTHESIZED_WIRE_53),
	.RIn(SYNTHESIZED_WIRE_53),
	.DCDn(SYNTHESIZED_WIRE_53),
	.wb_adr_i(Address[3:1]),
	.wb_dat_i(DataIn),
	
	.sTX(RS232_TxData),
	
	
	.IRQ(SYNTHESIZED_WIRE_0),
	
	.wb_dat_o(DataOut_RS)
);

assign	SYNTHESIZED_WIRE_46 =  ~Reset_L;

assign	SYNTHESIZED_WIRE_48 =  ~WE_L;


endmodule
