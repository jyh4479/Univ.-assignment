module mx2(d0, d1, s, y); //The module is mx2
	input [31:0] d0, d1; //input
	input s;
	output reg [31:0] y; //output reg
	
	always@(s, d0, d1) //according to s, d0, d1
	begin //start option
		case(s) //case s
			1'b0	:	y = d1; //if s is 0, y is d1
			1'b1	:	y = d0;    //if s is 1, y is d0
			default : y =32'h0; //else, the y is 0
		endcase
	end //end option
endmodule 