module multiplier_out(count,state,op_done,fifo_read,fifo_write,result,out_result); //Declare module of out logic

   input [1:0] state;//inputs
   input [2:0] count;
   input [31:0] result;

   output reg op_done,fifo_read,fifo_write;//output regs
   output reg [31:0] out_result;

   parameter IDLE =2'b00;//Declare parameter
   parameter EXEC =2'b01;
   parameter OUT  =2'b10;
   parameter DONE =2'b11;



always@(state or result or count)//practice function when changed variable
begin 
case(state)//check state
IDLE : begin
   fifo_read<=1'b0;
   fifo_write<=1'b0;
   op_done<=1'b0;
   out_result<=result;
  end


EXEC : begin //EXEC
   if(count==3'b011) fifo_read<=1'b1;

   else fifo_read<=1'b0;

   fifo_write<=1'b0;
   op_done<=1'b0;
   out_result<=result;
  end


OUT : begin //OUT
   fifo_read<=1'b0;
   fifo_write<=1'b1;
   op_done<=1'b0;
   out_result<=result;
  end


DONE : begin //DONE
   fifo_read<=1'b0;
   fifo_write<=1'b0;
   op_done<=1'b1;
   out_result<=result;
  end


default : begin //default
   fifo_read<=1'bx;
   fifo_write<=1'bx;
   op_done<=1'bx;
   out_result<=32'bx;
  end
endcase
end

endmodule
