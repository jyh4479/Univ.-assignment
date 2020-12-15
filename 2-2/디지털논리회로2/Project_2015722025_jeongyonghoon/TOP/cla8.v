module cla8 (a,b,ci,s,co);//8-bit cla
input [7:0] a,b;//8-bit input a,b
input ci; // input carry in
output [7:0] s;//8-bit output s
output co; // output carrt out

wire c1; // wire result of carry out 

//each instance calculate Cout and Sum of 4-bit input. 
cla4 U0_cla4(.a(a[3:0]),.b(b[3:0]),.ci(ci),.s(s[3:0]),.co(c1)); // 4bit cla(3~0)
cla4 U1_cla4(.a(a[7:4]),.b(b[7:4]),.ci(c1),.s(s[7:4]),.co(co)); // 4vit cla(4~7)

endmodule
