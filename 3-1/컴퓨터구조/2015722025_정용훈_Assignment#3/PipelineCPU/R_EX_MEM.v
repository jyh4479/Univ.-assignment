`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:49:45 05/06/2019 
// Design Name: 
// Module Name:    R_EX_MEM 
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
//Register EX_MEM

module R_EX_MEM(i_clk, i_rst_n, i_branch_pc, i_result, i_zero, i_read_data2, i_write_reg, i_WB_control,
				    i_MEM_control, Flush, Hold, o_branch_pc, o_result, o_zero, o_read_data2, o_write_reg, o_WB_control, o_MEM_control);
	input						i_clk, i_rst_n	;//1-bit input clock, active low reset
	input			[31:0]	i_branch_pc		;//32-bit input calculate the address of the branch
	input			[31:0]	i_result			;//32-bit input operated result
	input 					i_zero			;//1-bit input ALU zero flag
	input			[31:0]	i_read_data2	;//32-bit input data 2 read from register
	input			[4:0]		i_write_reg		;//5-bit input write register number
	input			[1:0]		i_WB_control	;//2-bit input back control signal
	input			[2:0]		i_MEM_control	;//3-bit input Memory access control signal           
	input						Flush, Hold;
	output reg	[31:0]	o_branch_pc		;//32-bit output reg calculate the address of the branch
	output reg	[31:0]	o_result			;//32-bit output reg operated result
	output reg 				o_zero			;//1-bit output reg ALU zero flag
	output reg	[31:0]	o_read_data2	;//32-bit output reg data 2 read from register
	output reg	[4:0]		o_write_reg		;//5-bit output reg write register number
	output reg	[1:0]		o_WB_control	;//2-bit output reg back control signal
	output reg	[2:0]		o_MEM_control	;//3-bit output reg Memory access control signal           
	
	reg						NOP;
	//Define Register
	always @ (posedge i_clk, negedge i_rst_n)	begin
		if(i_rst_n == 1'b0)	begin  //When Reset is 0
			o_branch_pc		<=	32'b0	;	
			o_result			<=	32'b0	;
			o_zero			<=	1'b0	;
			o_read_data2	<=	32'b0	;
			o_write_reg		<=	5'b0	;
			o_WB_control	<=	2'b0	;
			o_MEM_control	<=	3'b0	;
		end
		else	begin			//Otherwise
			o_branch_pc		<= i_branch_pc		;
		   o_result			<= i_result			;
		   o_zero			<= i_zero			;
		   o_read_data2	<= i_read_data2	;
		   o_write_reg		<= i_write_reg		;
		   o_WB_control	<= i_WB_control	;
		   o_MEM_control	<= i_MEM_control	;
		end
	end
endmodule
