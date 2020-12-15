module ns_logic(Ta,Tal,Tb,Tbl,s,d); //next state logic
	input Ta,Tal,Tb,Tbl; //inputs
	input [2:0]s;
	output [2:0]d; //outputs
	
	wire [2:0]w1,w2; ////wires
	wire [3:0]w3;
	
	_and3 U0_and3(.a(~s[2]),.b(s[1]),.c(s[0]),.y(w1[0])); //D2
	_and2 U1_and2(.a(s[2]),.b(~s[1]),.y(w1[1]));
	_and3 U2_and3(.a(s[2]),.b(s[1]),.c(~s[0]),.y(w1[2]));
	_or3 U3_or3(.a(w1[0]),.b(w1[1]),.c(w1[2]),.y(d[2]));
	
	_and3 U4_and3(.a(~s[2]),.b(~s[1]),.c(s[0]),.y(w2[0]));//D1
	_and2 U5_and2(.a(s[1]),.b(~s[0]),.y(w2[1]));
	_and3 U6_and3(.a(s[2]),.b(~s[1]),.c(s[0]),.y(w2[2]));
	_or3 U7_or3(.a(w2[0]),.b(w2[1]),.c(w2[2]),.y(d[1]));
	
	_and4 U8_and4(.a(~s[2]),.b(~s[1]),.c(~s[0]),.d(~Ta),.y(w3[0]));//D0
	_and4 U9_and4(.a(~s[2]),.b(s[1]),.c(~s[0]),.d(~Tal),.y(w3[1]));
	_and4 U10_and4(.a(s[2]),.b(~s[1]),.c(~s[0]),.d(~Tb),.y(w3[2]));
	_and4 U11_and4(.a(s[2]),.b(s[1]),.c(~s[0]),.d(~Tbl),.y(w3[3]));
	_or4 U12_or4(.a(w3[0]),.b(w3[1]),.c(w3[2]),.d(w3[3]),.y(d[0]));
endmodule