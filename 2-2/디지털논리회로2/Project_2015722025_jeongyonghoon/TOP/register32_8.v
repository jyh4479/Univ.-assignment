module register32_8(clk,clear,en,d_in,d_out0,d_out1,d_out2,d_out3,d_out4,d_out5,d_out6,d_out7); //Declare number of 8 32bits registers

   input clk,clear; //inputs
   input [7:0] en;
   input [31:0] d_in;

   output [31:0] d_out0,d_out1,d_out2,d_out3,d_out4,d_out5,d_out6,d_out7;//output

register32_r_en U0_register_r_en(.clk(clk),.clear(clear),.en(en[0]),.d_in(d_in),.d_out(d_out0));//Declare 32bits register for each output
register32_r_en U1_register_r_en(.clk(clk),.clear(clear),.en(en[1]),.d_in(d_in),.d_out(d_out1));
register32_r_en U2_register_r_en(.clk(clk),.clear(clear),.en(en[2]),.d_in(d_in),.d_out(d_out2));
register32_r_en U3_register_r_en(.clk(clk),.clear(clear),.en(en[3]),.d_in(d_in),.d_out(d_out3));
register32_r_en U4_register_r_en(.clk(clk),.clear(clear),.en(en[4]),.d_in(d_in),.d_out(d_out4));
register32_r_en U5_register_r_en(.clk(clk),.clear(clear),.en(en[5]),.d_in(d_in),.d_out(d_out5));
register32_r_en U6_register_r_en(.clk(clk),.clear(clear),.en(en[6]),.d_in(d_in),.d_out(d_out6));
register32_r_en U7_register_r_en(.clk(clk),.clear(clear),.en(en[7]),.d_in(d_in),.d_out(d_out7));

endmodule
