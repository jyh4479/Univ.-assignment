`timescale 1ns/100ps

module tb_dff_rs; //testbench Set/Resettable flipflop

	reg tb_clk, tb_set_n, tb_reset_n, tb_d; //input
	wire tb_q; //output

	_dff_rs U0_dff_rs (.clk(tb_clk), .set_n(tb_set_n), . reset_n(tb_reset_n), .d(tb_d), .q(tb_q));

	initial forever #5 tb_clk= ~tb_clk; //one cycle is 10.
	
	initial //start testbench
	begin
	#0; 	tb_clk= 0;	tb_set_n= 0; tb_reset_n=0; tb_d= 0;
	#3; 	tb_d= 1;
	#10; 	tb_d= 0;
	#10;	tb_d= 1;
	#10;	tb_d= 0;
	#10;	tb_reset_n= 1; tb_d= 1;
	#10; 	tb_d= 0;
	#10; 	tb_d= 1;
	#10; 	tb_d= 0;
	#10;	tb_set_n= 1; tb_d= 1;
	#10; 	tb_d= 0;
	#10; 	tb_d= 1;
	#10; 	tb_d= 0;
	#10;	tb_d= 1;
	#10; $stop;
	end
	
endmodule 
