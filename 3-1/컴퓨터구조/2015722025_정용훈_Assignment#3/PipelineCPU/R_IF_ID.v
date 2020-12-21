`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:50:14 05/06/2019 
// Design Name: 
// Module Name:    R_IF_ID 
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
//Register IF_ID

module R_IF_ID(i_clk, i_rst_n, i_next_pc, i_data, IFID_Write, IF_Flush, Hold, o_next_pc, o_data, Flush);
   input						i_clk, i_rst_n;	//1-bit clock, active low reset
   input			[31:0]	i_next_pc;			//32-bit input next PC
   input			[31:0]	i_data;				//32-bit input instruction
   input						IFID_Write;			//register enable signal
   input						IF_Flush;			//1-bit Flust
	input						Hold;
   output reg	[31:0]	o_next_pc;			//32-bit output reg next PC
   output reg	[31:0]	o_data;				//32-bit output reg instruction
	output reg				Flush;
	
   reg 			[31:0] 	Next_o_next_pc, Next_o_data;	//32-bit o_next_pc, o_data next value
	reg 			[31:0] 	temp_o_pc, temp_o_data;
	
   always @ (IF_Flush, IFID_Write, i_next_pc, i_data, o_data, o_next_pc)	begin
		if(IF_Flush == 1'b1)   begin			//when IF_Flush is 1
			Next_o_data    <= 32'h0;
         Next_o_next_pc <= 32'h0;
		end
      else if(IFID_Write == 1'b1) begin	//when IFID_Write is 1
			Next_o_data    <= i_data;
         Next_o_next_pc <= i_next_pc;
		end
      else begin									//Otherwise
			Next_o_data    <= o_data;
         Next_o_next_pc <= o_next_pc;
      end
   end
   //Define Register
   always @ (posedge i_clk, negedge i_rst_n)	begin
		if(i_rst_n == 1'b0)	begin //When reset is 0
			o_next_pc   <=   	32'h0;
         o_data      <=   	32'h0;
			Flush			<=		1'b0;
      end
		else if(Hold == 1'b1 && Flush == 1'b0)	begin
			o_next_pc   <=   	Next_o_next_pc;
         o_data      <=   	Next_o_data;
			Flush			<= 	1'b1;
		end
		else if(Hold == 1'b1 && Flush == 1'b1) begin
			o_next_pc   <=   	Next_o_next_pc;
         o_data      <=   	Next_o_data;
			Flush			<=		1'b0;
		end
      else	begin						//otherwise
			o_next_pc   <=   Next_o_next_pc;
         o_data      <=   Next_o_data;
      end
   end	
endmodule
