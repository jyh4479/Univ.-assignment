`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:49:25 05/06/2019 
// Design Name: 
// Module Name:    PipelineCPU_Hazards 
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
//Pipeline CPU module

module PipelineCPU_Hazards(i_clk, i_rst_n, o_h1, o_h2, o_control, o_data);
	input i_clk, i_rst_n;	//clock & reset signal
	output o_h1, o_h2;
	output [8:0] o_control;
	output [31:0] o_data;
	
	//Declare all wires of Instruction Fetch
	wire 			PCSrc;
	wire [31:0] i_branch_addr;
	wire [31:0]	o_IF_next_pc, o_IF_Ins;
	wire [31:0] o_pc_plus_four;
	wire			Flush;
	reg  [31:0] i_next_pc;
	
	//Declare all wires of Instruction Decoder stage
	wire 			RegWrite;
	wire [4:0]	i_Write_reg;
	wire [31:0] i_Write_data;
	wire [31:0] o_ID_next_pc, o_ID_read_data1, o_ID_read_data2, o_ID_Imm;
	wire [4:0]	o_ID_sou_reg, o_ID_tar_reg, o_ID_des_reg;
	wire [1:0]	o_ID_WB_control;
	wire [2:0]	o_ID_MEM_control;
	wire [3:0] 	o_ID_EX_control;
	wire			Flush_control;
	wire			next_PC_control;
	
	//Declare all wires of Excution stage
	wire [31:0] o_EX_branch_pc, o_EX_result, o_EX_read_data2;
	wire 			o_EX_zero;
	wire [4:0]	o_EX_write_reg;
	wire [1:0]	o_EX_WB_control;
	wire [2:0]	o_EX_MEM_control;
	//reg			Flush_result;
	
	//Declare all wires of Memory access stage
	wire [4:0]	o_MEM_write_reg;
	wire [31:0] o_MEM_write_data, o_MEM_result;
	wire [1:0]	o_MEM_WB_control;
	
	//Forwarding unit
	wire [1:0] ForwardA, ForwardB;
	wire       Forward_to_hazard;
	
	//Hazard Detection unit
	wire	EX_Bubble;
	wire	PC_Write;
	wire	IFID_Write;
	wire	Hold;
	//Jump address
	wire [31:0] J_addr;
	
	wire [8:0] o_in_con;
	
	assign o_h1 = PCSrc | Flush_control;
	assign o_h2 = PC_Write;
	assign o_control = o_in_con;
	assign o_data = i_Write_data;
	
	//Instance five stage such as Instruction Fetch, Instruction Decoder, Excution, Memory access, Write back state
	IF		U0_IF(.i_clk(i_clk), .i_rst_n(i_rst_n), .i_branch_addr(i_next_pc), .PC_Write(PC_Write), .IFID_Write(IFID_Write), .IF_Flush(PCSrc | Flush_control), .Hold(Hold), .o_prev_pc(o_pc_plus_four), .o_next_pc(o_IF_next_pc), .o_data(o_IF_Ins), .Flush(Flush));
	
	ID		U1_ID(.i_clk(i_clk), .i_rst_n(i_rst_n), .RegWrite(RegWrite), .i_next_pc(o_IF_next_pc), .i_write_reg(i_Write_reg), 
					.i_write_data(i_Write_data), .i_data(o_IF_Ins), .i_stall(PCSrc | EX_Bubble), .Flush(Flush), .o_branch_pc(o_ID_next_pc), 
					.o_read_data1(o_ID_read_data1), .o_read_data2(o_ID_read_data2), .o_imm(o_ID_Imm), .o_sou_reg(o_ID_sou_reg), 
					.o_tar_reg(o_ID_tar_reg), .o_des_reg(o_ID_des_reg), .o_WB_control(o_ID_WB_control), .o_MEM_control(o_ID_MEM_control), 
					.o_EX_control(o_ID_EX_control), .Flush_control(Flush_control), .next_PC_control(next_PC_control),.o_in_con(o_in_con));	
					
	EX		U2_EX(.i_clk(i_clk), .i_rst_n(i_rst_n), .i_branch_pc(o_ID_next_pc), .i_read_data1(o_ID_read_data1), .i_read_data2(o_ID_read_data2), 
					.i_imm(o_ID_Imm), .i_tar_reg(o_ID_tar_reg), .i_des_reg(o_ID_des_reg), .i_WB_control(o_ID_WB_control), 
					.i_MEM_control(o_ID_MEM_control), .i_EX_control(o_ID_EX_control), .Flush(Flush), .Hold(Hold),
					.i_write_data(i_Write_data), .ForwardA(ForwardA), .ForwardB(ForwardB), .EX_Flush(PCSrc),
					.o_branch_pc(o_EX_branch_pc), .o_result(o_EX_result), .o_zero(o_EX_zero),
					.o_read_data2(o_EX_read_data2), .o_write_reg(o_EX_write_reg), .o_WB_control(o_EX_WB_control), .o_MEM_control(o_EX_MEM_control));			 
					
	MEM	U3_MEM(.i_clk(i_clk), .i_rst_n(i_rst_n), .i_branch_pc(o_EX_branch_pc), .i_result(o_EX_result), 
					 .i_zero(o_EX_zero), .i_read_data2(o_EX_read_data2), .i_write_reg(o_EX_write_reg), .i_WB_control(o_EX_WB_control),
					 .i_MEM_control(o_EX_MEM_control), .o_write_reg(o_MEM_write_reg), .o_write_data(o_MEM_write_data),
					 .o_result(o_MEM_result), .o_WB_control(o_MEM_WB_control), .o_branch(PCSrc), .o_branch_pc(i_branch_addr));
					 
	WB		U4_WB(.i_clk(i_clk), .i_rst_n(i_rst_n), .i_write_reg(o_MEM_write_reg), .i_write_data(o_MEM_write_data), 
					.i_result(o_MEM_result), .i_WB_control(o_MEM_WB_control), .o_write_reg(i_Write_reg), .o_write_data(i_Write_data), .o_RegWrite(RegWrite));
					
	FU		U5_FU(.IDEX_Rs(o_ID_sou_reg), .IDEX_Rt(o_ID_tar_reg), .EXMEM_Rd(o_EX_write_reg), .EXMEM_RegWrite(o_EX_WB_control[0]), .MEMWB_Rd(i_Write_reg), .MEMWB_RegWrite(RegWrite), .ForwardA(ForwardA), .ForwardB(ForwardB), .Forward_to_hazard(Forward_to_hazard));
	HDU	U6_HDU(.IDEX_Rt(o_ID_tar_reg), .IFID_Rs(o_IF_Ins[25:21]), .IFID_Rt(o_IF_Ins[20:16]), .IDEX_MemRead(o_ID_MEM_control[1]), .Forward_to_hazard(Forward_to_hazard), .EX_Bubble(EX_Bubble), .PC_Write(PC_Write), .IFID_Write(IFID_Write), .Hold(Hold));
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Decide Next PC input as next_PC_control, PCSrc
	always @ (next_PC_control, PCSrc, o_pc_plus_four, i_branch_addr, J_addr)
	begin
		case({next_PC_control, PCSrc})
			2'b00 : i_next_pc	<= o_pc_plus_four;
			2'b01 : i_next_pc	<= i_branch_addr;
			2'b10 : i_next_pc	<= J_addr;
			default: i_next_pc <= 32'bx;
		endcase
	end
	//compute jump address
	assign J_addr = {o_IF_next_pc[31:28], o_IF_Ins[25:0], 2'b00};
	
endmodule
