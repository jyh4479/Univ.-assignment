`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    13:23:26 03/08/2019 
// Design Name: 
// Module Name:    IR 
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
module IR(i_clk, IRWrite, i_Instr, o_Instr);
	input [31:0] i_Instr;
	input i_clk, IRWrite;
	output reg [31:0] o_Instr;
	
	always@(posedge i_clk)begin
			if(IRWrite)
				o_Instr 	<= i_Instr;
			else
				o_Instr	<= o_Instr;
	end
	
endmodule
