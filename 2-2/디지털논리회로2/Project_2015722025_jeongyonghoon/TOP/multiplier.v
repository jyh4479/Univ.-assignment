module multiplier(fifo_data_count0,fifo_data_count1,clk,reset_n,op_start,op_clear,multiplicand,multiplier,out_result,op_done,fifo_read,fifo_write);
//Declare multiplier

//////////////Port//////////////
   input clk,reset_n,op_clear,op_start; //inputs
   input [3:0] fifo_data_count0,fifo_data_count1;
   input [31:0] multiplicand,multiplier;

   output op_done,fifo_read,fifo_write; //outputs
   output [31:0] out_result; 

   wire [31:0] result, next_result; //wires
   wire [1:0] next_state, state;
   wire [2:0] next_count, count;
   wire [4:0] check_radix; //for checking radix



//////////////instance//////////////
Sel_radix U0_Sel_radix(.multiplier(multiplier),.cal_count(next_count),.check_radix(check_radix));//The logic for checking each radix

multiplier_ns U0_multiplier_ns(.fifo_data_count0(fifo_data_count0),.fifo_data_count1(fifo_data_count1),.op_start(op_start),.op_clear(op_clear),.count(count),.state(state),.next_state(next_state),.next_count(next_count));//The next state logic
multiplier_cal U0_multiplier_cal(.multiplicand(multiplicand),.check_radix(check_radix),.count(count),.state(state),.result(result),.next_result(next_result));//The logic of calculater 
multiplier_out U0_multiplier_out(.count(count),.state(state),.op_done(op_done),.fifo_read(fifo_read),.fifo_write(fifo_write),.result(result),.out_result(out_result));
//Output logic

_dff_2_r U0_dff_2_r(.clk(clk),.reset_n(reset_n),.d(next_state),.q(state));//flip flops
_dff_3_r U0_dff_3_r(.clk(clk),.reset_n(reset_n),.d(next_count),.q(count));
_dff_32_r U0_dff_32_r(.clk(clk),.reset_n(reset_n),.d(next_result),.q(result));
endmodule

