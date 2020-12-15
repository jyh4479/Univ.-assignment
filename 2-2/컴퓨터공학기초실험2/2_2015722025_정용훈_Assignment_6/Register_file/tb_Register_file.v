`timescale 1ns/100ps //timescale

module tb_Register_file;
	reg tb_clk,tb_reset_n,tb_we;//tb input
	reg [2:0]tb_wAddr, tb_rAddr;
	reg [31:0]tb_wData;
	wire [31:0]tb_rData;//tb output 
	
	Register_file U0(.clk(tb_clk),.reset_n(tb_reset_n),.wAddr(tb_wAddr),.wData(tb_wData),.we(tb_we),.rAddr(tb_rAddr),.rData(tb_rData));
	//instance Register file
	initial forever #10 tb_clk = ~tb_clk;//Declare clk
	initial
	begin //start test
		  tb_clk = 0; tb_reset_n = 0; tb_we = 0; tb_wAddr = 3'b000; tb_rAddr = 3'b000; tb_wData = 32'h0000_0000;
	#15; tb_reset_n = 1; tb_we = 1; tb_wData = 32'h1111_1111;
	#20; tb_wAddr = 3'b001; tb_wData = 32'h1ff1_ff11;
	#20; tb_wAddr = 3'b101; tb_wData = 32'h1000_f011;
	#20; tb_wAddr = 3'b111; tb_wData = 32'hefef_0101;
	#10; tb_we = 0;
	#10; tb_rAddr = 3'b001;
	#10; tb_rAddr = 3'b101;
	#10; tb_rAddr = 3'b111;
	#10; $stop;
end //end of test

endmodule