`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:46:30 05/06/2019 
// Design Name: 
// Module Name:    FA 
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
//Full Adder
module FA(a,
			 b,
			 ci,
			 s);

	input a, b, ci;	//input a, b, carry in
	output s;			//output s

	assign s = a ^ b ^ ci;

endmodule


