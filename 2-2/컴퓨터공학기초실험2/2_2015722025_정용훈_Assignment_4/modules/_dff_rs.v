module _dff_rs(clk, set_n, reset_n, d, q); //set, reset D flip flop
	input clk, set_n, reset_n, d; //input
	output q; //output
	
	wire w_d1, w_d2; //wire
	
	_or2 U0_or2(.a(d), .b(~set_n), .y(w_d1)); //instance or2
	_and2 U0_and2(.a(w_d1), .b(reset_n), .y(w_d2)); //instance and2
	_dff U0_dff(.clk(clk), .d(w_d2), .q(q)); //instance d flip flop
	
endmodule
