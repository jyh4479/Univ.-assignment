module _register3_r(clk,reset,d,q); //3 bits register
	input clk,reset; //inputs
	input [2:0]d;
	output [2:0]q; //outputs
	//instance register
	_dff_r U0_dff_r(.clk(clk),.reset_n(reset),.d(d[0]),.q(q[0]));
	_dff_r U1_dff_r(.clk(clk),.reset_n(reset),.d(d[1]),.q(q[1]));
	_dff_r U2_dff_r(.clk(clk),.reset_n(reset),.d(d[2]),.q(q[2]));
endmodule