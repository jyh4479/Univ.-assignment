module _dff_r(clk, reset_n, d, q); //reset D flip flop
	input clk, reset_n, d; //input
	output q; //output
	
	wire w_d; //wires
	
	_and2 U0_and2(.a(d), .y(w_d), .b(reset_n)); //instance and
	_dff U0_dff(.clk(clk), .d(w_d), .q(q)); //instance d flip-flop
endmodule
