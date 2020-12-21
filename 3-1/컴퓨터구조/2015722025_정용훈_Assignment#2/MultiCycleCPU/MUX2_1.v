`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    13:24:03 03/08/2019 
// Design Name: 
// Module Name:    MUX2_1 
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
module MUX2_1(sel, i_data1, i_data2, o_data);
	input [31:0] i_data1, i_data2;
	input sel;
	output reg [31:0] o_data;
	
	always@(i_data1, i_data2, sel)begin
		if(sel)
			o_data = i_data2;
		else
			o_data = i_data1;
	end
endmodule
