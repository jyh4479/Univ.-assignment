module _dff_en(clk, en, d, q); //enable d flip flop
	input clk, en, d;	//input
	output q; //output
	
	wire w_d; //wire
	
	mx2 U0_mx2(.y(w_d), .d0(q), .d1(d), .s(en)); //instance multplexer
	_dff U0_dff(.clk(clk), .d(w_d), .q(q)); //instance d flip flop
	
endmodule
