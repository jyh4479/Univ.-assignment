module _dff_r(clk, reset_n, d, q); //d flip flop reset asyncronous
	input clk, reset_n, d; //inputs
	output reg q; //ouput and reg
	
	always @ (posedge clk or negedge reset_n)//The condition of clk and reset
	begin
		if(reset_n==0) q<=1'b0; //if reset 0 -> q is 0
		else q<=d; //else q is d
	end

endmodule

