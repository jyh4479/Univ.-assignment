module adder(din,op_start,clk,fifo_data_count,op_clear,reset_n,Register_we,op_done,out_result,fifo_read,wAddr); 
//Declare module of adder

   input clk,reset_n,op_clear,op_start;//inputs
   input [3:0] fifo_data_count;
   input [31:0] din;

   output op_done, fifo_read,Register_we;//outputs
   output [2:0] wAddr;
   output [31:0] out_result;

   wire [1:0] state, next_state,count,next_count; //wires
   wire [2:0] next_wAddr;
   wire [31:0] result,next_result;




_dff_2_r U0(.clk(clk),.reset_n(reset_n),.d(next_count),.q(count)); //flip flop
_dff_2_r U1(.clk(clk),.reset_n(reset_n),.d(next_state),.q(state));
_dff_3_r U2(.clk(clk),.reset_n(reset_n),.d(next_wAddr),.q(wAddr));
_dff_32_r U3(.clk(clk),.reset_n(reset_n),.d(next_result),.q(result));




adder_ns U4(.fifo_data_count(fifo_data_count),.op_start(op_start),.op_clear(op_clear),.wAddr(wAddr), //next state
.count(count),.state(state),.next_state(next_state),.next_count(next_count),.next_wAddr(next_wAddr));

adder_cal U5(.din(din),.state(state),.count(count),.result(result),.next_result(next_result)); //calculation

adder_out U6(.state(state),.count(count),.result(result),.out_result(out_result),.fifo_read(fifo_read),.op_done(op_done),.Register_we(Register_we));
//The logic for out

endmodule
