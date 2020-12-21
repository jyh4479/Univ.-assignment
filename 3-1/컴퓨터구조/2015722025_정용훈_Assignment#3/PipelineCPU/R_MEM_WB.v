`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:50:37 05/06/2019 
// Design Name: 
// Module Name:    R_MEM_WB 
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
//Register MEM_WB
module R_MEM_WB(i_clk, i_rst_n, i_write_reg, i_write_data, i_result, i_WB_control, o_write_reg, o_write_data, o_result, o_WB_control);
	input					 i_clk, i_rst_n;//1-bit input clock, active low reset
	input 		[4:0]	 i_write_reg	;//5-bit input write register number
	input 		[31:0] i_write_data	;//32-bit input memory read data
	input 		[31:0] i_result		;//32-bit input ALU operated result
	input 		[1:0]	 i_WB_control	;//3-bit input WB control signal      
	output reg	[4:0]	 o_write_reg	;//5-bit output reg write register number
	output reg  [31:0] o_write_data	;//32-bit output reg memory read data
	output reg  [31:0] o_result		;//32-bit output reg ALU operated result
	output reg  [1:0]	 o_WB_control	;//3-bit output reg WB control signal      
	//Define Register
	always @ (posedge i_clk, negedge i_rst_n)	begin
		if(i_rst_n == 1'b0)	begin			//When Reset is 0
			o_write_reg		<= 5'b0	;
			o_write_data	<= 32'b0	;
			o_result			<= 32'b0	;
			o_WB_control	<= 2'b0	;
		end
		else	begin							//Otherwise
			o_write_reg		<= i_write_reg	;
			o_write_data	<= i_write_data;
			o_result			<= i_result		;
			o_WB_control	<= i_WB_control;
		end
	end
endmodule
