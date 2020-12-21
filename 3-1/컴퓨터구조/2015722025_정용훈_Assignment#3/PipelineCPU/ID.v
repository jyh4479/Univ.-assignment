`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:47:47 05/06/2019 
// Design Name: 
// Module Name:    ID 
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
//Instruction Decoder stage module

module ID(i_clk, i_rst_n, RegWrite, i_next_pc, i_write_reg, i_write_data, i_data, i_stall, Flush,
			 o_branch_pc, o_read_data1, o_read_data2, o_imm, o_sou_reg, o_tar_reg, o_des_reg, o_WB_control, 
			 o_MEM_control, o_EX_control, Flush_control, next_PC_control,o_in_con);
	input					i_clk, i_rst_n;						//clock & reset signal
	input					RegWrite;								//Regsiter write signal
	input		[31:0]	i_next_pc;								//Next of pc
	input		[4:0]		i_write_reg;							//address of write register
	input		[31:0]	i_write_data;							//write data
	input		[31:0]	i_data;									//instruction format
	input					i_stall;									//select signal for Control signal mux 
	input					Flush;
	output	[31:0]	o_branch_pc;							//Branch of pc
	output	[31:0]	o_read_data1, o_read_data2;		//two register read data
	output	[31:0]	o_imm;									//immediate value
	output	[4:0]		o_sou_reg, o_tar_reg, o_des_reg;	//address of target and destination register
	output	[1:0]		o_WB_control;							//WB control signal
	output	[2:0]		o_MEM_control;							//MEM control signal
	output	[3:0]		o_EX_control;							//EX control signal
	output				Flush_control;							//1-bit Flush control signal
	output				next_PC_control;						//1-bit next_PC control signal
	output [8:0] o_in_con;
	
	wire [31:0]	o_RF1, o_RF2;	//two output data of regsiter file
	wire [31:0]	o_SEU;			//output of SEU
	//outputs of Main control logic
	wire [1:0]	o_WB;				
	wire [2:0]	o_MEM;			
	wire [3:0]	o_EX;
	wire [31:0] w_branch_pc;
	
	reg	[1:0]	r_WB;
	reg	[2:0]	r_MEM;
	reg	[3:0]	r_EX;
	
	assign o_in_con = {r_WB, r_MEM, r_EX};
	
	//Instance of Register file, Register ID_EX, Sign extend unit, Main control logic
	RF 			U0_RF(.i_clk(i_clk), .i_rst_n(i_rst_n), .i_Read_reg1(i_data[25:21]), .i_Read_reg2(i_data[20:16]),	.i_Write_reg(i_write_reg),
							.i_Write_data(i_write_data),	.RegWrite(RegWrite), .o_Read_data1(o_RF1), .o_Read_data2(o_RF2));
	
	R_ID_EX 		U1_ID_EX(.i_clk(i_clk), .i_rst_n(i_rst_n), .i_branch_pc(w_branch_pc), .i_read_data1(o_RF1), .i_read_data2(o_RF2), .i_imm(o_SEU),
								.i_bubble(i_stall),	.i_sou_reg(i_data[25:21]), .i_tar_reg(i_data[20:16]), .i_des_reg(i_data[15:11]), 
								.i_WB_control(r_WB), .i_MEM_control(r_MEM), .i_EX_control(r_EX), .Flush(Flush), .o_branch_pc(o_branch_pc),
								.o_read_data1(o_read_data1), .o_read_data2(o_read_data2), .o_imm(o_imm), .o_sou_reg(o_sou_reg), .o_tar_reg(o_tar_reg), 
								.o_des_reg(o_des_reg), .o_WB_control(o_WB_control), .o_MEM_control(o_MEM_control), .o_EX_control(o_EX_control));
								
	SEU			U2_SEU(.i_halfword(i_data[15:0]), .o_word(o_SEU));
	MainControl U3_MainControl(.opcode(i_data[31:26]), .RegDst(o_EX[0]), .ALUSrc(o_EX[3]), .MemtoReg(o_WB[1]), .RegWrite(o_WB[0]), 
										.MemRead(o_MEM[1]), .MemWrite(o_MEM[2]), .Branch(o_MEM[0]), .ALUOp(o_EX[2:1]),
										.Flush_control(Flush_control), .next_PC_control(next_PC_control));
										
	ADD_BR		U4_ADD_BR (.i_data1(o_SEU<<2), .i_data2(i_next_pc), .o_sum(w_branch_pc));
	
	// 3-to-1 multiplexer for control signal
	always @ (i_stall, o_WB, o_MEM, o_EX)	begin
		if	(i_stall == 1'b1)	begin		//when i_stall signal is 1
			r_WB 		<=		2'b0;
			r_MEM		<=		3'b0;
			r_EX		<=		4'b0;
		end
		else	begin							//Otherwise
			r_WB 		<=		o_WB;
			r_MEM		<=		o_MEM;
			r_EX		<=		o_EX;
		end
	end
endmodule
