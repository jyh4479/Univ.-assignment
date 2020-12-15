module _dff_4_r(clk,reset_n,d,q);//Declare module of 4bits D Flip Flop
   input clk,reset_n;//inputs
   input [3:0] d;

   output reg [3:0] q;//output reg

always@(posedge clk or negedge reset_n)//practice function when change variable
begin
   if(reset_n==0)	q<=4'b0000;//check reset

   else q<=d;//data out
end

endmodule