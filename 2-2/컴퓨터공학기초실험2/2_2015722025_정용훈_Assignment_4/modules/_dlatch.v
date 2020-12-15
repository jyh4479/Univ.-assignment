module _dlatch(clk,d,q,q_bar); //D latch
	input clk,d; //inputs
	output q,q_bar; //outputs
	wire d_bar,r,s; //wires
	//instance the gates
	_inv U0_inv(.a(d), .y(d_bar));
	_and2 U0_and2(.a(clk), .b(d_bar), .y(r));
	_and2 U1_and2(.a(clk), .b(d), .y(s));
	_srlatch U0_srlatch(.r(r), .s(s), .q(q), .q_bar(q_bar));
	
endmodule
