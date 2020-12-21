`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    13:23:49 03/08/2019 
// Design Name: 
// Module Name:    MDR 
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
module MDR(i_clk,i_data, o_data); //Nonarchitectural Register
	input [31:0] i_data;
	input i_clk;
	output reg[31:0] o_data;
	
	always@(posedge i_clk )begin
			o_data <= i_data;
	end
endmodule
