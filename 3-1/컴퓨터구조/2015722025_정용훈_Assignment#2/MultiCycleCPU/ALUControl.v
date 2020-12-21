`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    15:00:44 03/08/2019 
// Design Name: 
// Module Name:    ALUControl 
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
module ALUControl(i_funct, i_ALUop, o_ALUctrl);
	input [2:0] i_ALUop;
	input [5:0] i_funct;
	output reg[3:0] o_ALUctrl;
	
always@(i_ALUop, i_funct)begin
		case(i_ALUop)
		3'b000: o_ALUctrl <= 4'b0010;
		3'b001: o_ALUctrl <= 4'b0110;
		3'b010: begin
			case(i_funct)
				6'b000000: o_ALUctrl <= 4'b0010; // NOP
				6'b100000: o_ALUctrl <= 4'b0010; // add
				6'b100010: o_ALUctrl <= 4'b0110; // sub
				6'b100100: o_ALUctrl <= 4'b0000; // and
				6'b100101: o_ALUctrl <= 4'b0000; // or
				6'b101010: o_ALUctrl <= 4'b0111; // slt
				default: o_ALUctrl <= 4'bx;
			endcase
			end
		3'b011: o_ALUctrl <= 4'b0000; // andi
		3'b100: o_ALUctrl <= 4'b0111; // slti
		endcase
	end
endmodule
