`timescale 1ns/100ps

module tb_dlatch; //testbench for d latch
	reg tb_clk, tb_d; //input
	wire tb_q, tb_q_bar; //ouput

	_dlatch U0_dlatch (.clk(tb_clk), .d(tb_d), .q(tb_q), .q_bar(tb_q_bar));

	initial forever #5 tb_clk= ~(tb_clk); //one cycle is 10.

	initial// testbench for d latch
	begin
	#0 tb_clk = 0; tb_d = 0;
	#3 tb_d = 1;
	#3 tb_d = 0;
	#6 tb_d = 1;
	#2 tb_d = 0;
	#4 tb_d = 1;
	#4 tb_d = 0;
	#10 $stop;
	end
endmodule 
