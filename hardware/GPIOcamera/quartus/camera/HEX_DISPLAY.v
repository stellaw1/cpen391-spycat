module HEX_DISPLAY ( 
input [23:0]        wraddr,
output [6:0]		HEX0,
output [6:0]		HEX1,
output [6:0]		HEX2,
output [6:0]		HEX3,
output [6:0]		HEX4,
output [6:0]		HEX5
) ;

wire [3:0] addr0;
wire [3:0] addr1;
wire [3:0] addr2;
wire [3:0] addr3;
wire [3:0] addr4;
wire [3:0] addr5;

assign addr0 = wraddr[3:0];
assign addr1 = wraddr[7:4];
assign addr2 = wraddr[11:8];
assign addr3 = wraddr[15:12];
assign addr4 = wraddr[19:16];
assign addr5 = wraddr[23:20];

assign HEX0 = (addr0 == 4'd0)?7'h40: //0
            (addr0 == 4'd1)?7'h79: //1
            (addr0 == 4'd2)?7'h24: //2
            (addr0 == 4'd3)?7'h30: //3
			(addr0 == 4'd4)?7'h19: //4        
			(addr0 == 4'd5)?7'h12: //5
            (addr0 == 4'd6)?7'h02: //6
            (addr0 == 4'd7)?7'h78: //7
            (addr0 == 4'd8)?7'h00: //8
            (addr0 == 4'd9)?7'h10: //9
            (addr0 == 4'd10)?7'h08: //10
            (addr0 == 4'd11)?7'h03: //11
            (addr0 == 4'd12)?7'h43: //12
            (addr0 == 4'd13)?7'h21: //13
            (addr0 == 4'd14)?7'h06: //14
            7'h0e; //15
assign HEX1 = (addr1 == 4'd0)?7'h40: //0
            (addr1 == 4'd1)?7'h79: //1
            (addr1 == 4'd2)?7'h24: //2
            (addr1 == 4'd3)?7'h30: //3
			(addr1 == 4'd4)?7'h19: //4        
			(addr1 == 4'd5)?7'h12: //5
            (addr1 == 4'd6)?7'h02: //6
            (addr1 == 4'd7)?7'h78: //7
            (addr1 == 4'd8)?7'h00: //8
            (addr1 == 4'd9)?7'h10: //9
            (addr1 == 4'd10)?7'h08: //10
            (addr1 == 4'd11)?7'h03: //11
            (addr1 == 4'd12)?7'h43: //12
            (addr1 == 4'd13)?7'h21: //13
            (addr1 == 4'd14)?7'h06: //14
            7'h0e; //15
assign HEX2 = (addr2 == 4'd0)?7'h40: //0
            (addr2 == 4'd1)?7'h79: //1
            (addr2 == 4'd2)?7'h24: //2
            (addr2 == 4'd3)?7'h30: //3
			(addr2 == 4'd4)?7'h19: //4        
			(addr2 == 4'd5)?7'h12: //5
            (addr2 == 4'd6)?7'h02: //6
            (addr2 == 4'd7)?7'h78: //7
            (addr2 == 4'd8)?7'h00: //8
            (addr2 == 4'd9)?7'h10: //9
            (addr2 == 4'd10)?7'h08: //10
            (addr2 == 4'd11)?7'h03: //11
            (addr2 == 4'd12)?7'h43: //12
            (addr2 == 4'd13)?7'h21: //13
            (addr2 == 4'd14)?7'h06: //14
            7'h0e; //15
assign HEX3 = (addr3 == 4'd0)?7'h40: //0
            (addr3 == 4'd1)?7'h79: //1
            (addr3 == 4'd2)?7'h24: //2
            (addr3 == 4'd3)?7'h30: //3
			(addr3 == 4'd4)?7'h19: //4        
			(addr3 == 4'd5)?7'h12: //5
            (addr3 == 4'd6)?7'h02: //6
            (addr3 == 4'd7)?7'h78: //7
            (addr3 == 4'd8)?7'h00: //8
            (addr3 == 4'd9)?7'h10: //9
            (addr3 == 4'd10)?7'h08: //10
            (addr3 == 4'd11)?7'h03: //11
            (addr3 == 4'd12)?7'h43: //12
            (addr3 == 4'd13)?7'h21: //13
            (addr3 == 4'd14)?7'h06: //14
            7'h0e; //15
assign HEX4 = (addr4 == 4'd0)?7'h40: //0
            (addr4 == 4'd1)?7'h79: //1
            (addr4 == 4'd2)?7'h24: //2
            (addr4 == 4'd3)?7'h30: //3
			(addr4 == 4'd4)?7'h19: //4        
			(addr4 == 4'd5)?7'h12: //5
            (addr4 == 4'd6)?7'h02: //6
            (addr4 == 4'd7)?7'h78: //7
            (addr4 == 4'd8)?7'h00: //8
            (addr4 == 4'd9)?7'h10: //9
            (addr4 == 4'd10)?7'h08: //10
            (addr4 == 4'd11)?7'h03: //11
            (addr4 == 4'd12)?7'h43: //12
            (addr4 == 4'd13)?7'h21: //13
            (addr4 == 4'd14)?7'h06: //14
            7'h0e; //15
assign HEX5 = (addr5 == 4'd0)?7'h40: //0
            (addr5 == 4'd1)?7'h79: //1
            (addr5 == 4'd2)?7'h24: //2
            (addr5 == 4'd3)?7'h30: //3
			(addr5 == 4'd4)?7'h19: //4        
			(addr5 == 4'd5)?7'h12: //5
            (addr5 == 4'd6)?7'h02: //6
            (addr5 == 4'd7)?7'h78: //7
            (addr5 == 4'd8)?7'h00: //8
            (addr5 == 4'd9)?7'h10: //9
            (addr5 == 4'd10)?7'h08: //10
            (addr5 == 4'd11)?7'h03: //11
            (addr5 == 4'd12)?7'h43: //12
            (addr5 == 4'd13)?7'h21: //13
            (addr5 == 4'd14)?7'h06: //14
            7'h0e; //15


	
endmodule 
	
	