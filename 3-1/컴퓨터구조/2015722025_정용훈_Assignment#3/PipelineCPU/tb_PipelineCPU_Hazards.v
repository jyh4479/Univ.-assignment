`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   12:52:24 05/06/2019
// Design Name:   PipelineCPU_Hazards
// Module Name:   C:/project/PipelineCPU_Hazards/tb_PipelineCPU_Hazards.v
// Project Name:  PipelineCPU_Hazards
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: PipelineCPU_Hazards
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module tb_PipelineCPU_Hazards;
	// Inputs
	reg i_clk;
	reg i_rst_n;

	// Outputs
	wire o_h1;
	wire o_h2;
	wire [8:0] o_control;
	wire [31:0] o_data;

	parameter STEP =10; 
	always #(STEP/2) i_clk=~i_clk;  // clock assign
	
	// Instantiate the Unit Under Test (UUT)
	PipelineCPU_Hazards uut (
		.i_clk(i_clk), 
		.i_rst_n(i_rst_n), 
		.o_h1(o_h1), 
		.o_h2(o_h2), 
		.o_control(o_control), 
		.o_data(o_data)
	);

	initial begin
 		i_clk=1'b0; i_rst_n=1'b0;
 		#15; i_rst_n=1'b1;
 		#30000;
 		$stop;

	end
      
endmodule

