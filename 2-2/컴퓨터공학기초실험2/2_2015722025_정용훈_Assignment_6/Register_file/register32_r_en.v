module register32_r_en(clk,reset_n,d_in,d_out,en); //32 bits register
	input clk, reset_n, en; //input
	input [31:0]d_in;
	output [31:0]d_out; //output
	
	register8_r_en U0(.clk(clk),.reset_n(reset_n),.d_in(d_in[7:0]),.d_out(d_out[7:0]),.en(en));//instance register8_r_en
	register8_r_en U1(.clk(clk),.reset_n(reset_n),.d_in(d_in[15:8]),.d_out(d_out[15:8]),.en(en));//instance register8_r_en
	register8_r_en U2(.clk(clk),.reset_n(reset_n),.d_in(d_in[23:16]),.d_out(d_out[23:16]),.en(en));//instance register8_r_en
	register8_r_en U3(.clk(clk),.reset_n(reset_n),.d_in(d_in[31:24]),.d_out(d_out[31:24]),.en(en));//instance register8_r_en
	
endmodule