	component wifi1 is
		port (
			clk_clk                               : in    std_logic                     := 'X';             -- clk
			reset_reset_n                         : in    std_logic                     := 'X';             -- reset_n
			wifi_uart_0_external_connection_rxd   : in    std_logic                     := 'X';             -- rxd
			wifi_uart_0_external_connection_txd   : out   std_logic;                                        -- txd
			wifi_uart_0_external_connection_cts_n : in    std_logic                     := 'X';             -- cts_n
			wifi_uart_0_external_connection_rts_n : out   std_logic;                                        -- rts_n
			memory_mem_a                          : out   std_logic_vector(12 downto 0);                    -- mem_a
			memory_mem_ba                         : out   std_logic_vector(2 downto 0);                     -- mem_ba
			memory_mem_ck                         : out   std_logic;                                        -- mem_ck
			memory_mem_ck_n                       : out   std_logic;                                        -- mem_ck_n
			memory_mem_cke                        : out   std_logic;                                        -- mem_cke
			memory_mem_cs_n                       : out   std_logic;                                        -- mem_cs_n
			memory_mem_ras_n                      : out   std_logic;                                        -- mem_ras_n
			memory_mem_cas_n                      : out   std_logic;                                        -- mem_cas_n
			memory_mem_we_n                       : out   std_logic;                                        -- mem_we_n
			memory_mem_reset_n                    : out   std_logic;                                        -- mem_reset_n
			memory_mem_dq                         : inout std_logic_vector(7 downto 0)  := (others => 'X'); -- mem_dq
			memory_mem_dqs                        : inout std_logic                     := 'X';             -- mem_dqs
			memory_mem_dqs_n                      : inout std_logic                     := 'X';             -- mem_dqs_n
			memory_mem_odt                        : out   std_logic;                                        -- mem_odt
			memory_mem_dm                         : out   std_logic;                                        -- mem_dm
			memory_oct_rzqin                      : in    std_logic                     := 'X';             -- oct_rzqin
			hps_io_hps_io_uart0_inst_RX           : in    std_logic                     := 'X';             -- hps_io_uart0_inst_RX
			hps_io_hps_io_uart0_inst_TX           : out   std_logic;                                        -- hps_io_uart0_inst_TX
			hps_io_hps_io_uart0_inst_CTS          : in    std_logic                     := 'X';             -- hps_io_uart0_inst_CTS
			hps_io_hps_io_uart0_inst_RTS          : out   std_logic;                                        -- hps_io_uart0_inst_RTS
			hps_0_h2f_mpu_events_eventi           : in    std_logic                     := 'X';             -- eventi
			hps_0_h2f_mpu_events_evento           : out   std_logic;                                        -- evento
			hps_0_h2f_mpu_events_standbywfe       : out   std_logic_vector(1 downto 0);                     -- standbywfe
			hps_0_h2f_mpu_events_standbywfi       : out   std_logic_vector(1 downto 0)                      -- standbywfi
		);
	end component wifi1;

	u0 : component wifi1
		port map (
			clk_clk                               => CONNECTED_TO_clk_clk,                               --                             clk.clk
			reset_reset_n                         => CONNECTED_TO_reset_reset_n,                         --                           reset.reset_n
			wifi_uart_0_external_connection_rxd   => CONNECTED_TO_wifi_uart_0_external_connection_rxd,   -- wifi_uart_0_external_connection.rxd
			wifi_uart_0_external_connection_txd   => CONNECTED_TO_wifi_uart_0_external_connection_txd,   --                                .txd
			wifi_uart_0_external_connection_cts_n => CONNECTED_TO_wifi_uart_0_external_connection_cts_n, --                                .cts_n
			wifi_uart_0_external_connection_rts_n => CONNECTED_TO_wifi_uart_0_external_connection_rts_n, --                                .rts_n
			memory_mem_a                          => CONNECTED_TO_memory_mem_a,                          --                          memory.mem_a
			memory_mem_ba                         => CONNECTED_TO_memory_mem_ba,                         --                                .mem_ba
			memory_mem_ck                         => CONNECTED_TO_memory_mem_ck,                         --                                .mem_ck
			memory_mem_ck_n                       => CONNECTED_TO_memory_mem_ck_n,                       --                                .mem_ck_n
			memory_mem_cke                        => CONNECTED_TO_memory_mem_cke,                        --                                .mem_cke
			memory_mem_cs_n                       => CONNECTED_TO_memory_mem_cs_n,                       --                                .mem_cs_n
			memory_mem_ras_n                      => CONNECTED_TO_memory_mem_ras_n,                      --                                .mem_ras_n
			memory_mem_cas_n                      => CONNECTED_TO_memory_mem_cas_n,                      --                                .mem_cas_n
			memory_mem_we_n                       => CONNECTED_TO_memory_mem_we_n,                       --                                .mem_we_n
			memory_mem_reset_n                    => CONNECTED_TO_memory_mem_reset_n,                    --                                .mem_reset_n
			memory_mem_dq                         => CONNECTED_TO_memory_mem_dq,                         --                                .mem_dq
			memory_mem_dqs                        => CONNECTED_TO_memory_mem_dqs,                        --                                .mem_dqs
			memory_mem_dqs_n                      => CONNECTED_TO_memory_mem_dqs_n,                      --                                .mem_dqs_n
			memory_mem_odt                        => CONNECTED_TO_memory_mem_odt,                        --                                .mem_odt
			memory_mem_dm                         => CONNECTED_TO_memory_mem_dm,                         --                                .mem_dm
			memory_oct_rzqin                      => CONNECTED_TO_memory_oct_rzqin,                      --                                .oct_rzqin
			hps_io_hps_io_uart0_inst_RX           => CONNECTED_TO_hps_io_hps_io_uart0_inst_RX,           --                          hps_io.hps_io_uart0_inst_RX
			hps_io_hps_io_uart0_inst_TX           => CONNECTED_TO_hps_io_hps_io_uart0_inst_TX,           --                                .hps_io_uart0_inst_TX
			hps_io_hps_io_uart0_inst_CTS          => CONNECTED_TO_hps_io_hps_io_uart0_inst_CTS,          --                                .hps_io_uart0_inst_CTS
			hps_io_hps_io_uart0_inst_RTS          => CONNECTED_TO_hps_io_hps_io_uart0_inst_RTS,          --                                .hps_io_uart0_inst_RTS
			hps_0_h2f_mpu_events_eventi           => CONNECTED_TO_hps_0_h2f_mpu_events_eventi,           --            hps_0_h2f_mpu_events.eventi
			hps_0_h2f_mpu_events_evento           => CONNECTED_TO_hps_0_h2f_mpu_events_evento,           --                                .evento
			hps_0_h2f_mpu_events_standbywfe       => CONNECTED_TO_hps_0_h2f_mpu_events_standbywfe,       --                                .standbywfe
			hps_0_h2f_mpu_events_standbywfi       => CONNECTED_TO_hps_0_h2f_mpu_events_standbywfi        --                                .standbywfi
		);

