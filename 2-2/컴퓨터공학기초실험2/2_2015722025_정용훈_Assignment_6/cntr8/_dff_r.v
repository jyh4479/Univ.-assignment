module _dff_r(clk, reset_n, d, q); //resettable dff
	input clk, reset_n, d; //input
	output reg q; //output, reg
	
	always@(posedge clk or negedge reset_n)
	begin
		if(reset_n==0) q<=1'b0; //if reset_n is 0, q is 0
		else q<=d; //else q is d
	end
endmodule