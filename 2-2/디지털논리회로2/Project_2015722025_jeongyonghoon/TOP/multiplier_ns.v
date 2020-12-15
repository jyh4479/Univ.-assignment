module multiplier_ns(fifo_data_count0,fifo_data_count1,op_start,op_clear,count,state,next_state,next_count);

   input op_start,op_clear; //inputs
   input[1:0] state; 
   input [2:0] count; 
   input [3:0] fifo_data_count0,fifo_data_count1;

   output reg [1:0] next_state; //outputs
   output reg [2:0] next_count; 

   parameter IDLE =2'b00; //Declare each parameter
   parameter EXEC =2'b01; 
   parameter OUT  =2'b10; 
   parameter DONE =2'b11; 


always@(op_clear or op_start or state or count or fifo_data_count0 or fifo_data_count1)
//practice function when change each value
begin
case(state)
IDLE : //When IDLE
begin

if(op_clear==1'b1) begin //check condition of clear
   next_state<=IDLE;
   next_count<=3'b000;
  end
  
else if(op_start==1'b0) begin //check condition of op_start
   next_state<=state; 
   next_count<=3'b000;
  end
  
else begin //else
   next_state<=EXEC;
   next_count<=3'b0;
  end
  
end




EXEC : //When EXEC
begin

if(op_clear==1'b1) begin //check condition of clear
   next_state<=IDLE; 
   next_count<=3'b000;
  end
  
else if(count==3'b011)begin //check count
   next_state<=OUT; //change state
   next_count<=count+3'b001;
  end
  
else begin //else
   next_state<=EXEC; //repeat calculate
   next_count<=count+3'b001;
  end
  
end




OUT : //When OUT
begin

   if(op_clear==1'b1) begin //check condition of clear
   next_state<=IDLE;
   next_count<=3'b000; //initialize
   end

   else if(fifo_data_count0==4'b0000 && fifo_data_count1==4'b0000) begin //check count
   next_state<=DONE;
   next_count<=3'b0;
   end

   else begin //else
   next_state<=IDLE; //initialize
   next_count<=3'b000;
  end

end




DONE : //When DONE
begin

if(op_clear==1'b1) begin // clear set
   next_state<=IDLE;
   next_count<=3'b000;
  end
  
if(op_start==1'b1) begin // clear set
   next_state<=DONE;
   next_count<=count; //maintain count
   end

else begin // change next state
   next_state<=IDLE;
   next_count<=3'b000;
  end

end



default : begin // default
   next_state<=2'bx;
   next_count<=3'bx;
  end
endcase


end
endmodule
