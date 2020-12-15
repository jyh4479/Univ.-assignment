module cal_flags4(op, result, co_add, c3_add, co_sub, c3_sub, c, n, z, v); //flag c n z v
	input [2:0] op;
	input [3:0] result;
	input co_add, c3_add, co_sub, c3_sub;
	output c,n,z,v;
	
	assign c= (op[2:1]!==2'b11)? 0 : ((op[0]===0)? co_add : co_sub); //carry
	assign n= result[3]; //negative
	assign z= (result===2'b0000)? 1 : 0; //zero
	assign v= (op[2:1]!=2'b11)? 0 : ((op[0]===0)? (co_add^c3_add) : (co_sub^c3_sub)); //overflow
	
endmodule
