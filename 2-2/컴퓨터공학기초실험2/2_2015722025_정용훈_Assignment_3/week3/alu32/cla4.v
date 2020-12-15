module cla4(a, b, ci, s, co); //making cla by instancing clb and fa_v2
	input [3:0] a, b;
	input ci;
	output [3:0] s;
	output co;
	
	wire wc1, wc2, wc3;
	
	clb4 U0_clb4(.a(a), .b(b), .ci(ci), .c1(wc1), .c2(wc2), .c3(wc3), .co(co));
	fa_v2 U0_fa_v2(.a(a[0]), .b(b[0]), .ci(ci), .s(s[0]));
	fa_v2 U1_fa_v2(.a(a[1]), .b(b[1]), .ci(wc1), .s(s[1]));
	fa_v2 U2_fa_v2(.a(a[2]), .b(b[2]), .ci(wc2), .s(s[2]));
	fa_v2 U3_fa_v2(.a(a[3]), .b(b[3]), .ci(wc3), .s(s[3]));
endmodule
