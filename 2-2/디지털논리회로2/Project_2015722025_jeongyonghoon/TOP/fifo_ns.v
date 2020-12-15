module fifo_ns(op_clear,wr_en,rd_en,state,data_count,next_state); //Declare module of next state

   input wr_en, rd_en,op_clear;//inputs
   input [2:0] state;
   input [3:0] data_count;

   output [2:0] next_state;//output

   reg [2:0] next_state;//reg

   parameter INIT =3'b000;//Declare parameter
   parameter NO_OP =3'b001;
   parameter WRITE =3'b010;
   parameter WR_ERROR =3'b011;
   parameter READ =3'b100;
   parameter RD_ERROR =3'b101;



always@(wr_en or rd_en or data_count or state or op_clear) //pracitce function when change variable
begin
case(state) //check state
INIT :
begin
if(op_clear==1'b1) next_state<=INIT;

else if(wr_en==1'b1 && rd_en==1'b1) next_state<=NO_OP;

else if(wr_en==1'b1)
  begin
   if(data_count==4'b1000) next_state<=WR_ERROR;
   else next_state<=WRITE;
  end

else if(rd_en==1'b1)
  begin
   if(data_count==4'b0000) next_state<=RD_ERROR;
   else next_state<=READ;
  end
  
else next_state<=NO_OP;
end



NO_OP :
begin
if(op_clear==1'b1) next_state<=INIT;

else if(wr_en==1'b1 && rd_en==1'b1) next_state<=NO_OP;

else if(wr_en==1'b1)
  begin
   if(data_count==4'b1000) next_state<=WR_ERROR;

   else next_state<=WRITE;
  end

else if(rd_en==1'b1)
  begin
   if(data_count==4'b0000) next_state<=RD_ERROR;

   else next_state<=READ;
  end

else next_state<=NO_OP;
end




WRITE :
begin
if(op_clear==1'b1) next_state<=INIT;

else if(wr_en==1'b1 && rd_en==1'b1) next_state<=NO_OP;

else if(wr_en==1'b1)
  begin
   if(data_count==4'b1000) next_state<=WR_ERROR;

   else next_state<=WRITE;
  end

else if(rd_en==1'b1)
  begin
   if(data_count==4'b0000) next_state<=RD_ERROR;

   else next_state<=READ;
  end

else next_state<=NO_OP;
end




WR_ERROR :
begin
if(op_clear==1'b1) next_state<=INIT;

else if(wr_en==1'b1 && rd_en==1'b1) next_state<=NO_OP;

else if(wr_en==1'b1)
  begin
   if(data_count==4'b1000) next_state<=WR_ERROR;

   else next_state<=WRITE;
  end

else if(rd_en==1'b1)
  begin
   if(data_count==4'b0000) next_state<=RD_ERROR;

   else next_state<=READ;
  end

else next_state<=NO_OP;
end




READ :
begin
if(op_clear==1'b1) next_state<=INIT;

else if(wr_en==1'b1 && rd_en==1'b1) next_state<=NO_OP;

else if(wr_en==1'b1)
  begin
   if(data_count==4'b1000) next_state<=WR_ERROR;

   else next_state<=WRITE;
  end

else if(rd_en==1'b1)
  begin
   if(data_count==4'b0000) next_state<=RD_ERROR;

   else next_state<=READ;
  end

else next_state<=NO_OP;
end




RD_ERROR :
begin
if(op_clear==1'b1) next_state<=INIT;

else if(wr_en==1'b1 && rd_en==1'b1) next_state<=NO_OP;

else if(wr_en==1'b1)
  begin
   if(data_count==4'b1000) next_state<=WR_ERROR;

   else next_state<=WRITE;
  end

else if(rd_en==1'b1)
  begin
   if(data_count==4'b0000) next_state<=RD_ERROR;

   else next_state<=READ;
  end

else next_state<=NO_OP;
end



default : next_state=3'bxxx;
endcase
end

endmodule






