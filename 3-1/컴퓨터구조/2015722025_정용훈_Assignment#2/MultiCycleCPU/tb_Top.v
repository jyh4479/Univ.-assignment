`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   16:06:26 04/10/2019
// Design Name:   MultiCycleCPU
// Module Name:   C:/Xilinx/Projects/MultiCycle/tb_top.v
// Project Name:  MultiCycle
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: MultiCycleCPU
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module tb_Top;

	// Inputs
	reg i_clk;
	reg i_rst_n;

	// Outputs
	wire [31:0] o_data_out;
	wire [7:0] o_state;

	// Instantiate the Unit Under Test (UUT)
	MultiCycleCPU uut (
		.i_clk(i_clk), 
		.i_rst_n(i_rst_n), 
		.o_data_out(o_data_out), 
		.o_state(o_state)
	);
	always #5 i_clk = ~i_clk;
	initial begin
		// Initialize Inputs
		i_clk = 0;
		i_rst_n = 0;
		#10; i_rst_n=1;
		// Wait 100 ns for global reset to finish
		#560;
		$stop;
		// Add stimulus here

	end
      
endmodule

