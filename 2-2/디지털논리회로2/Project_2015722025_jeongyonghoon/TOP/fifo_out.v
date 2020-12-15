module fifo_out(state,data_count,full,empty); // fifo_out logic module
input [2:0] state; // 3bit input variable
input [3:0] data_count; // 4bit input variable
output full,empty; // output variables

parameter INIT =3'b000; // INIT
parameter NO_OP=3'b001; // NO_OP
parameter WRITE =3'b010; // WRITE
parameter WR_ERROR =3'b011; // WR_ERROR
parameter READ =3'b100; // READ
parameter RD_ERROR =3'b101; // RD_ERROR

reg wr_ack,wr_err,rd_ack,rd_err,full,empty; // reg variables

always@(state or data_count) // when input variables change
begin
case(state) // come in change
INIT : // 3'b000
begin
full=1'b0; 
empty=1'b1;
end

NO_OP : // 3'b001
begin 
if(data_count==4'b0000) // when queue is empty
begin
full=1'b0; 
empty=1'b1;
end
else if(data_count==4'b1000) // when queue is full
begin
full=1'b1; 
empty=1'b0;
end
else // when queue is not full and empty
begin
full=1'b0; 
empty=1'b0;
end
end

WRITE :  // 3'b010
begin
if(data_count==4'b1000) // when queue is full
begin
full=1'b1; 
empty=1'b0;
end
else // when queue is not full
begin
full=1'b0; 
empty=1'b0;
end
end

WR_ERROR : // 3'b011
begin
full=1'b1; 
empty=1'b0;
end

READ :  // 3'b100
begin
if(data_count==4'b0000)// when queue is empty
begin
full=1'b0; 
empty=1'b1;
end
else // when queue is not empty
begin
full=1'b0; 
empty=1'b0;
end
end

RD_ERROR : // 3'b101
begin
full=1'b0; 
empty=1'b1;
end

default : // default
begin 
full=1'bx; 
empty=1'bx;
end

endcase
end

endmodule










