`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:48:32 05/06/2019 
// Design Name: 
// Module Name:    MainControl 
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
//Main Control Unit
module MainControl (opcode, RegDst, ALUSrc, MemtoReg, RegWrite, MemRead, MemWrite, Branch, ALUOp, Flush_control, next_PC_control);

	input 		[5:0]	opcode;  //operation code
	//output control signals
	output reg			RegDst, ALUSrc, MemtoReg, RegWrite, MemRead, MemWrite, Branch, Flush_control, next_PC_control;
	output reg	[1:0]	ALUOp;

	always@(opcode)	begin
		case(opcode)
			6'b000000	:	begin		//if opcode is 6'b000000
				RegDst			<= 1'b1;
				ALUSrc			<= 1'b0;
				MemtoReg			<= 1'b0;	
				RegWrite			<= 1'b1;
				MemRead			<= 1'b0;
				MemWrite			<= 1'b0;
				Branch			<= 1'b0;
				ALUOp				<= 2'b10;
				Flush_control	<= 1'b0;
				next_PC_control<= 1'b0;
			end
			6'b100011	:	begin		//if opcode is 6'b100011
				RegDst			<= 1'b0;
				ALUSrc			<= 1'b1;
				MemtoReg			<= 1'b1;	
				RegWrite			<= 1'b1;
				MemRead			<= 1'b1;
				MemWrite			<= 1'b0;
				Branch			<= 1'b0;
				ALUOp				<= 2'b00;
				Flush_control	<= 1'b0;
				next_PC_control<= 1'b0;
			end
			6'b101011	:	begin		//if opcode is 6'b101011
				RegDst			<= 1'b0;
				ALUSrc			<= 1'b1;
				MemtoReg			<= 1'b0;	
				RegWrite			<= 1'b0;
				MemRead			<= 1'b0;
				MemWrite			<= 1'b1;
				Branch			<= 1'b0;
				ALUOp				<= 2'b00;
				Flush_control	<= 1'b0;
				next_PC_control<= 1'b0;
			end
			6'b000101	:	begin		//if opcode is 6'b000100
				RegDst			<= 1'b0;
				ALUSrc			<= 1'b0;
				MemtoReg			<= 1'b0;	
				RegWrite			<= 1'b0;
				MemRead			<= 1'b0;
				MemWrite			<= 1'b0;
				Branch			<= 1'b1;
				ALUOp				<= 2'b01;
				Flush_control	<= 1'b0;
				next_PC_control<= 1'b0;
			end
			6'b000010	:	begin		//if opcode is 6'b000010
				RegDst			<= 1'b0;
				ALUSrc			<= 1'b0;
				MemtoReg			<= 1'b0;	
				RegWrite			<= 1'b0;
				MemRead			<= 1'b0;
				MemWrite			<= 1'b0;
				Branch			<= 1'b0;
				ALUOp				<= 2'b00;
				Flush_control	<= 1'b1;
				next_PC_control<= 1'b1;
			end
			6'b001000	:	begin		//if opcode is 6'b001000
				RegDst			<= 1'b0;
				ALUSrc			<= 1'b1;
				MemtoReg			<= 1'b0;	
				RegWrite			<= 1'b1;
				MemRead			<= 1'b0;
				MemWrite			<= 1'b0;
				Branch			<= 1'b0;
				ALUOp				<= 2'b00;
				Flush_control	<= 1'b0;
				next_PC_control<= 1'b0;
			end
			default	:	begin			//default opcode
				RegDst			<= 1'bx;
				ALUSrc			<= 1'bx;
				MemtoReg			<= 1'bx;	
				RegWrite			<= 1'bx;
				MemRead			<= 1'bx;
				MemWrite			<= 1'bx;
				Branch			<= 1'bx;
				ALUOp				<= 2'bx;
				Flush_control	<= 1'bx;
				next_PC_control<= 1'bx;
			end
		endcase
	end
endmodule
