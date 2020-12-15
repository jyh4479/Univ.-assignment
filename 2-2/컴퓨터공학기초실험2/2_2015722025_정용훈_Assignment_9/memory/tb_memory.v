`timescale 1ns/100ps // timescalse
module tb_memory; //name of module
reg clk, cen, wen; //input
reg [7:0] addr;
reg [31:0] din;
wire [31:0] dout; //output

memory U0(clk, cen, wen, addr, din, dout); //load memory

always#(5) clk = ~clk;	//Declare clock

initial
begin
	clk =0; cen=0; wen =0; addr = 8'b0; din = 32'b0; //initial setting
	#10; cen =1; wen =1; addr = 8'h01; din= 32'h0000_0001 ; //The case of saving data to memory
	#10 addr = 8'h02 ; din= 32'h0000_0002 ;
	#10 addr = 8'h03 ; din= 32'h0000_0003 ;
	#10 addr = 8'h04 ; din= 32'h0000_0004 ;
	#10 addr = 8'h05 ; din= 32'h0000_0005 ;
	#10 addr = 8'h06 ; din= 32'h0000_0006 ;
	#10 addr = 8'h01 ; wen =0; //The case of reading data from memory
	#10 addr = 8'h02 ;
	#10 addr = 8'h03 ;
	#10 addr = 8'h04 ;
	#10 addr = 8'h05 ;
	#10 addr = 8'h06 ;
	#10 addr = 8'h07 ;
	#10 addr = 8'h08 ;
	#10 $stop;
end
endmodule