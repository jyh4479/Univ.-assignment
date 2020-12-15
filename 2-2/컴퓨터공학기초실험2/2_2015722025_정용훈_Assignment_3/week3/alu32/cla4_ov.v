module cla4_ov(a,b,ci,c3,s,co);  //use cla4 to check overflow
	input [3:0] a,b;
	input ci;
	output [3:0] s;
	output c3,co;
	
	wire c1, c2;
	
	//instance clb4 and fa_v2
	clb4 U0_clb4(.a(a), .b(b), .ci(ci), .c1(c1), .c2(c2), .c3(c3), .co(co));
	fa_v2 U0_fa_v2(.a(a[0]), .b(b[0]), .ci(ci), .s(s[0]));
	fa_v2 U1_fa_v2(.a(a[1]), .b(b[1]), .ci(c1), .s(s[1]));
	fa_v2 U2_fa_v2(.a(a[2]), .b(b[2]), .ci(c2), .s(s[2]));
	fa_v2 U3_fa_v2(.a(a[3]), .b(b[3]), .ci(c3), .s(s[3]));
endmodule
