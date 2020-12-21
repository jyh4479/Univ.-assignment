`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:44:09 05/06/2019 
// Design Name: 
// Module Name:    ADD_BR 
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
//32-bit Adder to calculate the branch address
module ADD_BR (i_data1, i_data2, o_sum);
	input		[31:0] 	i_data1, i_data2;	//32-bit inpu data
	output	[31:0]	o_sum;				//32-bit output data

	//wire variable for adder's carry
	wire c1, c2, c3, c4, c5, c6, c7;

	//Instance of CLA4(4-bit Carry Look-Ahead Adder) for 32-bit CLA
	CLA4 U0_CLA4(.a(i_data1[3:0]), .b(i_data2[3:0]), .ci(1'b0), .s(o_sum[3:0]), .co(c1));
	CLA4 U1_CLA4(.a(i_data1[7:4]), .b(i_data2[7:4]), .ci(c1), .s(o_sum[7:4]), .co(c2));
	CLA4 U2_CLA4(.a(i_data1[11:8]), .b(i_data2[11:8]), .ci(c2), .s(o_sum[11:8]), .co(c3));
	CLA4 U3_CLA4(.a(i_data1[15:12]), .b(i_data2[15:12]), .ci(c3), .s(o_sum[15:12]), .co(c4));
	CLA4 U4_CLA4(.a(i_data1[19:16]), .b(i_data2[19:16]), .ci(c4), .s(o_sum[19:16]), .co(c5));
	CLA4 U5_CLA4(.a(i_data1[23:20]), .b(i_data2[23:20]), .ci(c5), .s(o_sum[23:20]), .co(c6));
	CLA4 U6_CLA4(.a(i_data1[27:24]), .b(i_data2[27:24]), .ci(c6), .s(o_sum[27:24]), .co(c7));
	CLA4 U7_CLA4(.a(i_data1[31:28]), .b(i_data2[31:28]), .ci(c7), .s(o_sum[31:28]));  //Don't need to carry out
endmodule
