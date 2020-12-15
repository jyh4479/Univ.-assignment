`timescale 1ns/100ps //time scale

module tb_multiplier; //name of module
reg tb_clk,tb_reset_n,tb_op_start, tb_op_clear; //input
reg [31:0] tb_multiplicand,tb_multiplier;
wire tb_op_done; //output
wire [63:0] tb_result; 

multiplier U0_multiplier(.clk(tb_clk),.reset_n(tb_reset_n),.op_start(tb_op_start),.op_clear(tb_op_clear),.multiplicand(tb_multiplicand),.multiplier(tb_multiplier),.result(tb_result),.op_done(tb_op_done)); //Load muliplier

always # 1.5 tb_clk=~tb_clk; //Declare clock purse
initial
begin //set values that used in multiplier
tb_clk=1'b0; tb_reset_n=1'b0; tb_op_clear=0; tb_op_start=0; tb_multiplicand=32'b0; tb_multiplier=32'b0;
#4 tb_reset_n=1'b1; tb_multiplicand=32'h7; tb_multiplier=32'h32;
#3 tb_op_start=1'b1;
#60 tb_multiplicand=32'hb; tb_multiplier=32'h5;
#10 tb_op_start=1'b0;
#10 tb_op_start=1'b1;
#40 tb_multiplicand=32'h26; tb_multiplier=32'h31;
#5 tb_op_clear=1;
#5 tb_op_clear=0;
#50 tb_multiplicand=32'h38; tb_multiplier=32'h49;
#60 tb_multiplicand=32'h25; tb_multiplier=32'h43;
#30 tb_reset_n=0;
#20 tb_reset_n=1;
#10 tb_multiplicand=32'hffffffff; tb_multiplier=32'h5;
#60 tb_multiplicand=32'hFFFFFFF3; tb_multiplier=32'hFFFFFFF9;
#60 $stop;

end //end
endmodule //end moudle
