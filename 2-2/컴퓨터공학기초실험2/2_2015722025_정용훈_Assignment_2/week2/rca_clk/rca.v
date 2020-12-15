module rca(a,b,ci,s,co); //initialize ripple carry adder
	input [3:0] a,b; //input like array(count is 4)
	input ci; //input
	output [3:0] s; //ouput like array(count is 4)
	output co; //output
	wire [2:0] c; //wire

	fa U0_fa(.a(a[0]),.b(b[0]), .s(s[0]),.ci(ci),.co(c[0])); //instance full adder in fa.v
	fa U1_fa(.a(a[1]),.b(b[1]), .s(s[1]),.ci(c[0]),.co(c[1])); //instance full adder in fa.v
	fa U2_fa(.a(a[2]),.b(b[2]), .s(s[2]),.ci(c[1]),.co(c[2])); //instance full adder in fa.v
	fa U3_fa(.a(a[3]),.b(b[3]), .s(s[3]),.ci(c[2]),.co(co)); //instance full adder in fa.v

endmodule //Declare end of module
