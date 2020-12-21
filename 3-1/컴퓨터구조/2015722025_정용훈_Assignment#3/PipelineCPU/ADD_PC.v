`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:44:25 05/06/2019 
// Design Name: 
// Module Name:    ADD_PC 
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
//32-bit adder to increment the PC
module ADD_PC(i_data1, i_data2, o_sum);
	input		[31:0]	i_data1, i_data2;	//32-bit input data
	output	[31:0]	o_sum;				//32-bit output data

	//wire variable for adder's carry
	wire c1, c2, c3, c4, c5, c6, c7;

	//Instance of RCA4(4-bit Ripple carry Adder) for 32-bit RCA
	RCA4 U0_RCA4(.a(i_data1[ 3: 0]), .b(i_data2[ 3: 0]), .ci(1'b0), .s(o_sum[ 3: 0]), .co(c1));
	RCA4 U1_RCA4(.a(i_data1[ 7: 4]), .b(i_data2[ 7: 4]), .ci(c1)  , .s(o_sum[ 7: 4]), .co(c2));
	RCA4 U2_RCA4(.a(i_data1[11: 8]), .b(i_data2[11: 8]), .ci(c2)  , .s(o_sum[11: 8]), .co(c3));
	RCA4 U3_RCA4(.a(i_data1[15:12]), .b(i_data2[15:12]), .ci(c3)  , .s(o_sum[15:12]), .co(c4));
	RCA4 U4_RCA4(.a(i_data1[19:16]), .b(i_data2[19:16]), .ci(c4)  , .s(o_sum[19:16]), .co(c5));
	RCA4 U5_RCA4(.a(i_data1[23:20]), .b(i_data2[23:20]), .ci(c5)  , .s(o_sum[23:20]), .co(c6));
	RCA4 U6_RCA4(.a(i_data1[27:24]), .b(i_data2[27:24]), .ci(c6)  , .s(o_sum[27:24]), .co(c7));
	RCA4 U7_RCA4(.a(i_data1[31:28]), .b(i_data2[31:28]), .ci(c7)  , .s(o_sum[31:28]));  //Don't need to carry out

endmodule

