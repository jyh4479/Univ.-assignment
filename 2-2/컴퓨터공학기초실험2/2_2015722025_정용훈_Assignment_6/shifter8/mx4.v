module mx4(y,d0,d1,d2,d3,s);
input d0,d1,d2,d3;
input [1:0] s;
output y;
wire [1:0] w1;

mx2 U0_mx2(.d0(d0),.d1(d1),.s(s[0]),.y(w1[0]));
mx2 U1_mx2(.d0(d2),.d1(d3),.s(s[0]),.y(w1[1]));
mx2 U2_mx2(.d0(w1[0]),.d1(w1[1]),.s(s[1]),.y(y));

endmodule