module cla_clk(clock, a, b, ci, s_cla, co_cla); //Declare module and factor
	input	clock;  //use clock for filp-flop
	input [31:0] a, b; //Declare 32-bit inputs
	input ci; //Declare input
	output [31:0] s_cla; //Declare 32-bit outputs
	output co_cla; //Declare output

	reg [31:0] reg_a, reg_b; //Declare 32-bit reg
	reg reg_ci; //Declare reg
	reg [31:0] reg_s_cla; //Declare 32-bit reg
	reg reg_co_cla; //Declare reg

	wire [31:0] wire_s_cla; //Declare 32-bit wire
	wire wire_co_cla; //Declare wire

	always @ (posedge clock) //only get the variabla at the rising edge.
	begin //start the content
		reg_a <= a;
		reg_b <= b;
		reg_ci <= ci;
		reg_s_cla <= wire_s_cla;
		reg_co_cla <= wire_co_cla;
	end //end of content

	cla32 U0_cla32(.a(reg_a), .b(reg_b), .ci(reg_ci), .s(wire_s_cla), .co(wire_co_cla)); //instance
	assign s_cla = reg_s_cla;
	assign co_cla = reg_co_cla;
endmodule //Declare end of module
