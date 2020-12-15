module fa_v2(a, b, ci, s); //fa_v2 for cla
	input a,b,ci; //Declare input
	output s; //Declare output

	wire ws; //Declare wire

//instance other gates for fa_v2
	_xor2 U0_fa(.a(a), .b(b), .y(ws));
	_xor2 U1_fa(.a(ws), .b(ci), .y(s));

endmodule //Declare end of module
