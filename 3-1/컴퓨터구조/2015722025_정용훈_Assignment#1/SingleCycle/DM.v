`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    16:42:56 03/09/2019 
// Design Name: 
// Module Name:    DM 
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
//Data Memory module
module DM(i_clk, MemWrite,i_addr, i_data, o_data);

  input i_clk, MemWrite;   //input 1bit clock, read and write signal

 input [31:0]i_addr;               //input 32bit address
  input [31:0]i_data;               //input 32bit data
  output [31:0]o_data;              //output 32bit data

  reg [31:0] o_data;

  reg [7:0]mem[255:0];             //8bit data memory array

  initial
  begin
    $readmemb("C:\\Users\\ASUS\\Desktop\\SingleCycle\\data_memory.txt",mem); //readmemb read binary number from data_memory.txt and store to data memory
  end

  always@(posedge i_clk) begin
    if(MemWrite==1'b1) begin
            mem[i_addr+3]<=i_data[7:0];
            mem[i_addr+2]<=i_data[15:8];
            mem[i_addr+1]<=i_data[23:16];
            mem[i_addr]<=i_data[31:24];
    end
    else begin
				mem[i_addr+3]	<=	mem[i_addr+3];
				mem[i_addr+2]	<= mem[i_addr+2];
				mem[i_addr+1]	<=	mem[i_addr+1];
				mem[i_addr]		<= mem[i_addr];
	 end
  end

  always@(MemWrite or i_addr) begin
        if(MemWrite==1'b0)
          begin
            o_data[7:0] <=mem[i_addr+3];
            o_data[15:8] <=mem[i_addr+2];
            o_data[23:16] <=mem[i_addr+1];
            o_data[31:24] <=mem[i_addr];
          end		
      else;
 end
endmodule
