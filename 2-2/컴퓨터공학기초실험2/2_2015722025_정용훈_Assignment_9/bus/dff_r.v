module dff_r(clk, reset_n, d, q); //D-flip-flop
input clk, reset_n; //input
input [1:0]d;
output reg [1:0]q; //output reg

always@(posedge clk or negedge reset_n) //when change clk and reset_n
begin
	if(reset_n == 0) q<= 2'b00; //if reset_n is 0, q is 0
	else 					q <= d; //else q is d
end
endmodule