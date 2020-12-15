module _dff2_r_result(reset_n, next_result, result);//The device for result
   input reset_n; //input
   input [63:0]next_result;
   output reg[63:0]result; //output, reg
   always@(next_result or reset_n)   begin //The device run when change value of next_result and reset_n
      if(reset_n == 0) result<=63'b0; //if reset_n is 0, result is 0
      else if(next_result==64'bx) result<=64'b0;
      else result<=next_result; //else, result is next_result
      end //end content
   endmodule //end module