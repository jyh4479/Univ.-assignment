module _dff_for_check(clk,reset_n,next_data_count,a,d,q);//Declare D Flip Flop

   input clk,reset_n;//inputs
   input [3:0] next_data_count;
   input [31:0] d,a;

   output reg [31:0] q;//output reg

always@(posedge clk or negedge reset_n) //practice function when clock or reset_n change(posedge, negedge)
begin
   if(reset_n==0) q<=32'h00000000; //check reset signal

   else if(next_data_count==4'b0111 || next_data_count==4'b1000) q<=a;//check data count

   else q<=d; //data out
end

endmodule