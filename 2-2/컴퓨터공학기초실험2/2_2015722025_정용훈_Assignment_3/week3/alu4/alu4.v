module alu4(a, b, op, result, c, n, z, v); //alu4 
	input [3:0] a,b;
	input [2:0] op;
	output [3:0] result;
	output c, n, z, v;
	
	wire [3:0] w_not_a, w_not_b, w_and, w_or, w_xor, w_xnor, w_add, w_sub;
	wire c3_add, co_add, c3_sub, co_sub;
	
	//instance inverter, and, or, xor, xnor, cla4, mux and cal_flags
	_inv_4bits U0_inv(.a(a), .y(w_not_a));
	_inv_4bits U1_inv(.a(b), .y(w_not_b));
	_and2_4bits U2_and(.a(a), .b(b),.y(w_and));
	_or2_4bits U3_or(.a(a), .b(b), .y(w_or));
	_xor2_4bits U4_xor(.a(a), .b(b), .y(w_xor));
	_xnor2_4bits U5_xnor(.a(a), .b(b), .y(w_xnor));
	//a,b,ci,c3,s,co
	cla4_ov U6_cla4_ov (.a(a),.b(b),.ci(1'b0),
							.c3(c3_add),.s(w_add),
							.co(co_add));
									
	cla4_ov U7_cla4_ov (.a(a), .b(w_not_b), .ci(1'b1),
							.c3(c3_sub), .s(w_sub),
							.co(co_sub));
	//a,b,c,d,e,f,g,h,s2,s1,s0,y
	mx8_4bits U8_mx(.a(w_not_a),.b(w_not_b),
						.c(w_and),.d(w_or),.e(w_xor),
						.f(w_xnor),.g(w_add),.h(w_sub),
						.s2(op[2]),.s1(op[1]),.s0(op[0]),
						.y(result));
	
	cal_flags4 U9_cal_flags(.op(op), .result(result),
								.co_add(co_add), .c3_add(c3_add),
								.co_sub(co_sub), .c3_sub(c3_sub),
								.c(c), .n(n), .z(z), .v(v));
	
	
endmodule
