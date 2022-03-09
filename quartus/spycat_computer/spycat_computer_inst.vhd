	component spycat_computer is
		port (
			system_pll_ref_clk_clk      : in    std_logic                     := 'X';             -- clk
			system_pll_ref_reset_reset  : in    std_logic                     := 'X';             -- reset
			sdram_clk_clk               : out   std_logic;                                        -- clk
			memory_mem_a                : out   std_logic_vector(12 downto 0);                    -- mem_a
			memory_mem_ba               : out   std_logic_vector(2 downto 0);                     -- mem_ba
			memory_mem_ck               : out   std_logic;                                        -- mem_ck
			memory_mem_ck_n             : out   std_logic;                                        -- mem_ck_n
			memory_mem_cke              : out   std_logic;                                        -- mem_cke
			memory_mem_cs_n             : out   std_logic;                                        -- mem_cs_n
			memory_mem_ras_n            : out   std_logic;                                        -- mem_ras_n
			memory_mem_cas_n            : out   std_logic;                                        -- mem_cas_n
			memory_mem_we_n             : out   std_logic;                                        -- mem_we_n
			memory_mem_reset_n          : out   std_logic;                                        -- mem_reset_n
			memory_mem_dq               : inout std_logic_vector(7 downto 0)  := (others => 'X'); -- mem_dq
			memory_mem_dqs              : inout std_logic                     := 'X';             -- mem_dqs
			memory_mem_dqs_n            : inout std_logic                     := 'X';             -- mem_dqs_n
			memory_mem_odt              : out   std_logic;                                        -- mem_odt
			memory_mem_dm               : out   std_logic;                                        -- mem_dm
			memory_oct_rzqin            : in    std_logic                     := 'X';             -- oct_rzqin
			hps_io_hps_io_uart0_inst_RX : in    std_logic                     := 'X';             -- hps_io_uart0_inst_RX
			hps_io_hps_io_uart0_inst_TX : out   std_logic;                                        -- hps_io_uart0_inst_TX
			io_acknowledge              : in    std_logic                     := 'X';             -- acknowledge
			io_irq                      : in    std_logic                     := 'X';             -- irq
			io_address                  : out   std_logic_vector(15 downto 0);                    -- address
			io_bus_enable               : out   std_logic;                                        -- bus_enable
			io_byte_enable              : out   std_logic_vector(1 downto 0);                     -- byte_enable
			io_rw                       : out   std_logic;                                        -- rw
			io_write_data               : out   std_logic_vector(15 downto 0);                    -- write_data
			io_read_data                : in    std_logic_vector(15 downto 0) := (others => 'X')  -- read_data
		);
	end component spycat_computer;

	u0 : component spycat_computer
		port map (
			system_pll_ref_clk_clk      => CONNECTED_TO_system_pll_ref_clk_clk,      --   system_pll_ref_clk.clk
			system_pll_ref_reset_reset  => CONNECTED_TO_system_pll_ref_reset_reset,  -- system_pll_ref_reset.reset
			sdram_clk_clk               => CONNECTED_TO_sdram_clk_clk,               --            sdram_clk.clk
			memory_mem_a                => CONNECTED_TO_memory_mem_a,                --               memory.mem_a
			memory_mem_ba               => CONNECTED_TO_memory_mem_ba,               --                     .mem_ba
			memory_mem_ck               => CONNECTED_TO_memory_mem_ck,               --                     .mem_ck
			memory_mem_ck_n             => CONNECTED_TO_memory_mem_ck_n,             --                     .mem_ck_n
			memory_mem_cke              => CONNECTED_TO_memory_mem_cke,              --                     .mem_cke
			memory_mem_cs_n             => CONNECTED_TO_memory_mem_cs_n,             --                     .mem_cs_n
			memory_mem_ras_n            => CONNECTED_TO_memory_mem_ras_n,            --                     .mem_ras_n
			memory_mem_cas_n            => CONNECTED_TO_memory_mem_cas_n,            --                     .mem_cas_n
			memory_mem_we_n             => CONNECTED_TO_memory_mem_we_n,             --                     .mem_we_n
			memory_mem_reset_n          => CONNECTED_TO_memory_mem_reset_n,          --                     .mem_reset_n
			memory_mem_dq               => CONNECTED_TO_memory_mem_dq,               --                     .mem_dq
			memory_mem_dqs              => CONNECTED_TO_memory_mem_dqs,              --                     .mem_dqs
			memory_mem_dqs_n            => CONNECTED_TO_memory_mem_dqs_n,            --                     .mem_dqs_n
			memory_mem_odt              => CONNECTED_TO_memory_mem_odt,              --                     .mem_odt
			memory_mem_dm               => CONNECTED_TO_memory_mem_dm,               --                     .mem_dm
			memory_oct_rzqin            => CONNECTED_TO_memory_oct_rzqin,            --                     .oct_rzqin
			hps_io_hps_io_uart0_inst_RX => CONNECTED_TO_hps_io_hps_io_uart0_inst_RX, --               hps_io.hps_io_uart0_inst_RX
			hps_io_hps_io_uart0_inst_TX => CONNECTED_TO_hps_io_hps_io_uart0_inst_TX, --                     .hps_io_uart0_inst_TX
			io_acknowledge              => CONNECTED_TO_io_acknowledge,              --                   io.acknowledge
			io_irq                      => CONNECTED_TO_io_irq,                      --                     .irq
			io_address                  => CONNECTED_TO_io_address,                  --                     .address
			io_bus_enable               => CONNECTED_TO_io_bus_enable,               --                     .bus_enable
			io_byte_enable              => CONNECTED_TO_io_byte_enable,              --                     .byte_enable
			io_rw                       => CONNECTED_TO_io_rw,                       --                     .rw
			io_write_data               => CONNECTED_TO_io_write_data,               --                     .write_data
			io_read_data                => CONNECTED_TO_io_read_data                 --                     .read_data
		);

