module _dff_32_r(clk,reset_n,d,q);//Declare module of D Flip Flop

   input clk,reset_n;//inputs
   input [31:0] d; 

   output reg [31:0] q;//output reg

always@(posedge clk or negedge reset_n)//practice function when change variable
begin
   if(reset_n==0) q<=32'b0; //check reset signal

   else q<=d; //data out
end
endmodule

