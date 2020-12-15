`timescale 1ns/100ps

module tb_register32; //name of test bench
	reg tb_clk; //clock
	reg [31:0]tb_d;
	wire [31:0]tb_q;
	//instance the module
	_register32 U0_register32(.clk(tb_clk), .d(tb_d), .q(tb_q));
	
	initial forever #12 tb_clk = ~tb_clk; //run clk forver
	
	initial
	begin //start test
	#0; tb_clk = 0;
	#0; tb_d = 32'h1234_5678;
	#7; tb_d = 32'h9876_5432;
	#7; tb_d = 32'hffee_ddcc;
	#14; tb_d = 32'hbbaa_ccdd;
	#5; tb_d = 32'h7766_5544;
	#10; tb_d = 32'h3322_1100;
	#10; tb_d = 32'h1234_5678;
	#20; $stop;
	end //end
endmodule