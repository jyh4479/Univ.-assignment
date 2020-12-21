`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:46:58 05/06/2019 
// Design Name: 
// Module Name:    FU 
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
//Forwarding Unit
module FU(IDEX_Rs, IDEX_Rt, EXMEM_Rd, EXMEM_RegWrite, MEMWB_Rd, MEMWB_RegWrite, ForwardA, ForwardB, Forward_to_hazard);
	input			[4:0] IDEX_Rs;				//Rs number comes from ID/EX pipeline register
	input			[4:0] IDEX_Rt;				//Rt number comes from ID/EX pipeline register
	input			[4:0] EXMEM_Rd;			//Rd number comes from EX/MEM pipeline register
	input			[4:0] MEMWB_Rd;			//Rd number comes from MEM/WB pipeline register
	input 				EXMEM_RegWrite;	//RegWrite control signal from EX/MEM pipeline register
	input					MEMWB_RegWrite;	//RegWrite control signal comes from MEM/WB pipeline register
	output reg	[1:0] ForwardA;			//the first ALU operand select signal
	output reg	[1:0] ForwardB;			//the second ALU operand select signal
	output reg 			Forward_to_hazard;
	
	//Decide ForwardA
always @ (EXMEM_RegWrite, EXMEM_Rd, IDEX_Rs, IDEX_Rt, MEMWB_RegWrite, MEMWB_Rd) begin
  if((EXMEM_RegWrite) && (EXMEM_Rd!=0) && (EXMEM_Rd == IDEX_Rs)) begin   //The first ALU operand is forwarded from the prior ALU result
   ForwardA <= 2'b00;
   Forward_to_hazard <= 1;
  end
  else if ((EXMEM_RegWrite) && (EXMEM_Rd != 0) && (EXMEM_Rd == IDEX_Rt)) begin   //addi -> 2
   ForwardB <= 2'b00;
   Forward_to_hazard <= 1;
  end
  else if((MEMWB_RegWrite) && (MEMWB_Rd!=0) && (EXMEM_Rd != IDEX_Rs) && (MEMWB_Rd == IDEX_Rs)) begin //The first ALU operand is forwarded from data memory or an earlier ALU result
   ForwardA <= 2'b00;
   Forward_to_hazard <= 1;
  end
  else if((MEMWB_RegWrite) && (MEMWB_Rd != 0) && (EXMEM_Rd != IDEX_Rt) && (MEMWB_Rd == IDEX_Rt)) begin //lw -> 1
   ForwardB <= 2'b00;
   Forward_to_hazard <= 1;
  end
  else begin
   ForwardA <= 2'b00;  //The first ALU operand comes from the register file
   ForwardB <= 2'b00;
   Forward_to_hazard <= 0;
  end
 end

endmodule
