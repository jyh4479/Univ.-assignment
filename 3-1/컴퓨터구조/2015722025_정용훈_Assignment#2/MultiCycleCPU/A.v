`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    13:21:04 03/08/2019 
// Design Name: 
// Module Name:    A 
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
module A(i_clk,i_x, o_y); //Nonarchitectural Register
	input [31:0] i_x;
	input i_clk;
	output reg[31:0] o_y;
	
	always@(posedge i_clk )begin
			o_y <= i_x;
	end
endmodule

