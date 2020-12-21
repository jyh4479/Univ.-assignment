`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:45:00 05/06/2019 
// Design Name: 
// Module Name:    ALUControl 
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
//ALU control unit
module ALUControl(i_funct, i_ALUOp, o_ALU_CS);
	input			[5:0] i_funct;		//6-bit input funct
	input			[1:0] i_ALUOp;		//2-bit input ALUOp
	output reg	[3:0]	o_ALU_CS;	//4-bit output control signal
	
	always@(i_ALUOp, i_funct)	begin
		case(i_ALUOp)
			2'b00	:	o_ALU_CS <= 4'b0010;									//i_ALUOp is 2'b00
			2'b01	:	o_ALU_CS <= 4'b0110;									//i_ALUOp is 2'b01
			2'b10	:	begin														//i_ALUOp is 2'b10
				if(i_funct == 6'b100000)		o_ALU_CS <= 4'b0010;	//i_funct is 6'b100000
				else if(i_funct == 6'b100010)	o_ALU_CS <= 4'b0110;	//i_funct is 6'b100010
				else if(i_funct == 6'b100100)	o_ALU_CS <= 4'b0000;	//i_funct is 6'b100101
				else if(i_funct == 6'b100101)	o_ALU_CS <= 4'b0001; //i_funct is 6'b100101
				else if(i_funct == 6'b101010)	o_ALU_CS <= 4'b0111;	//i_funct is 6'b101010
				else if(i_funct == 6'b000000)	o_ALU_CS	<= 4'b1000; //i_funct is 6'b000000
				else if(i_funct == 6'b000010)	o_ALU_CS	<= 4'b1001; //i_funct is 6'b000010
				else if(i_funct == 6'b000011)	o_ALU_CS	<= 4'b1010; //i_funct is 6'b000011
				else if(i_funct == 6'b100111)	o_ALU_CS	<= 4'b1100; //i_funct is 6'b100111
				else	o_ALU_CS <= 4'bx;										//default i_funct
			end
			default	:								o_ALU_CS <= 4'bx;		//default i_ALUOp
		endcase
	end
endmodule
