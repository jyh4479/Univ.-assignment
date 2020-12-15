`timescale 1ns/100ps

module tb_srlatch; //srlatch testbench
	reg tb_r, tb_s; //input
	wire tb_q, tb_q_bar; //output
	
	_srlatch U0_srlatch(.r(tb_r), .s(tb_s), .q(tb_q), .q_bar(tb_q_bar));
	
	parameter STEP= 10; //step is 10.
	
	initial //start test.
	begin
	#0 		tb_r= 0; tb_s= 0; 
	#STEP;	tb_r= 1;
	#STEP;	tb_r= 0; tb_s= 1;
	#STEP;	tb_r= 1;
	#STEP;				tb_s= 0;
	#STEP;	tb_r= 0; 
	#STEP;	$stop;
	
	end
endmodule
	