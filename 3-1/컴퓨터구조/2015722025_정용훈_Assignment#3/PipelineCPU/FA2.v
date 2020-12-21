`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:46:42 05/06/2019 
// Design Name: 
// Module Name:    FA2 
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
//Declare Full Adder module
module FA2(a, b, ci, s, co);

input a, b, ci;	//Declare input data a or b or carry in
output s, co;		//Declare output data sum or carry out

wire sm;				//Declare wire sm or c[0]~c[1]
wire [1:0]	c;

assign co = c[0]|c[1];

HA U0_HA(.a(b), .b(ci), .s(sm), .co(c[0]));	//Half Adder module Instance  
HA U1_HA(.a(a), .b(sm), .s(s), .co(c[1]));	//Half Adder module Instance 

endmodule
