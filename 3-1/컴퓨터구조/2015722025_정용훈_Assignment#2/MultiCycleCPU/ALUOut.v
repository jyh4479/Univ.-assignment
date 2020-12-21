`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    13:22:32 03/08/2019 
// Design Name: 
// Module Name:    ALUOut 
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
module ALUOut(i_clk, i_alu_result, o_alu_out);
	
	input [31:0] i_alu_result;
	input i_clk;
	output reg[31:0] o_alu_out;
	
	always@(posedge i_clk)
	begin
		o_alu_out <= i_alu_result;
	end
endmodule

