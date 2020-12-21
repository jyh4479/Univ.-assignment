`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:47:59 05/06/2019 
// Design Name: 
// Module Name:    IF 
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
//Instruction Fetch stage module

module IF(i_clk, i_rst_n, i_branch_addr, PC_Write, IFID_Write, IF_Flush, Hold, o_prev_pc, o_next_pc, o_data, Flush);
	input				i_clk, i_rst_n;	//clock & reset signal
	input	 [31:0]	i_branch_addr;		//on of input of pc
	input				PC_Write;			//1-bit PC_Write signal
	input				IFID_Write;			//1-bit IFID_Write signal
	input				IF_Flush;			//1-bit Flush flag
	input				Hold;
	output [31:0]	o_prev_pc;			//PC + 4 value
	output [31:0]	o_next_pc;			//output IF_ID(next pc)
	output [31:0]	o_data;				//instruction data
	output 			Flush;
	
	wire [31:0] o_pc;			//output of pc
	wire [31:0]	o_ADD_PC;	//output of adder
	wire [31:0]	o_IM;			//output of IM
	wire			flush;
	
	assign Flush = flush;
	
	//Instance PC, IM, Register of IF_ID, Adder of pc
	PC 		U0_PC(.i_clk(i_clk), .i_rst_n(i_rst_n), .i_next_pc(i_branch_addr), .PC_Write(PC_Write), .o_pc(o_pc));
	IM 		U1_IM(.i_addr(o_pc), .o_instr(o_IM));
	R_IF_ID	U2_IF_ID(.i_clk(i_clk), .i_rst_n(i_rst_n), .i_next_pc(o_ADD_PC), .i_data(o_IM), .IFID_Write(IFID_Write), .IF_Flush(IF_Flush), 
							.Hold(Hold), .o_next_pc(o_next_pc), .o_data(o_data), .Flush(flush));
							
	ADD_PC	U3_ADD_PC(.i_data1(o_pc), .i_data2(4), .o_sum(o_ADD_PC));
	
	assign o_prev_pc = o_ADD_PC; //For next_pc value
	
endmodule
