
module wifi1 (
	clk_clk,
	reset_reset_n,
	wifi_uart_0_external_connection_rxd,
	wifi_uart_0_external_connection_txd,
	wifi_uart_0_external_connection_cts_n,
	wifi_uart_0_external_connection_rts_n,
	memory_mem_a,
	memory_mem_ba,
	memory_mem_ck,
	memory_mem_ck_n,
	memory_mem_cke,
	memory_mem_cs_n,
	memory_mem_ras_n,
	memory_mem_cas_n,
	memory_mem_we_n,
	memory_mem_reset_n,
	memory_mem_dq,
	memory_mem_dqs,
	memory_mem_dqs_n,
	memory_mem_odt,
	memory_mem_dm,
	memory_oct_rzqin,
	hps_io_hps_io_uart0_inst_RX,
	hps_io_hps_io_uart0_inst_TX,
	hps_io_hps_io_uart0_inst_CTS,
	hps_io_hps_io_uart0_inst_RTS,
	hps_0_h2f_mpu_events_eventi,
	hps_0_h2f_mpu_events_evento,
	hps_0_h2f_mpu_events_standbywfe,
	hps_0_h2f_mpu_events_standbywfi);	

	input		clk_clk;
	input		reset_reset_n;
	input		wifi_uart_0_external_connection_rxd;
	output		wifi_uart_0_external_connection_txd;
	input		wifi_uart_0_external_connection_cts_n;
	output		wifi_uart_0_external_connection_rts_n;
	output	[12:0]	memory_mem_a;
	output	[2:0]	memory_mem_ba;
	output		memory_mem_ck;
	output		memory_mem_ck_n;
	output		memory_mem_cke;
	output		memory_mem_cs_n;
	output		memory_mem_ras_n;
	output		memory_mem_cas_n;
	output		memory_mem_we_n;
	output		memory_mem_reset_n;
	inout	[7:0]	memory_mem_dq;
	inout		memory_mem_dqs;
	inout		memory_mem_dqs_n;
	output		memory_mem_odt;
	output		memory_mem_dm;
	input		memory_oct_rzqin;
	input		hps_io_hps_io_uart0_inst_RX;
	output		hps_io_hps_io_uart0_inst_TX;
	input		hps_io_hps_io_uart0_inst_CTS;
	output		hps_io_hps_io_uart0_inst_RTS;
	input		hps_0_h2f_mpu_events_eventi;
	output		hps_0_h2f_mpu_events_evento;
	output	[1:0]	hps_0_h2f_mpu_events_standbywfe;
	output	[1:0]	hps_0_h2f_mpu_events_standbywfi;
endmodule
