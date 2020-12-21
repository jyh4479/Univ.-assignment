`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:47:12 05/06/2019 
// Design Name: 
// Module Name:    HA 
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
//Declare Half adder module
module HA(a, b, s, co);

input a, b;		//Declare input data a or b
output s, co;	//Declare output data sum or carry out

assign s = a^b;
assign co = a&b;

endmodule
