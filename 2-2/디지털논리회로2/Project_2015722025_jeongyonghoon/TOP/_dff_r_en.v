module _dff_r_en(clk,clear,en,d,q); //Deckare module of D-Flip-Flop

   input clk, clear,en,d; //inputs

   output reg q; //output reg

always@(posedge clk or posedge clear) //practice function when clk posedge or posedge clear
begin
   if(clear==1'b1) q<=1'b0; //check clear

   else if(en) q<=d; //check en

   else q<=q; //else keep data of q
end
endmodule
