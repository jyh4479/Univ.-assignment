`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:51:33 05/06/2019 
// Design Name: 
// Module Name:    SEU 
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
//Sign Extension Unit
module SEU (i_halfword, o_word);
	input [15:0] 	i_halfword;	//15-bit input word
	output [31:0]	o_word;		//32-bit output word	

	//if sign bit is 1, word[31:16] = 16'hffff, else word[31:16] = 16'h0000;
	assign o_word = (i_halfword[15] == 1'b1) ? {(16'hffff),i_halfword[15:0]} : {16'h0000, i_halfword[15:0]};

endmodule
