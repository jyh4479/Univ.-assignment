module _dff_r(clk,reset_n,d,q);//Declare module of D Flip Flop

   input clk,reset_n;//inputs
   input d;

   output reg q;//output reg

always@(posedge clk or negedge reset_n) //practice function when change variable
begin
   if(reset_n==0)	q<=1'b0; //check reset signal

   else q<=d; //data out
end

endmodule

