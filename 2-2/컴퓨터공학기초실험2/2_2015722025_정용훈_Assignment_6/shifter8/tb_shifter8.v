`timescale 1ns/100ps
module tb_shifter8;
	reg tb_clk, tb_reset_n; 
	reg [2:0] tb_op;
	reg [1:0] tb_shamt;
	reg [7:0] tb_d_in;
	wire [7:0] tb_d_out;
	
		shifter8 test_shifter8(.clk(tb_clk),.reset_n(tb_reset_n),
							.op(tb_op),.shamt(tb_shamt),
							.d_in(tb_d_in),.d_out(tb_d_out)); //instance shifter8
	
	always #5 tb_clk = ~tb_clk;
	
	initial
		begin
	tb_clk=1; tb_reset_n=0;tb_op=0;tb_d_in=0;tb_shamt=0;
	#12.5; tb_reset_n=1;
	#10; tb_op=3'b001; tb_d_in=8'b01110111;
	#20; tb_op=3'b010;
	#20; tb_shamt=2'b10;
	#30; tb_op=3'b011;
	#15; $stop;
		
		end
endmodule