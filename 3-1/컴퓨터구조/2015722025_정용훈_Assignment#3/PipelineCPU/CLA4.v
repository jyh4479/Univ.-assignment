`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:45:17 05/06/2019 
// Design Name: 
// Module Name:    CLA4 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
//4-bit Carry look-Ahead Adder
module CLA4(a,
				b,
				ci,
				s,
				co);
	
	input		[3:0]	a, b;	//4-bit input a, b
	input 			ci;	//carry in
	output	[3:0]	s;		//4-bit output s
	output 			co;	//carry out

	//wire variable for carry
	wire c1, c2, c3;

	//Instance FA for CLA
	FA	U0_FA(.a(a[0]), .b(b[0]), .ci(ci), .s(s[0]));
	FA	U1_FA(.a(a[1]), .b(b[1]), .ci(c1), .s(s[1]));
	FA	U2_FA(.a(a[2]), .b(b[2]), .ci(c2), .s(s[2]));
	FA	U3_FA(.a(a[3]), .b(b[3]), .ci(c3), .s(s[3]));
	//Instance CLB for Carry
	CLB	U0_CLB(.a(a), .b(b), .ci(ci), .c1(c1), .c2(c2), .c3(c3), .co(co));

endmodule

