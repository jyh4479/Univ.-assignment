module _dff_2_r(clk,reset_n,d,q);//Declare module of D Flip Flop

   input clk,reset_n;//inputs
   input [1:0] d; 

   output reg [1:0] q;//output reg

always@(posedge clk or negedge reset_n)//practice function when chage variable
begin
   if(reset_n==0) q<=2'b00;//check reset signal

   else q<=d;//data out
end

endmodule

