module fa_v2(a, b, ci, s); //fa_v2 for cla
	input a,b,ci;
	output s;
	
	wire ws;
	
	//instance 
	_xor2 U0_fa(.a(a), .b(b), .y(ws));
	_xor2 U1_fa(.a(ws), .b(ci), .y(s));
	
endmodule
