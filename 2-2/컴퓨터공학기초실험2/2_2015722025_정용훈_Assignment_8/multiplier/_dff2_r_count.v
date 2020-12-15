module _dff2_r_count(clk, reset_n, next_count, count);//for count dff
   input clk, reset_n; //input
   input [4:0]next_count; 
   output reg[4:0]count; //output, reg
   always@(posedge clk or negedge reset_n) begin //asynchronous dff
      if(reset_n == 0) count<=5'b00000; //if reset_n is 0, count is 0
      else count<=next_count; //else, cout is next_count
      end //end content
   endmodule //end modlue