`timescale 1ns/100ps

module tb_dff_en; //testbench
	reg tb_clk, tb_en, tb_d; //input register
	wire tb_q;	//wire
	
	_dff_en U0_dff_en(.clk(tb_clk), .en(tb_en), .d(tb_d), .q(tb_q)); 
	
	initial forever #5 tb_clk= ~tb_clk; //one cycle is 10.
	
	initial //start testbench
	begin
	#0;	tb_clk= 0; tb_en= 1; tb_d= 0; 
	#3;	tb_d= 1;
	#10;	tb_d= 0;
	#10;	tb_d= 1;
	#10;	tb_en= 0;	tb_d= 0;
	#10;	tb_d= 1;
	#10;	tb_d= 0;
	#10;	tb_d= 1;
	#10;	tb_d= 0;
	#15; $stop;
	end
endmodule
