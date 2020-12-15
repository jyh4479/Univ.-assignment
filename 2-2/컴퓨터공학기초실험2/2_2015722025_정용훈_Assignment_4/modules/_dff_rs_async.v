module _dff_rs_async(clk, set_n, reset_n, d, q); //d flip flop reset and set asyncronous
	input clk, set_n, reset_n, d;
	output reg q;
	
	always @ (posedge clk or negedge set_n or negedge reset_n) //condition
	begin
		if(reset_n==0) q<=1'b0; //if reset_n is 0, q is 0
		else if(set_n==0) q<=1'b1; //else if set_n is 0 qis 1
		else q<=d; //else q is d
	end
	
endmodule