module adder_ns(fifo_data_count,op_start,op_clear,wAddr,count,state,next_state,next_count,next_wAddr); //Declare module of next state

   input op_start,op_clear; //inputs
   input [2:0] wAddr;
   input [3:0] fifo_data_count;
   input[1:0] state; 
   input [1:0] count; 

   output reg [1:0] next_state;//outputs regs
   output reg [1:0] next_count; 
   output reg [2:0] next_wAddr;

   parameter IDLE =2'b00; //Declare parameter
   parameter EXEC =2'b01;
   parameter OUT  =2'b10;
   parameter DONE =2'b11;


always@(op_clear or op_start or state or count or fifo_data_count or wAddr) //practice function when change each value
begin
case(state)
IDLE ://when state is IDLE
begin

if(op_clear==1'b1) begin //check condition of clear
   next_state<=IDLE; //initialize
   next_count<=2'b00;
   next_wAddr<=3'b000;
  end

else if(op_start==1'b0) begin //check condition of op_start
   next_state<=state; //mantain state
   next_count<=2'b00;
   next_wAddr<=3'b000;
  end

else begin //else
   next_state<=EXEC; //set calculation
   next_count<=2'b00;
   next_wAddr<=wAddr;
  end
  
end





EXEC : //when EXEC
begin

if(op_clear==1'b1) begin //check condition of clear
   next_state<=IDLE; //initialize
   next_count<=2'b00;
   next_wAddr<=3'b000;
  end

else if(count==2'b10)begin //check count
   next_state<=OUT;
   next_count<=count;
   next_wAddr<=wAddr;
  end

else begin //else
   next_state<=EXEC; //repeat calculation
   next_count<=count+2'b01;
   next_wAddr<=wAddr;
  end
  
end





OUT ://when out
begin

   if(op_clear==1'b1) begin //check condition of clear
   next_state<=IDLE; //initialize
   next_count<=2'b00;
   next_wAddr<=3'b000;
  end

   else if(fifo_data_count==4'b0000) begin //check data count
   next_state<=DONE; //notify done calculation
   next_count<=2'b00;
   next_wAddr<=wAddr;
  end

   else begin //else
   next_state<=IDLE;
   next_count<=2'b00;
   next_wAddr<=wAddr+3'b001;
  end
  
end





DONE : //when done
begin

if(op_clear==1'b1) begin //check condition of clear
   next_state<=IDLE; //initialize
   next_count<=2'b00;
   next_wAddr<=3'b000;
  end

else if(op_start==1'b1) begin //check condition of op_start
   next_state<=DONE;
   next_count<=2'b00;
   next_wAddr<=wAddr;
  end

else begin //else
   next_state<=IDLE; //initialize
   next_count<=2'b00;
   next_wAddr<=wAddr;
  end

end




default : begin // default
   next_state<=2'bxx;
   next_count<=2'bxx;
   next_wAddr<=3'bxxx;
  end
endcase


end
endmodule




