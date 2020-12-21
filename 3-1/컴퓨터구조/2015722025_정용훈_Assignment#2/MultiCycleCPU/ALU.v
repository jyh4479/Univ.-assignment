`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    13:21:45 03/08/2019 
// Design Name: 
// Module Name:    ALU 
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
module ALU(i_data1, i_data2, ALUop, o_result, o_zero);
	input [31:0] i_data1, i_data2;
	input [3:0] ALUop;
	output o_zero;
	output reg [31:0] o_result;

	assign o_zero = (o_result == 0);
	
	always@(i_data1, i_data2, ALUop) begin
		if(ALUop == 4'b0000)
			o_result <= i_data1 & i_data2;
		else if(ALUop == 4'b0001)
			o_result <= i_data1 | i_data2;
		else if(ALUop == 4'b0010)
			o_result <= i_data1 + i_data2;
		else if(ALUop == 4'b0110)
			o_result <= i_data1 - i_data2;
		else if(ALUop == 4'b0111)
			o_result <= (i_data1 < i_data2);
		else
			o_result <= 32'bz;
	end
endmodule
