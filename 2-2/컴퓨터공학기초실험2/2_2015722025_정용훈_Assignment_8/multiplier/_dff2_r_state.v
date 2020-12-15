module _dff2_r_state(clk, reset_n, next_state, state);//The state Flip Flop
   input clk, reset_n; //input
   input [1:0]next_state;
   output reg[1:0]state; //output, reg
   always@(posedge clk or negedge reset_n) begin //asynchronous Flip Flop
      if(reset_n == 0) state<=1'b0; //if reset_n is 0, state is 0
      else state<=next_state; //else state is next_state;
      end //end content
   endmodule //end module