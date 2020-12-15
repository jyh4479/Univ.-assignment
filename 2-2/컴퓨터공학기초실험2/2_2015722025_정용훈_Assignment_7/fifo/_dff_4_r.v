module _dff_4_r(clk, reset_n, d, q);
	input clk, reset_n; //input
	input [3:0]d;
	output reg[3:0]q; //output reg
	
always@(posedge clk or negedge reset_n) begin//always
		if(~reset_n) q<= 4'b0000;//when reset is 0
		else q<= d;//else, q is d
	end
endmodule
