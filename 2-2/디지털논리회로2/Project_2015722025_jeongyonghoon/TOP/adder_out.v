module adder_out(state,count,result,out_result,fifo_read,op_done,Register_we); //Declare module of OUT state

   input [1:0] state; //inputs
   input [1:0] count;
   input [31:0] result;

   output reg op_done,fifo_read,Register_we; //outputs
   output reg [31:0] out_result;

   parameter IDLE =2'b00; //Declare state paramter
   parameter EXEC =2'b01;
   parameter OUT  =2'b10;
   parameter DONE =2'b11;


always@(state or result or count) //practice function when change each value
begin 
case(state)
IDLE : begin //when IDLE
   fifo_read<=1'b0; //Declare each output
   Register_we<=1'b0;
   op_done<=1'b0;
   out_result<=result;
  end



EXEC : begin //when EXEC
   if(count==2'b10) //Declare each output
  begin //when if count is 2
   Register_we<=1'b1;
   fifo_read<=1'b0;
  end

  else //else
   begin
   fifo_read<=1'b1;
   Register_we=1'b0;
  end

   op_done<=1'b0;
   out_result<=result;
end



OUT : begin //when OUT
   fifo_read<=1'b0; //Declare each output
   Register_we<=1'b1;
   op_done<=1'b0;
   out_result<=result;
  end



DONE : begin //when DONE
   fifo_read<=1'b0; //Declare each output
   Register_we<=1'b0;
   op_done<=1'b1;
   out_result<=result;
  end



default : begin //default
   fifo_read<=1'bx;
   Register_we<=1'bx;
   op_done<=1'bx; 
   out_result<=32'bx;
  end
endcase
end

endmodule
