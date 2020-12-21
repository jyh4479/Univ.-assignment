`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    16:42:37 03/09/2019 
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
module ALUControl(funct, ALUOp, ALU_control_input);			// ALU_control module
  input [5:0] funct;
  input [2:0] ALUOp;				
  output [3:0]ALU_control_input;	

  reg [3:0]ALU_control_input;

always@(funct or ALUOp) begin
	if(ALUOp == 3'b000) ALU_control_input<= 4'b0010; 	
   else if(ALUOp == 3'b001) ALU_control_input<= 4'b0110; 	
   else if(ALUOp == 3'b010) begin							
		if(funct == 6'b100000)      ALU_control_input<= 4'b0010;	// => add
      else if(funct == 6'b100010) ALU_control_input<= 4'b0110;	// => sub
      else if(funct == 6'b100100) ALU_control_input<= 4'b0000;	// => and
      else if(funct == 6'b100101) ALU_control_input<= 4'b0001;	// => or
      else if(funct == 6'b101010) ALU_control_input<= 4'b0111;	// => slt
		else if(funct == 6'b100111) ALU_control_input<= 4'b0011;	// => nor
      else if(funct == 6'b000000) ALU_control_input<= 4'b0000;	// when instruction is 32'd0
      else                        ALU_control_input<= ALU_control_input;
	end
	else if(ALUOp==3'b011) 			 ALU_control_input<= 4'b1011;
	else if(ALUOp==3'b100) 			 ALU_control_input<= 4'b0111;
   else  ALU_control_input<= 4'bxxxx;
end

endmodule
