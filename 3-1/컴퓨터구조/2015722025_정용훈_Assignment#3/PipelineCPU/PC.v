`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:48:59 05/06/2019 
// Design Name: 
// Module Name:    PC 
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
//Program counter
module PC(i_clk, i_rst_n, i_next_pc, PC_Write, o_pc);
	input 					i_clk, i_rst_n;		//clock, reset_n
	input						PC_Write;
	input 		[31:0]	i_next_pc;		//32-bit input next program counter
	output reg	[31:0]	o_pc;		//32-bit output program counter

	//define register of PC
	always@(posedge i_clk, negedge i_rst_n)	begin
		if			(i_rst_n==1'b0)		o_pc <= 32'h0000;		//if reset signal is 0, initial to 0
		else if	(PC_Write == 1'b1)	o_pc <= i_next_pc;	//else set to next value
	end

endmodule
