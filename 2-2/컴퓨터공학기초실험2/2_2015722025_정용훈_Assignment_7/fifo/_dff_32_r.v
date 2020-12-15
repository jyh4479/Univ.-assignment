module _dff_32_r(clk, reset_n, d, q);
	input clk, reset_n; //input
	input [31:0]d;
	output reg[31:0]q; //output reg
	
always@(posedge clk or negedge reset_n) begin//always 
		if(~reset_n) q<= 32'h00000000;//when reset is 0
		else q<= d;//else, q is d
	end
endmodule
