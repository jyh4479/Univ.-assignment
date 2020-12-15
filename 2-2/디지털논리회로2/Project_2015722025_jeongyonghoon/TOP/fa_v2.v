module fa_v2(a,b,ci,s);//Declare module of full adder

   input a,b,ci;//inputs

   output s;//output

   wire p;//wire

_xor2 U0_xor2(.a(a),.b(b),.y(p));//Declare xor gate
_xor2 U1_xor2(.a(p),.b(ci),.y(s));
endmodule
