`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:44:40 05/06/2019 
// Design Name: 
// Module Name:    ALU 
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
//Arithmetic Logic Unit
module ALU (i_data1, i_data2, i_shamt, ALUop, o_result, o_zero);
	input			[31:0]	i_data1, i_data2;	//32-bit input data
	input			[4:0]		i_shamt;				//5-bit shift amount
	input			[3:0]		ALUop;				//4-bit ALU operation code
	output reg	[31:0]	o_result;			//32-bit ALU's resule
	output 					o_zero;				//zero flag

	//wire variable to save each operaton 
	wire	[31:0]	w_and, w_or, w_add, w_sub, w_slt, w_nor, w_sll, w_srl, w_ff;
	reg	[31:0]	w_sra;
	
	//binary encoding
	parameter AND	= 4'b0000;
	parameter OR	= 4'b0001;
	parameter ADD	= 4'b0010;
	parameter SUB	= 4'b0110;
	parameter SLT	= 4'b0111;
	parameter NOR	= 4'b1100;
	parameter SLL	= 4'b1000;
	parameter SRL	= 4'b1001;
	parameter SRA	= 4'b1010;

	//As ALUop, decision o_result
	always@(ALUop, w_and, w_or, w_add, w_sub, w_slt, w_nor, w_sll, w_srl, w_sra)	begin
		case(ALUop)
			AND	:	o_result <= w_and;		//if ALUop is AND
			OR		:	o_result <= w_or;			//if ALUop is OR
			ADD	:	o_result <= w_add;		//if ALUop is ADD
			SUB	:	o_result <= w_sub;		//if ALUop is SUB
			SLT	:	o_result <= w_slt;		//if ALUop is SLT
			NOR	:	o_result <= w_nor;		//if ALUop is NOR
			SLL	:	o_result <=	w_sll;		//if ALUop is SLL
			SRL	:	o_result	<=	w_srl;		//if ALUop is SRL
			SRA	:	o_result	<=	w_sra;		//if ALUop is SRA
			default	:	o_result <= 32'hxx;	//default value
		endcase
	end
	
	//Instance Carry look-Ahead Adder for Addition
	ADD_ALU	U0_ADD_ALU(.i_data1(i_data1), .i_data2(i_data2), .i_cin(1'b0), .o_sum(w_add));
	//Instance Carry look-Ahead Adder for Subtraction
	ADD_ALU	U1_ADD_ALU(.i_data1(i_data1), .i_data2(~i_data2), .i_cin(1'b1), .o_sum(w_sub));
	//And operation
	assign w_and = i_data1 & i_data2;
	//Or operation
	assign w_or = i_data1 | i_data2;
	//Nor operation
	assign w_nor = ~w_or;
	//Slt operation
	assign w_slt = (i_data1 < i_data2) ? 32'h1 : 32'h0;
	//Decision zero flag
	assign o_zero = (o_result[31:0] == 32'h0) ? 1'b0 : 1'b1;		//if result=32'h0, z=1. else z=0
	//Logical Shift left
	assign w_sll = i_data2<<i_shamt;
	//Logical Shift right
	assign w_srl = i_data2>>i_shamt;
	//Arithmatic Shift right	
	assign w_ff = 32'hffffffff<<(32-i_shamt);
	always @ (i_data2, w_srl, w_ff)	begin
		if(i_data2[31] == 1)	w_sra <= w_srl | w_ff;
		else						w_sra <= w_srl;
	end
endmodule
