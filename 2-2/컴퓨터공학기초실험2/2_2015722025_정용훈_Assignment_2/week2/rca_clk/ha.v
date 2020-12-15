module ha(a, b, s, co); //initialize half adder
	input a, b; //initailize 2 inputs
	output s, co; //2 outputs
//	_and2 U0_and(.a(a), .b(b), .y(co)); //use and2 by instancing in gates.v
//	_xor2 U1_xor(.a(a), .b(b), .y(s)); //use xor2 by instancing in gates.v

	assign s = a ^ b; //change the content of instance
	assign co = a & b;

endmodule //Declare end of module