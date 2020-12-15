module _dff_3_r(clk, reset_n, d, q);
	input clk, reset_n;
	input [2:0]d;//3bit flip-flop 
	output reg[2:0]q;//output q 
	
always@(posedge clk or negedge reset_n) begin//always
		if(~reset_n) q<= 3'b000;//when the reset is 0
		else q<= d;//else, q is d
	end
endmodule
