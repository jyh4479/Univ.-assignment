`timescale 1ns/100ps

module tb_dff_rs_sync_async; //name of test bench
	reg tb_clk, tb_set_n, tb_reset_n, tb_d;
	wire tb_q_sync, tb_q_async;
	//instance the moudle that used test
	_dff_rs_sync_async U0_dff_rs_sync_async(.clk(tb_clk),.set_n(tb_set_n),.reset_n(tb_reset_n),
	.d(tb_d),.q_sync(tb_q_sync),.q_async(tb_q_async));
	
	initial forever #5 tb_clk=~(tb_clk); //setting clock forever
	
	initial
	begin //start test
	#0; 	tb_clk= 0;	tb_set_n= 0; tb_reset_n=0; tb_d= 0;
	#3; 	tb_d= 1;
	#10; 	tb_d= 0;
	#10;	tb_d= 1;
	#10;	tb_d= 0;
	#10;	tb_reset_n= 1; tb_d= 1;
	#10;	tb_reset_n=0;
	#10;	tb_reset_n=1;
	#10; 	tb_d= 0;
	#10; 	tb_d= 1;
	#10; 	tb_d= 0;
	#10;	tb_set_n= 1; tb_d= 1;
	#10; 	tb_d= 0;
	#10; 	tb_d= 1;
	#10; 	tb_d= 0;
	#10;	tb_d= 1;
	#10; $stop;
	end //end
endmodule 
