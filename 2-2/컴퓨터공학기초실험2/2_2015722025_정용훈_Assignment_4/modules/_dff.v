module _dff(clk, d, q, q_bar);  //d flip flop 
	input clk,d;  //input
	output q,q_bar; //output
	wire clk_bar, w_q; //wire
	
	_inv U0_inv(.a(clk), .y(clk_bar));//instance inverter
	_dlatch U0_dlatch(.clk(clk_bar), .d(d), .q(w_q));	 //instance dlatch
	_dlatch U1_dlatch(.clk(clk), .d(w_q), .q(q), .q_bar(q_bar)); //instance dlatch
	
endmodule
