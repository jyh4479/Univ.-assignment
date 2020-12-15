module _register8(clk, d, q); //8 bits register
	input	clk; //for clock
	input[7:0] d;
	output[7:0] q;
	//instance 8 D flip flop
	_dff U0_dff (.clk(clk), .d(d[0]), .q(q[0]));
	_dff U1_dff (.clk(clk), .d(d[1]), .q(q[1]));
	_dff U2_dff (.clk(clk), .d(d[2]), .q(q[2]));
	_dff U3_dff (.clk(clk), .d(d[3]), .q(q[3]));
	_dff U4_dff (.clk(clk), .d(d[4]), .q(q[4]));
	_dff U5_dff (.clk(clk), .d(d[5]), .q(q[5]));
	_dff U6_dff (.clk(clk), .d(d[6]), .q(q[6]));
	_dff U7_dff (.clk(clk), .d(d[7]), .q(q[7]));
	
endmodule