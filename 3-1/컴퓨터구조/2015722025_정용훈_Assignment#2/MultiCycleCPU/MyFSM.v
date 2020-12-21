`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    14:41:17 04/11/2019 
// Design Name: 
// Module Name:    MyFSM 
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
module MyFSM(i_clk, i_rst_n, i_op, i_funct, i_zero, PCWriteCond, PCWrite, IorD, MemRead, MemWrite, MemtoReg, IRWrite, PCSource, 
           ALUOp, ALUSrcB, ALUSrcA, RegWrite, RegDst, cur_state, nxt_state);
	
	input [5:0] i_op, i_funct;
	input i_clk, i_rst_n, i_zero;
	output reg IorD, MemtoReg, IRWrite, MemRead, MemWrite, PCWrite, PCWriteCond, RegWrite;
	output reg[1:0]  PCSource, ALUSrcA, ALUSrcB, RegDst;
	output reg[2:0] ALUOp;
	output [7:0] cur_state, nxt_state;
	reg [7:0] state, next;
	
	parameter Fetch = 0;
	parameter Decode = 1;
	parameter UnDefined = 255;
	
	assign cur_state = state;
	assign nxt_state = next;
	
////////////////////////////////////////////////////////////////////////////////////////	
	parameter Type_I = 2; //SLTI & ANDI
	parameter Execute_I = 3;
	
	parameter BGE = 4; //BGE
	
	parameter LWAI_first =5; //LWAI
	parameter LWAI_second = 6;
	parameter LWAI_third = 7;
	parameter LWAI_fourth= 8;
////////////////////////////////////////////////////////////////////////////////////////
	
	always@(posedge i_clk or negedge i_rst_n)begin //sequencial logic
		if(!i_rst_n)
			state <= Fetch;
		else 
			state <= next;
	end
	
	always@(state, i_op, i_zero)begin  // state & output logic
		next <= 4'bx;
		case(state)
			UnDefined : begin
			    next <= UnDefined;
			    end
			Fetch: begin IorD <= 0; 
							 ALUSrcA <= 0;
							 ALUSrcB <= 2'b01;
							 ALUOp <= 2'b00;
							 PCSource <= 0;
							 IRWrite <= 1;
							 PCWrite <= 1;
							 MemRead <= 1;
							 MemWrite <= 0;
							 PCWriteCond <=0;
							 RegWrite <=0;
							 next <= Decode;
						end
			Decode: begin ALUSrcA <= 0;
							  ALUSrcB <= 2'b11;
							  ALUOp <= 2'b00;
							  MemRead <= 0;// necessary, enable unset, 
							  IRWrite <= 0; // necessary, enable unset
							  PCWrite <= 0; // necessary, enable unset
							  case(i_op)
							  6'b001010: next <= 2; //SLTI
							  6'b001100: next <= 2; //ANDI
							  6'b000001: next <= 4; //BGE
							  6'b100100: next <= 5; //LWAI
							  default: next <= UnDefined;
							  endcase
					   end
////////////////////////////////////////////////////////////////////////////////////////
			Type_I: begin //check SLTI or ANDI
						ALUSrcA<=2'b01; //select source
						ALUSrcB<=2'b10;
						case(i_op) //check op code
							6'b001100: begin //ANDI
							ALUOp<=3'b011; //select operation
							next<=Execute_I; //next state
						end
						
						6'b001010: begin //SLTI
							ALUOp<=3'b100; //select operation
							next<=Execute_I; //next state
						end
						
						default: next <= UnDefined;
						endcase
					end
			Execute_I: begin
								RegDst<=2'b00; //select write register
								RegWrite<=1'b1; //write enalbe
								MemtoReg<=1'b0; //select write data
								next <= Fetch;
							end					  
////////////////////////////////////////////////////////////////////////////////////////
			BGE: begin //instruction of BGE
							ALUSrcA<=2'b01; //select source
							ALUSrcB<=2'b00;
							ALUOp<=3'b100; //select operation of slt
							if(i_zero==1'b1) //check flag
								begin //working branch
									PCWriteCond<=1'b1;
									PCSource<=2'b01;
								end //ignore branch
								next <= Fetch;
							end
////////////////////////////////////////////////////////////////////////////////////////
			LWAI_first: begin //start LWAI
							ALUSrcA<=2'b01; //select source
							ALUSrcB<=2'b00;
							ALUOp<=3'b000; //add rs rt
							IorD=1; //for load from memory (rs+rt)
							RegDst<=1; //write data
							next<=LWAI_second;
							end
			LWAI_second: begin
							MemRead<=1; //for read data memory[rs+rt]
							next<=LWAI_third;
						   end	  
			LWAI_third: begin 
							ALUSrcA<=2'b11; //change source of A
							MemtoReg<=2'b01; //select write data
							MemRead<=0; //off read signal
							RegWrite<=1; //on register write
							next<=LWAI_fourth;
							end
			LWAI_fourth: begin
							MemtoReg<=0; //select data (rt + 4)
							RegDst<=0;
							next <= Fetch;
							end
////////////////////////////////////////////////////////////////////////////////////////
			default: next <= state;
		endcase
	end
endmodule
