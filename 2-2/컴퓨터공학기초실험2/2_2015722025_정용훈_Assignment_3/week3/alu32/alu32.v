module alu32(a, b, op, result, c, n, z, v);
	input [31:0] a, b;
	input [2:0] op;
	output [31:0] result;
	output c, n, z, v;
	
	wire [31:0] w_not_a, w_not_b, w_and, w_or, w_xor, w_xnor, w_add, w_sub;
	wire co_prev_add, co_add, co_prev_sub, co_sub;
	
	//instance inverter and, or, xor, xnor, mux, cla32 and cal_falgs 
	_inv_32bits U0_inv_32bits(.a(a), .y(w_not_a));
	_inv_32bits U1_inv_32bits(.a(b), .y(w_not_b));
	_and2_32bits U0_and2_32bits(.a(a), .b(b), .y(w_and));
	_or2_32bits U0_or2_32bits(.a(a), .b(b), .y(w_or));
	_xor2_32bits U0_xor2_32bits(.a(a), .b(b), .y(w_xor));
	_xnor2_32bits U0_xnor2_32bits(.a(a), .b(b), .y(w_xnor));
	//a,b,ci,s,co_prev,co
	cla32_ov U0_cla32_ov(.a(a), .b(b), .ci(0),
								.s(w_add), .co_prev(co_prev_add),
								.co(co_add));
	cla32_ov U1_cla32_ov(.a(a), .b(w_not_b), .ci(1),
								.s(w_sub), .co_prev(co_prev_sub),
								.co(co_sub));
	
	//a,b,c,d,e,f,g,h,s2,s1,s0,y
	mx8_32bits U0_mx8_32bits(.a(w_not_a), .b(w_not_b), .c(w_and),
									.d(w_or), .e(w_xor), .f(w_xnor),
									.g(w_add), .h(w_sub),
									.s2(op[2]), .s1(op[1]), .s0(op[0]),
									.y(result));
	//op, result, co_add, co_prev_add, co_sub, co_prev_sub, c, n, z, v								
	cal_flags32 U0_cal_flag32(.op(op), .result(result),
									.co_add(co_add), .co_prev_add(co_prev_add),
									.co_sub(co_sub), .co_prev_sub(co_prev_sub),
									.c(c), .n(n), .z(z), .v(v));
									
endmodule

								