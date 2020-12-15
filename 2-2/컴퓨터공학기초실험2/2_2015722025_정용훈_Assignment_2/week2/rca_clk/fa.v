module fa(a,b,ci,s,co); //initialize full adder
	input a, b, ci; //3 inputs
	output s,co; //2 outputs
	wire sm, c1, c2; //3 wires

	ha U0_ha(.a(b), .b(ci), .s(sm), .co(c1)); //instance half adder in ha.v
	ha U1_ha(.a(a), .b(sm), .s(s), .co(c2)); //instance half adder in ha.v
	_or2 U2_or(.a(c2), .b(c1), .y(co)); //instance or gate in gates.v

endmodule //Declare end of module