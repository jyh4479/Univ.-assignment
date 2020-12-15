module fifo_cal(state,head,tail,data_count,we,re,next_head,next_tail,next_data_count);

   input [2:0] state, head, tail; //inputs
   input [3:0] data_count;

   output we,re; //outputs
   output [2:0] next_head,next_tail;
   output [3:0] next_data_count;

   reg we,re; //regs
   reg [2:0] next_head,next_tail;
   reg [3:0] next_data_count;

   parameter INIT =3'b000; //Declare paramter
   parameter NO_OP=3'b001;
   parameter WRITE =3'b010;
   parameter WR_ERROR =3'b011;
   parameter READ =3'b100;
   parameter RD_ERROR =3'b101;


always@(state or head or tail or data_count) //practice function when chnaged variable
begin
case(state) //check state
INIT :
begin
   next_head<=3'b000; //initialize
   next_tail<=3'b000;
   next_data_count<=4'b0000;
   we<=1'b0; re<=1'b0;
end



NO_OP :
begin
   next_head<=head; //Keep current
   next_tail<=tail;
   next_data_count<=data_count;

if(data_count==4'b1000) we<=1'b0;
end



WRITE :
begin
if(data_count==4'b0111) next_tail<=tail; //check count and keep current tail

else next_tail<=tail+3'b001; //change tail
   next_data_count<=data_count+4'b0001;
   next_head<=head;
   re<=1'b0; we<=1'b1;
end




WR_ERROR ://write error
begin
   next_head<=head;
   next_tail<=tail;
   next_data_count<=data_count;
   we<=1'b0; re<=1'b0;
end




READ :
begin
if(data_count==4'b1000) next_tail<=tail+3'b001; //check count and change tail

else next_tail<=tail;
   next_data_count<=data_count+4'b1111;
   next_head<=head+3'b001; //change head
   we<=1'b0; re<=1'b1;
end




RD_ERROR : //Read error
begin
   next_head<=head;
   next_tail<=tail;
   next_data_count<=data_count;
   re<=1'b0; we<=1'b0;
end



default : // default
begin
   next_data_count<=4'bx;
   next_head<=3'bx;
   next_tail<=3'bx;
   we<=1'bx; re<=1'bx;
end

endcase
end

endmodule