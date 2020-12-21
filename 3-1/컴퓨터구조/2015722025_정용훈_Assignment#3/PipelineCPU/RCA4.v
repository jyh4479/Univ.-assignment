`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:50:52 05/06/2019 
// Design Name: 
// Module Name:    RCA4 
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
//Declare 4-Bit Ripple carry adder module
module RCA4(a,
						b,
						ci,
						s,
						co);		 

	input [3:0] a, b;		//Declare 4-bit input data a or b
	input 			ci;			//Declare 1-bit input carry data
	output [3:0] s;			//Declare 4-bit output sum data
	output 			co;			//Declare 1-bit output carry data
	
	wire [2:0] c;			//Declare wire c[0]~c[2]

	//Full Adder module Instance I0_fa ~ I3_fa
	FA2 U0_FA2(.a(a[0]), .b(b[0]), .ci(ci), .s(s[0]), .co(c[0]));		
	FA2 U1_FA2(.a(a[1]), .b(b[1]), .ci(c[0]), .s(s[1]), .co(c[1]));
	FA2 U2_FA2(.a(a[2]), .b(b[2]), .ci(c[1]), .s(s[2]), .co(c[2]));
	FA2 U3_FA2(.a(a[3]), .b(b[3]), .ci(c[2]), .s(s[3]), .co(co));

endmodule
