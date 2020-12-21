`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    16:41:59 03/09/2019 
// Design Name: 
// Module Name:    ADD_PC 
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

module ADD_PC(i_data1,i_data2,o_sum);
  input [31:0]i_data1;      //input 32bit data
  input [31:0]i_data2;      //input 32bit data
  output [31:0]o_sum;       //output 32bit sum, not carry out
  
  cla32 U0_cla32(.a(i_data1), .b(i_data2), .ci(1'b0), .s(o_sum), .co());  
  
endmodule






