`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    16:45:29 03/28/2019 
// Design Name: 
// Module Name:    MyControl 
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
module MyControl(op,RegDst,Jump,Branch,MemtoReg,ALUOp,MemWrite,ALUSrc,RegWrite,PCToReg,ExtMode);
	input [5:0]op;                                                       //input 6bit op code
	output reg [1:0] RegDst;
	output reg Jump,Branch,MemtoReg,MemWrite,ALUSrc,RegWrite,PCToReg,ExtMode;  //output 1bit signals
	output reg [2:0] ALUOp;                                                    //output 3bit ALU Control op code

	
	always@(op) //Repeat function when change opcode
	begin //start always
		case(op) //check case
		6'b100011 : begin // case of lw
						ALUOp <= 3'b000; //Declare working of ALU (ADD)
						ExtMode <= 1'b1; //Practice extend for imm value
						PCToReg <= 1'b0; //Delcare path of data that is loaded
						MemWrite <= 1'b0; //lw is not approach to memory for using store
						MemtoReg <= 1'b1; //Declare path of data, from ALU or memory
						RegWrite <= 1'b1; //For saving data to register
						RegDst <= 2'b00; //Selet write register
						ALUSrc <= 1'b1; //Declare source of ALU
						Jump <= 1'b0; //On the signal if op is JUMP
						Branch <= 1'b0; //On the signal if op is BRANCH
						end
						
		6'b101011 : begin // case of sw
						ALUOp <= 3'b000; //Declare working of ALU (ADD)
						ExtMode <= 1'bx; //don't care
						PCToReg <= 1'b0; //Delcare path of data
						MemWrite <= 1'b1; //On signal for save data
						MemtoReg <= 1'bx; //don't care
						RegWrite <= 1'b0; //For saving data to register
						RegDst <= 2'bxx; //don't care
						ALUSrc <= 1'b1; //Declare source of ALU
						Jump <= 1'b0; //On the signal if op is JUMP
						Branch <= 1'b0; //On the signal if op is BRANCH
						end
						
		6'b000010 : begin// case of jump
						ALUOp <= 3'bx; //don't care
						ExtMode <= 1'bx; //don't care
						PCToReg <= 1'b0; //Delcare path of data
						MemWrite <= 1'b0; //Not approach to memory
						MemtoReg <= 1'bx; //don't care
						RegWrite <= 1'b0; //Not saving data to register
						RegDst <= 2'bxx; //don't care
						ALUSrc <= 1'bx; //don't care
						Jump <= 1'b1; //On the signal if op is JUMP
						Branch <= 1'b0; //On the signal if op is BRANCH
						end
						
		6'b001000 : begin // case of addi
						ALUOp <= 3'b000; //Declare working of ALU (ADD)
						ExtMode <= 1'b1;  //Practice extend for imm value
						PCToReg <= 1'b0; //Delcare path of data that imm + Rs
						MemWrite <= 1'b0; //addi is not approach to memory
						MemtoReg <= 1'b0; //Declare path of data, from ALU or memory
						RegWrite <= 1'b1; //For saving data to register
						RegDst <= 2'b00; //Selet write register
						ALUSrc <= 1'b1; //Declare source of ALU
						Jump <= 1'b0; //On the signal if op is JUMP
						Branch <= 1'b0; //On the signal if op is BRANCH
						end
						
		6'b001110 : begin // case of xori
						ALUOp <= 3'b011; //Delcare working of ALU
						ExtMode <= 1'b0; //For extend imm value
						PCToReg <= 1'b0; //Delcare path of data
						MemWrite <= 1'b0; //Not approach to memory
						MemtoReg <= 1'b0; //don't care
						RegWrite <= 1'b1; //For saving data to register
						RegDst <= 2'b00; //Selet write register
						ALUSrc <= 1'b1; //Declare source of ALU
						Jump <= 1'b0; //On the signal if op is JUMP
						Branch <= 1'b0; //On the signal if op is BRANCH
						end
						
		6'b000100 : begin // case of beq
						ALUOp <= 3'b001; //Declare working of ALU (SUB)
						ExtMode <= 1'b1; //Practice extend for imm value
						PCToReg <= 1'bx; //don't care
						MemWrite <= 1'b0; //Not approach to memory
						MemtoReg <= 1'bx; //don't care
						RegWrite <= 1'b0; //Do not save data to register
						RegDst <= 2'bxx; //don't care
						ALUSrc <= 1'b0; //Declare source of ALU
						Jump <= 1'b0; //On the signal if op is JUMP
						Branch <= 1'b1; //On the signal if op is BRANCH
						end
						
		6'b001010 : begin // case of slti
						ALUOp <= 3'b100; //Delcare working of ALU
						ExtMode <= 1'b1; //Practice extend for imm value
						PCToReg <= 1'b0; //Delcare path of data
						MemWrite <= 1'b0; //Not approach to memory
						MemtoReg <= 1'b0; //Declare path of data, from ALU or memory
						RegWrite <= 1'b1; //For saving data to register
						RegDst <= 2'b00; //Selet write register
						ALUSrc <= 1'b1; //Declare source of ALU
						Jump <= 1'b0; //On the signal if op is JUMP
						Branch <= 1'b0; //On the signal if op is BRANCH
						end
						
		6'b000011 : begin // case of jal
						ALUOp <= 3'bx; //don't care
						ExtMode <= 1'bx; //don't care
						PCToReg <= 1'b1; //Delcare path of data
						MemWrite <= 1'b0; //Not approach to memory
						MemtoReg <= 1'bx; //don't care
						RegWrite <= 1'b1; //For saving data to register
						RegDst <= 2'b10; //Selet write register
						ALUSrc <= 1'bx; //don't care
						Jump <= 1'b1; //On the signal if op is JUMP
						Branch <= 1'bx; //don't care
						end
						
		6'b000000 : begin // case of R-type intruction
						ALUOp <= 3'b010; //Delcare working of ALU
						ExtMode <= 1'bx; //don't care
						PCToReg <= 1'b0; //Delcare path of data
						MemWrite <= 1'b0; //Not approach to memory
						MemtoReg <= 1'b0; //Declare path of data, from ALU or memory
						RegWrite <= 1'b1; //approach to register for saving data to register
						RegDst <= 2'b01; //Selet write register
						ALUSrc <= 1'b0; //Declare source of ALU
						Jump <= 1'b0; //On the signal if op is JUMP
						Branch <= 1'b0; //On the signal if op is BRANCH
						end
						
		default : begin // default case
						ALUOp <= 3'bx; //don't care
						ExtMode <= 1'bx;
						PCToReg <= 1'bx;
						MemWrite <= 1'bx;
						MemtoReg <= 1'bx;
						RegWrite <= 1'bx;
						RegDst <= 2'bx; 
						ALUSrc <= 1'bx;
						Jump <= 1'bx;
						Branch <= 1'bx;
						end
				endcase
	end
endmodule