module _dff_rs_sync(clk, set_n, reset_n, d, q); //dff reset and set synchronous
	input clk, set_n, reset_n, d;
	output reg q;
	
	always@(posedge clk) //only change when clk endge
	begin
		if(reset_n==0) q<=1'b0; //if reset_n is 0, q is 0
		else if(set_n==0) q<=1'b1; //if set_n is 0, 1 is 1
		else q<=d; //else q is d
	end
	
endmodule
