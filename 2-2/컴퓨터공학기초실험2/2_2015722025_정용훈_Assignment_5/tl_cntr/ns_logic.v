module ns_logic(Ta,Tb,s,d); //next state logic
	input Ta,Tb; //inputs
	input [1:0] s;
	output [1:0] d; //outputs
	wire w1,w2; //wires
	
	_and3 U0_and3(.a(~Ta),.b(~s[0]),.c(~s[1]),.y(w1));
	_and3 U1_and3(.a(~Tb),.b(~s[0]),.c(s[1]),.y(w2));
	_or2 U3_or2(.a(w1),.b(w2),.y(d[0]));//D0
	_xor2 U4_xor2(.a(s[0]),.b(s[1]),.y(d[1])); //D1
	
	endmodule
