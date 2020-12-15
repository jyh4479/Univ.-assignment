module cal_flags32(op, result, co_add, co_prev_add, co_sub, co_prev_sub, c, n, z, v);
	input [2:0] op; //opcode
	input [31:0] result;
	input co_add, co_prev_add, co_sub, co_prev_sub;
	output c, n, z, v; //output for flag
	
	assign c= (op[2:1]!=2'b11)? 1'b0: ((op[0]==0)? co_add : co_sub); //Carry
	assign n= result[31]; //Negative
	assign z= (result==4'h00000000)? 1'b1:1'b0; //Zero
	assign v= (op[2:1]!=2'b11)? 0 : ((op[0]==0)? (co_add^co_prev_add) : (co_sub^co_prev_sub)); //Overflow
	
endmodule