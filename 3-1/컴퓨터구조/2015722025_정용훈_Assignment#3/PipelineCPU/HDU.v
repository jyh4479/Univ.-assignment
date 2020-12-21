`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:47:28 05/06/2019 
// Design Name: 
// Module Name:    HDU 
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
//Hazard Detection Unit
module HDU(IDEX_Rt, IFID_Rs, IFID_Rt, IDEX_MemRead, Forward_to_hazard, EX_Bubble, PC_Write, IFID_Write, Hold);
	input			[4:0]	IDEX_Rt;			//Rt number comes from ID/EX pipeline register 
	input			[4:0]	IFID_Rs;			//Rs number comes from IF/ID pipeline register
	input			[4:0]	IFID_Rt;			//Rt number comes from IF/ID pipeline register
	input					IDEX_MemRead;	//MemRead control signal comes from ID/EX pipeline register
	input					Forward_to_hazard;
	output reg			EX_Bubble;		//Bubble insert enable signal into the EX stage
	output reg			PC_Write;		//PC write enable signal
	output reg			IFID_Write;		//IF/ID pipeline write enable signal
	output reg			Hold;
	
	//Decide Ex_Bubble, PC_Write, IFID_Write
	always @ (Forward_to_hazard, IDEX_MemRead, IDEX_Rt, IFID_Rs, IFID_Rt)	begin
		//When find Hazard detect
		if((Forward_to_hazard) || ((IDEX_MemRead) && ((IDEX_Rt == IFID_Rs) || (IDEX_Rt == IFID_Rt))))	begin
			EX_Bubble	<= 1'b1;
			PC_Write		<= 1'b0;
			IFID_Write	<= 1'b0;
			Hold			<= 1'b1;
		end
		//Otherwise
		else	begin
			EX_Bubble	<= 1'b0;
			PC_Write		<= 1'b1;
			IFID_Write	<= 1'b1;
			Hold			<= 1'b0;
		end
	end
endmodule
