`timescale 1ns/100ps

module tb_dff; //testbench
	reg tb_clk, tb_d; //input
	wire tb_q, tb_q_bar;

	_dff U0_dff (.clk(tb_clk), .d(tb_d), .q(tb_q), .q_bar(tb_q_bar));

	initial forever #5 tb_clk = ~tb_clk;//5 up 5 down
	
	initial //initial start
	begin
	#0; tb_clk = 0; tb_d = 0;
	#3; tb_d = 1;
	#3; tb_d = 0;
	#6; tb_d = 1;
	#2; tb_d = 0;
	#4; tb_d = 1;
	#4; tb_d = 0;
	#10; $stop;
	end
endmodule
