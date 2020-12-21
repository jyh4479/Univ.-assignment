`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:49:59 05/06/2019 
// Design Name: 
// Module Name:    R_ID_EX 
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
//Register ID_EX

module R_ID_EX(i_clk, i_rst_n, i_branch_pc, i_read_data1, i_read_data2, i_imm, i_bubble, i_sou_reg, i_tar_reg, 
					i_des_reg, i_WB_control, i_MEM_control, i_EX_control, Flush, o_branch_pc, o_read_data1, o_read_data2, o_imm, 
				   o_sou_reg, o_tar_reg, o_des_reg, o_WB_control, o_MEM_control, o_EX_control);
	input			i_clk, i_rst_n;									//1-bit input clock, active low reset
	input			[31:0]	i_branch_pc;								//32-bit input Next PC
	input			[31:0]	i_read_data1, i_read_data2;		//32-bit input data1, 2 read from register
	input			[31:0]	i_imm;									//32-bit input immediate value sign-extended
	input						i_bubble;
	input			[4:0]		i_sou_reg, i_tar_reg, i_des_reg;	//5-bit input target register address,  destination register address
	input			[1:0]		i_WB_control;							//2-bit input WB control signal
	input			[2:0]		i_MEM_control;							//3-bit input MEM control signal
	input			[3:0]		i_EX_control;							//4-bit input EX control signal
	input						Flush;
	output reg	[31:0]	o_branch_pc;								//32-bit output reg Nexp PC
	output reg	[31:0]	o_read_data1, o_read_data2;		//32-bit output reg data1, 2 read from register
	output reg	[31:0]	o_imm;									//32-bit output reg immediate value sign-extended
	output reg	[4:0]		o_sou_reg, o_tar_reg, o_des_reg;	//5-bit output reg target register address, destination register address
	output reg	[1:0]		o_WB_control;							//2-bit output reg WB control signal
	output reg	[2:0]		o_MEM_control;							//3-bit output reg MEM control signal
	output reg	[3:0]		o_EX_control;							//4-bit output reg EX control signal
	
	//next value reg variables
	reg	[31:0]	Next_o_branch_pc;
	reg	[31:0]	Next_o_read_data1, Next_o_read_data2;
	reg	[31:0]	Next_o_imm;
	reg	[4:0]		Next_o_sou_reg, Next_o_tar_reg, Next_o_des_reg;
	reg	[1:0]		Next_o_WB_control;
	reg	[2:0]		Next_o_MEM_control;
	reg	[3:0]		Next_o_EX_control;
	
	always @ (i_bubble, i_branch_pc, i_read_data1, i_read_data2, i_imm, i_sou_reg, i_tar_reg, i_des_reg, i_WB_control, i_MEM_control, i_EX_control)	begin
		if(i_bubble == 1'b1)	begin
			Next_o_branch_pc 	<= 32'h0;
			Next_o_read_data1 <= 32'h0;
			Next_o_read_data2 <= 32'h0;
			Next_o_imm 			<= 32'h0;
			Next_o_sou_reg		<= 5'h0;
			Next_o_tar_reg		<= 5'h0;
			Next_o_des_reg		<= 5'h0;
			Next_o_WB_control	<= 1'b0;
			Next_o_MEM_control<= 3'b0;
			Next_o_EX_control	<= 4'h0;
		end
		else begin
			Next_o_branch_pc 	<= i_branch_pc;
			Next_o_read_data1 <= i_read_data1;
			Next_o_read_data2 <= i_read_data2;
			Next_o_imm 			<= i_imm;
			Next_o_sou_reg		<= i_sou_reg;
			Next_o_tar_reg		<= i_tar_reg;
			Next_o_des_reg		<= i_des_reg;
			Next_o_WB_control	<= i_WB_control;
			Next_o_MEM_control<= i_MEM_control;
			Next_o_EX_control	<= i_EX_control;
		end
	end
	
	//Define Register
	always @ (posedge i_clk, negedge i_rst_n)	begin
		if(i_rst_n == 1'b0)	begin	//When Reset is 0
			o_branch_pc		<=	32'b0;
			o_read_data1	<= 32'b0;
			o_read_data2	<= 32'b0;
			o_imm				<= 32'b0;
			o_sou_reg		<= 5'b0;
			o_tar_reg		<= 5'b0;
			o_des_reg		<= 5'b0;
			o_WB_control	<= 2'b0;
			o_MEM_control	<= 3'b0;
			o_EX_control	<= 4'b0;
		end
		else if(i_bubble == 1'b1 && Flush == 1'b0) begin
			o_branch_pc		<=	o_branch_pc 	;
			o_read_data1	<= o_read_data1 	;
			o_read_data2	<= o_read_data2 	;
			o_imm				<= o_imm 			;
			o_sou_reg		<= o_sou_reg		;
			o_tar_reg		<= o_tar_reg		;
			o_des_reg		<= o_des_reg		;
			o_WB_control	<= o_WB_control	;
			o_MEM_control	<= o_MEM_control	;
			o_EX_control	<= o_EX_control	;
		end
		else if(i_bubble == 1'b1 && Flush == 1'b1) begin
			o_branch_pc		<=	Next_o_branch_pc 	;
			o_read_data1	<= Next_o_read_data1 ;
			o_read_data2	<= Next_o_read_data2 ;
			o_imm				<= Next_o_imm 			;
			o_sou_reg		<= Next_o_sou_reg		;
			o_tar_reg		<= Next_o_tar_reg		;
			o_des_reg		<= Next_o_des_reg		;
			o_WB_control	<= Next_o_WB_control	;
			o_MEM_control	<= Next_o_MEM_control;
			o_EX_control	<= Next_o_EX_control	;
		end
		else	begin					//Otherwise				
			o_branch_pc		<=	Next_o_branch_pc 	;
			o_read_data1	<= Next_o_read_data1 ;
			o_read_data2	<= Next_o_read_data2 ;
			o_imm				<= Next_o_imm 			;
			o_sou_reg		<= Next_o_sou_reg		;
			o_tar_reg		<= Next_o_tar_reg		;
			o_des_reg		<= Next_o_des_reg		;
			o_WB_control	<= Next_o_WB_control	;
			o_MEM_control	<= Next_o_MEM_control;
			o_EX_control	<= Next_o_EX_control	;
		end
	end	
endmodule
