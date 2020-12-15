module _dff_r_en(clk, reset_n, en, d, q);
	input clk, reset_n, en, d; //input
	output reg q; //output, reg
	
	always @ (posedge clk or negedge reset_n) begin
		if(~reset_n) q<=1'b0; //if reset is 0, output is 0
		else if(en) q<=d; //Declare endable
		else q<=q;
	end
endmodule
