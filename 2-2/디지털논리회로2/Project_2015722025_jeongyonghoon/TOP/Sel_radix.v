module Sel_radix(multiplier,cal_count,check_radix); //Declare module of for checking radix

   input [2:0] cal_count; //inputs
   input [31:0] multiplier;

   output reg [4:0] check_radix; //output

   parameter zero=5'b00000; //Declare parameter of count
   parameter once=5'b00001;
   parameter twice=5'b00010;
   parameter third=5'b00011;
   parameter fourth=5'b00100;

always@(cal_count or multiplier) //practice function when change variable
begin
case(cal_count) //check count

zero : check_radix <= 5'bx; //start
once : check_radix <= {multiplier[3:0],1'b0}; //time of calculation
twice : check_radix <= multiplier[7:3];
third : check_radix <= multiplier[11:7];
fourth : check_radix <= multiplier[15:11];

default : check_radix <= 5'bx; // default case
endcase
end
endmodule
