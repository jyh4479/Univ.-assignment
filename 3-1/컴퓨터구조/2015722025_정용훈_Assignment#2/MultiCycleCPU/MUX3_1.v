`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    13:24:55 03/08/2019 
// Design Name: 
// Module Name:    MUX3_1 
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
module MUX3_1(sel, i_data1, i_data2, i_data3, o_data);
	input [31:0] i_data1, i_data2, i_data3;
	input [1:0] sel;
	output reg [31:0] o_data;
	
	always@(i_data1, i_data2, i_data3, sel)begin
		case(sel)
			0: o_data = i_data1;
			1: o_data = i_data2;
			2: o_data = i_data3;
			default : o_data = 32'bx;
		endcase
	end
endmodule
