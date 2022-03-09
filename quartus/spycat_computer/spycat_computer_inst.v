	spycat_computer u0 (
		.system_pll_ref_clk_clk      (<connected-to-system_pll_ref_clk_clk>),      //   system_pll_ref_clk.clk
		.system_pll_ref_reset_reset  (<connected-to-system_pll_ref_reset_reset>),  // system_pll_ref_reset.reset
		.sdram_clk_clk               (<connected-to-sdram_clk_clk>),               //            sdram_clk.clk
		.memory_mem_a                (<connected-to-memory_mem_a>),                //               memory.mem_a
		.memory_mem_ba               (<connected-to-memory_mem_ba>),               //                     .mem_ba
		.memory_mem_ck               (<connected-to-memory_mem_ck>),               //                     .mem_ck
		.memory_mem_ck_n             (<connected-to-memory_mem_ck_n>),             //                     .mem_ck_n
		.memory_mem_cke              (<connected-to-memory_mem_cke>),              //                     .mem_cke
		.memory_mem_cs_n             (<connected-to-memory_mem_cs_n>),             //                     .mem_cs_n
		.memory_mem_ras_n            (<connected-to-memory_mem_ras_n>),            //                     .mem_ras_n
		.memory_mem_cas_n            (<connected-to-memory_mem_cas_n>),            //                     .mem_cas_n
		.memory_mem_we_n             (<connected-to-memory_mem_we_n>),             //                     .mem_we_n
		.memory_mem_reset_n          (<connected-to-memory_mem_reset_n>),          //                     .mem_reset_n
		.memory_mem_dq               (<connected-to-memory_mem_dq>),               //                     .mem_dq
		.memory_mem_dqs              (<connected-to-memory_mem_dqs>),              //                     .mem_dqs
		.memory_mem_dqs_n            (<connected-to-memory_mem_dqs_n>),            //                     .mem_dqs_n
		.memory_mem_odt              (<connected-to-memory_mem_odt>),              //                     .mem_odt
		.memory_mem_dm               (<connected-to-memory_mem_dm>),               //                     .mem_dm
		.memory_oct_rzqin            (<connected-to-memory_oct_rzqin>),            //                     .oct_rzqin
		.hps_io_hps_io_uart0_inst_RX (<connected-to-hps_io_hps_io_uart0_inst_RX>), //               hps_io.hps_io_uart0_inst_RX
		.hps_io_hps_io_uart0_inst_TX (<connected-to-hps_io_hps_io_uart0_inst_TX>), //                     .hps_io_uart0_inst_TX
		.io_acknowledge              (<connected-to-io_acknowledge>),              //                   io.acknowledge
		.io_irq                      (<connected-to-io_irq>),                      //                     .irq
		.io_address                  (<connected-to-io_address>),                  //                     .address
		.io_bus_enable               (<connected-to-io_bus_enable>),               //                     .bus_enable
		.io_byte_enable              (<connected-to-io_byte_enable>),              //                     .byte_enable
		.io_rw                       (<connected-to-io_rw>),                       //                     .rw
		.io_write_data               (<connected-to-io_write_data>),               //                     .write_data
		.io_read_data                (<connected-to-io_read_data>)                 //                     .read_data
	);

