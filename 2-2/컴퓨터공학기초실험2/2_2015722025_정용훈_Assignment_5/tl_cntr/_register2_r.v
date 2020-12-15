module _register2_r(clk,reset,d,q); //2 bits register
	input clk,reset; //inputs
	input [1:0]d;
	output [1:0]q; //outputs
	//instance register
	_dff_r U0_drr_r(.clk(clk),.reset_n(reset),.d(d[0]),.q(q[0]));
	_dff_r U1_drr_r(.clk(clk),.reset_n(reset),.d(d[1]),.q(q[1]));
	endmodule
