`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:45:33 05/06/2019 
// Design Name: 
// Module Name:    CLB 
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
//Carry Look-Ahead block
module CLB (a,
				b,
				ci,
				c1,
				c2,
				c3,
				co);
	
	input [3:0] a, b;				 //4-bit input a, b
	input 		ci;				 //carry in
	output		c1, c2, c3, co; //each bit carry out

	wire [3:0] p, g;				//propagate, generate variable
	
	//generate
	assign g[0] = a[0] & b[0];
	assign g[1] = a[1] & b[1];
	assign g[2] = a[2] & b[2];
	assign g[3] = a[3] & b[3];
	//propagate
	assign p[0] = a[0] | b[0];
	assign p[1] = a[1] | b[1];
	assign p[2] = a[2] | b[2];
	assign p[3] = a[3] | b[3];
	//decision c1, c2, c3, co
	assign c1 = g[0] | (p[0] & ci);
	assign c2 = g[1] | (p[1] & g[0]) | (p[1] & p[0] & ci);
	assign c3 = g[2] | (p[2] & g[1]) | (p[2] & p[1] & g[0]) | (p[2] & p[1] & p[0] & ci);
	assign co = g[3] | (p[3] & g[2]) | (p[3] & p[2] & g[1]) | (p[3] & p[2] & p[1] & g[0]) | (p[3] & p[2] & p[1] & p[0] & ci);

endmodule