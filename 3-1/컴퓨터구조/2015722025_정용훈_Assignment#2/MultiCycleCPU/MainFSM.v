`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    16:00:42 04/10/2019 
// Design Name: 
// Module Name:    MainFSM 
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
module MainFSM(i_clk, i_rst_n, i_op, i_funct, i_zero, PCWriteCond, PCWrite, IorD, MemRead, MemWrite, MemtoReg, IRWrite, PCSource, 
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
	parameter Mem_Adr = 2;
	parameter Mem_Read = 3;
	parameter Mem_Writeback = 4;
	parameter Mem_Write = 5;
	parameter ADDI_Writeback = 6;
	parameter Execute = 7;
	parameter ALU_Writeback = 8;
	parameter Branch = 9;
	parameter Jump = 12;
	parameter UnDefined = 255;
	
	assign cur_state = state;
	assign nxt_state = next;
	
	always@(posedge i_clk or negedge i_rst_n)begin //sequencial logic
		if(!i_rst_n)
			state <= Fetch;
		else 
			state <= next;
	end

	always@(state, i_op, i_zero)begin  // state & output logic
		next <= 4'bx;  
		case(state)

			Fetch: begin IorD <= 0; 
							 ALUSrcA <= 0;
							 ALUSrcB <= 2'b01;
							 ALUOp <= 2'b00;
							 PCSource <= 0;
							 IRWrite <= 1;
							 PCWrite <= 1;
							 MemRead <= 1;
							 MemWrite <= 0;// necessary, enable unset 
							 PCWriteCond <=0;// necessary, enable unset
							 RegWrite <=0;// necessary, enable unset
							 next <= Decode;
			end
			Decode: begin ALUSrcA <= 0;
							  ALUSrcB <= 2'b11;
							  ALUOp <= 2'b00;
							  MemRead <= 0;// necessary, enable unset, 
							  IRWrite <= 0; // necessary, enable unset
							  PCWrite <= 0; // necessary, enable unset
							  case(i_op)
							  0: begin
									if(i_funct == 6'b0) 	//NOP
										next <= Fetch;
									else
										next <= UnDefined;
							  end
							  2: next <= Jump; //j
							  4: next <= Branch; //beq
							  8: next <= Mem_Adr; //addi
							  35: next <= Mem_Adr; //lw
							  43: next <= Mem_Adr; //sw
							  default: next <= UnDefined;
							  endcase
					   end
			Mem_Adr: begin 
						ALUSrcA <= 1;
					   ALUSrcB <= 2'b10;
					   ALUOp <= 2'b00;
						if(i_op == 35) next <= Mem_Read;
					   else if(i_op == 43) next <= Mem_Write;
						else if(i_op == 8) next <= ADDI_Writeback;
					   else next <= Execute;
						end
			Mem_Read: begin
							 IorD <= 1;
							 MemRead <= 1;
						    next <= Mem_Writeback;
			end					  
			Mem_Writeback: begin 
						  RegDst <= 2'b00;
						  MemtoReg <= 1;
						  RegWrite <= 1;
						  MemRead <= 0;// necessary, enable unset,
						  next <= Fetch;
			end						
			Mem_Write: begin
						  IorD <= 1;
						  MemWrite <= 1;
						  next <= Fetch;
						  end
			Execute: begin
						  ALUSrcA <= 1;
					     ALUSrcB <= 0;
					     ALUOp <= 2;
					     next <= ALU_Writeback;
						  end
			ALU_Writeback: begin 
							 RegDst <= 2'b01;
						    MemtoReg <= 0;
						    RegWrite <= 1;
						    next <= Fetch;
							 end
			ADDI_Writeback: begin 
							 RegDst <= 2'b00;
						    MemtoReg <= 0;
						    RegWrite <= 1;
						    next <= Fetch;
							 end
			Branch: begin 
						  ALUSrcA <= 1;
					     ALUSrcB <= 0;
					     ALUOp <= 1;
					     PCSource <= 1;
					     PCWriteCond <= 1;
						  next <= Fetch;
						  end
			Jump: begin
					PCSource <=2;
					PCWrite <= 1;
					RegWrite <= 0;
					next <= Fetch;
					end
			UnDefined : begin
			    next <= UnDefined;
			    end
			default: next <= state;
		endcase
	end
endmodule
