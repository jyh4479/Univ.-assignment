`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:48:47 05/06/2019 
// Design Name: 
// Module Name:    MEM 
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
//Memory access stage module

module MEM(i_clk, i_rst_n, i_branch_pc, i_result, i_zero, i_read_data2, i_write_reg, i_WB_control,
			  i_MEM_control, o_write_reg, o_write_data, o_result, o_WB_control, o_branch, o_branch_pc);
	input					i_clk, i_rst_n;	//clock & reset signal
	input		[31:0]	i_branch_pc;		//PC of branch
	input		[31:0]	i_result;			//input address of memory
	input					i_zero;				//zero flag of ALU output
	input		[31:0]	i_read_data2;		//Write data to memory
	input		[4:0]		i_write_reg;		//address of write register
	input		[1:0]		i_WB_control;		//WB control signals
	input		[2:0]		i_MEM_control;		//MEM control signals
	output	[4:0]		o_write_reg;		//address of write register
	output	[31:0]	o_write_data;		//memory read data
	output	[31:0]	o_result;			//ALU oerated result
	output	[1:0]		o_WB_control;		//WB control signals
	output				o_branch;			//branch control signal
	output	[31:0]	o_branch_pc;		//calculate the address of the branch
	
	wire [31:0] o_DM;	//read data at the Data memory
	
	assign o_branch = i_MEM_control[0] & i_zero;	//set the branch control signal to using PC
	assign o_branch_pc = i_branch_pc;				//calculate the address of the branch
	
	//Instance Data memory, Register MEM/WB
	DM			U0_DM(.i_clk(i_clk), .MemRead(i_MEM_control[1]), .MemWrite(i_MEM_control[2]), .i_addr(i_result), .i_data(i_read_data2), .o_data(o_DM));
	R_MEM_WB	U1_MEM_WB(.i_clk(i_clk), .i_rst_n(i_rst_n), .i_write_reg(i_write_reg), .i_write_data(o_DM), .i_result(i_result), .i_WB_control(i_WB_control), 
							 .o_write_reg(o_write_reg), .o_write_data(o_write_data), .o_result(o_result), .o_WB_control(o_WB_control));
endmodule
