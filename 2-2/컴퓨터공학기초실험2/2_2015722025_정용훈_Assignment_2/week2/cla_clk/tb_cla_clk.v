`timescale 1ns/100ps //test bench for cla_clk

module tb_cla_clk; //Declare name of module
	reg clock;
	reg [31:0] tb_a, tb_b; //Declare regs
	reg tb_ci;
	wire [31:0] tb_s_cla; //Declare wires
	wire tb_co_cla;

	parameter STEP = 10; //initial for clock

	cla_clk U0_cla_clk(.clock(clock), .a(tb_a), .b(tb_b),
								.ci(tb_ci), .s_cla(tb_s_cla), .co_cla(tb_co_cla)); //instance

	always#(STEP/2) clock = ~clock;  //clock 0 5 and 1 5

	initial
		begin //start content
		clock=1; //clock setting
				tb_a=32'h00000000; tb_b=32'h00000000; tb_ci=0; //put the 32bit number in the test bench variable
		#STEP	tb_a=32'hffffffff;
		#STEP	tb_a=32'h0000ffff; tb_b=32'hffff0000;
		#STEP	tb_a=32'h123fa562; tb_b=32'h35614642;
		#STEP	tb_a=32'h123fa562; tb_b=32'h35614642;
		#STEP	$stop;
		end //end of content
endmodule //Declare end of moudle
