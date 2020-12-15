`timescale 1ns/100ps //
//using self-checking test bench

module tb_alu4();

	reg [3:0] tb_a, tb_b; //input
	reg [2:0] tb_op; //opcode
	wire [3:0] tb_result; //result
	wire tb_c, tb_n, tb_z, tb_v; //flags
	
	alu4 U0_alu4(.a(tb_a), .b(tb_b), .op(tb_op), .result(tb_result), .c(tb_c), .n(tb_n), .z(tb_z), .v(tb_v)); //4bit alu is worked. 
	
	initial
		begin
		
		tb_a=4'b1011; tb_b=4'b0110; tb_op=3'b000; #10;
		//if any result is not satisfied, error is printed.
		if(tb_result!==4'b1111 || tb_c!=0 || tb_n!=1 || tb_z!=0 || tb_v!=1) $display("000 failed");
		tb_op=3'b001; #10;
		
		if(tb_result!==4'b0000 || tb_c!=0 || tb_n!=1 || tb_z!=0 || tb_v!=1) $display("001 failed");
		tb_op=3'b010; #10;
		
		if(tb_result!==4'b0000 || tb_c!=0 || tb_n!=1 || tb_z!=0 || tb_v!=1) $display("010 failed");
		tb_op=3'b011; #10;
		
		if(tb_result!==4'b1111 || tb_c!=0 || tb_n!=1 || tb_z!=0 || tb_v!=1) $display("011 failed");
		tb_op=3'b100; #10;
		
		if(tb_result!==4'b1111 || tb_c!=0 || tb_n!=1 || tb_z!=0 || tb_v!=1) $display("100 failed");
		tb_op=3'b101; #10;
		
		if(tb_result!==4'b0000 || tb_c!=0 || tb_n!=1 || tb_z!=0 || tb_v!=1) $display("101 failed");
		tb_op=3'b110; #10;
		
		if(tb_result!==4'b1111 || tb_c!=0 || tb_n!=1 || tb_z!=0 || tb_v!=1) $display("110 failed");
		tb_op=3'b111; #10;
		
		if(tb_result!==4'b0001 || tb_c!=0 || tb_n!=1 || tb_z!=0 || tb_v!=1) $display("111 failed");
		
		end
endmodule
