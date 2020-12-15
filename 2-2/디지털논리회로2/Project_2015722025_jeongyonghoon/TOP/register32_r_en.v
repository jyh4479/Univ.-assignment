module register32_r_en(clk,clear,en,d_in,d_out);//Declare 32bits register

   input clk, clear, en;//inputs
   input [31:0] d_in;

   output [31:0] d_out;//output

register8_r_en U0_register_r_en(.clk(clk),.clear(clear),.en(en),.d_in(d_in[7:0]),.d_out(d_out[7:0]));//Declare number of 4, 8bits registers
register8_r_en U1_register_r_en(.clk(clk),.clear(clear),.en(en),.d_in(d_in[15:8]),.d_out(d_out[15:8]));
register8_r_en U2_register_r_en(.clk(clk),.clear(clear),.en(en),.d_in(d_in[23:16]),.d_out(d_out[23:16]));
register8_r_en U3_register_r_en(.clk(clk),.clear(clear),.en(en),.d_in(d_in[31:24]),.d_out(d_out[31:24]));

endmodule
