`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:46:14 05/06/2019 
// Design Name: 
// Module Name:    EX 
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
//Execution stage

module EX(i_clk, i_rst_n, i_branch_pc, i_read_data1, i_read_data2, i_imm, i_tar_reg, i_des_reg, i_WB_control, 
			 i_MEM_control, i_EX_control, i_write_data, ForwardA, ForwardB, EX_Flush, Flush, Hold, o_branch_pc, o_result,
			 o_zero, o_read_data2, o_write_reg, o_WB_control, o_MEM_control);
	input					i_clk, i_rst_n;				//clock, active low reset signal
	input		[31:0]	i_branch_pc;						//32-bit input next_pc
	input		[31:0]	i_read_data1, i_read_data2;//32-bit input read_data1,2
	input		[31:0]	i_imm;							//32-bit input sign-extended imm
	input		[4:0]		i_tar_reg, i_des_reg;		//5-bit input target register, destination register address
	input		[1:0]		i_WB_control;					//2-bit input WB_control signal
	input		[2:0]		i_MEM_control;					//3-bit input MEM_control signal
	input		[3:0]		i_EX_control;					//4-bit input EX_control signal
	input 	[31:0]	i_write_data;					//WB step's write_data
	input		[1:0]		ForwardA, ForwardB;			//Forwarding signal A, B
	input					EX_Flush;						//1-bit WX_Flush signal
	input					Flush, Hold;
	output	[31:0]	o_branch_pc;	//32-bit output branch_pc
	output	[31:0]	o_result;		//32-bit output result
	output				o_zero;			//1-bit output zero flag
	output	[31:0]	o_read_data2;	//32-bit output read_data2
	output	[4:0]		o_write_reg;	//5-bit write register address
	output	[1:0]		o_WB_control;	//2-bit WB_control signal
	output	[2:0]		o_MEM_control;	//3-bit MEM_control signal
	
	wire [3:0] w_alu_cs;		//4-bit wire ALUcontrol output
	wire [31:0] w_ALUSrc;	//32-bit wire ALUSrc mux output
	wire [4:0] w_RegDst;		//5-bit wire RegDst mux output
	wire w_zero;				//1-bit wire zero flag
	wire [31:0] w_result;	//32-bit wire ALU result
	
	reg	[31:0] alu_data1;		//32-bit reg alu input data A
	reg	[31:0] alu_data2;		//32-bit reg alu input data B
	reg	[1:0] r_WB;				//2-bit WB mux result
	reg	[2:0]	r_MEM;			//3-bit MEM mux result
	
	//Three term operator
	assign w_ALUSrc = (i_EX_control[3]) ? (i_imm):(alu_data2);	//ALUSrc mux
	assign w_RegDst = (i_EX_control[0]) ? (i_des_reg):(i_tar_reg);	//RegDst mux;
	
	//Instance of ALU module
	ALU			U0_ALU(.i_data1(alu_data1), .i_data2(w_ALUSrc), .i_shamt(i_imm[10:6]),
							 .ALUop(w_alu_cs), .o_result(w_result), .o_zero(w_zero));
	//Instance of EX_MEM Module
	R_EX_MEM		U1_EX_MEM(.i_clk(i_clk), .i_rst_n(i_rst_n), .i_branch_pc(i_branch_pc), .i_result(w_result),
								.i_zero(w_zero), .i_read_data2(i_read_data2), .i_write_reg(w_RegDst), .i_WB_control(r_WB),
								.i_MEM_control(r_MEM), .Flush(Flush), .Hold(Hold), .o_branch_pc(o_branch_pc), .o_result(o_result), .o_zero(o_zero),
								.o_read_data2(o_read_data2), .o_write_reg(o_write_reg), .o_WB_control(o_WB_control), .o_MEM_control(o_MEM_control));
	//Instance ALUControl module
	ALUControl	U3_ALUControl(.i_funct(i_imm[5:0]), .i_ALUOp(i_EX_control[2:1]), .o_ALU_CS(w_alu_cs));
	
	// 3-to-1 mux for alu_data1 as ForwardA
	always @ (ForwardA, i_read_data1, i_write_data, o_result)	begin
		case(ForwardA)
		2'b00:	alu_data1	<=	i_read_data1;
		2'b01:	alu_data1	<=	i_write_data;
		2'b10:	alu_data1	<=	o_result;
		default:	alu_data1	<=	32'bx;
		endcase
	end
	// 3-to-1 mux for alu_data2 as ForwardB
	always @ (ForwardB, i_read_data2, i_write_data, o_result)	begin
		case(ForwardB)
		2'b00:	alu_data2	<=	i_read_data2;
		2'b01:	alu_data2	<=	i_write_data;
		2'b10:	alu_data2	<=	o_result;
		default:	alu_data2	<=	32'bx;
		endcase
	end
	// 2-to-1 mux for r_WB, r_MEM as  EX_Flush
	always @ (EX_Flush, i_WB_control, i_MEM_control)	begin
		if(EX_Flush == 1'b1)	begin
			r_WB	<=	2'b0;
			r_MEM	<=	3'b0;
		end
		else	begin
			r_WB	<=	i_WB_control;
			r_MEM	<=	i_MEM_control;
		end
	end
endmodule
