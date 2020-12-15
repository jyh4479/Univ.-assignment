module rca(a,b,ci,s,co); //Declares the number of names and factors for a module
input [3:0] a,b; //Declare 4-bit input as a and b
input ci; //Declare ci as input
output [3:0] s; //Declare 4-bit output as s
output co; //Declare co as output

wire [2:0] c;//Wire declaration that connects carry out of full adder
fa U0_fa(.a(a[0]),.b(b[0]),.ci(ci),.s(s[0]),.co(c[0])); //Determine input and output by importing information from Full adder
fa U1_fa(.a(a[1]),.b(b[1]),.ci(c[0]),.s(s[1]),.co(c[1])); //Determine input and output by importing information from Full adder
fa U2_fa(.a(a[2]),.b(b[2]),.ci(c[1]),.s(s[2]),.co(c[2])); //Determine input and output by importing information from Full adder
fa U3_fa(.a(a[3]),.b(b[3]),.ci(c[2]),.s(s[3]),.co(co)); //Determine input and output by importing information from Full adder

endmodule //Declare end of module
