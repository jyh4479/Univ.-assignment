module multiplier(clk, reset_n, multiplier, multiplicand, op_start, op_clear, op_done, result);   //declare module
   input clk; //input
   input reset_n;
   input [31:0] multiplier, multiplicand;
   input op_start, op_clear;

   output reg op_done; //output, reg
   output [63:0] result;

   wire [1:0] state, next_state; //wires
   wire [4:0] count;
   wire [4:0] next_count;
   wire [31:0] next_multiplier,next_multiplicand;
   wire[63:0]next_result;
   
   always@(state)   begin //for check done
      if(state == 2'b10) op_done = 1'b1; //if state is done, op_done is 1
      else op_done = 1'b0; //else, op_done is 0
      end

   multiplier_ns U0_multiplier_ns(.reset_n(reset_n),.op_start(op_start),.op_clear(op_clear),.state(state),.next_count(next_count),.multiplicand(multiplicand),.multiplier(multiplier),.next_multiplicand(next_multiplicand),.next_multiplier(next_multiplier),.next_state(next_state),.count(count));
	//For declaring Next state
   multiplier_cal U1_multiplier_cal(.clk(clk),.op_start(op_start),.reset_n(reset_n),.op_clear(op_clear),.multiplier(next_multiplier),.multiplicand(next_multiplicand),.state(state),.result(next_result),.count(next_count));
	//For Cacluating
   _dff2_r_state U2_dff2_r(.clk(clk), .reset_n(reset_n), .next_state(next_state), .state(state)); //Flip Flop
   _dff2_r_count U3_dff2_r(.clk(clk), .reset_n(reset_n), .next_count(next_count), .count(count));
   _dff2_r_result U4_dff2_r(.reset_n(reset_n),.next_result(next_result),.result(result)); //The device just save value
endmodule //end module