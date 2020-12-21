`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:51:20 05/06/2019 
// Design Name: 
// Module Name:    WB 
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
//Write Back stage module
module WB(i_clk, i_rst_n, i_write_reg, i_write_data, i_result, i_WB_control, o_write_reg, o_write_data, o_RegWrite);
	input						i_clk, i_rst_n;	//clock & reset signal
	input			[4:0]		i_write_reg;		//write register address
	input			[31:0]	i_write_data;		//read data at data memory
	input			[31:0]	i_result;			//ALU operated result
	input			[1:0]		i_WB_control;		//WB control signal
	output		[4:0]		o_write_reg;		//write register address
	output reg  [31:0]	o_write_data;		//read data at data memory
	output					o_RegWrite;			//register file write enable signal
	
	//output register write enable signal
	assign o_RegWrite = i_WB_control[0];
	//output register write address
	assign o_write_reg = i_write_reg;
	
	//set write data as PCSrc control signal
	always@(i_WB_control, i_write_data, i_result)	begin
		if(i_WB_control[1] == 1'b1)	o_write_data <= i_write_data;
		else									o_write_data <= i_result;
	end
endmodule
