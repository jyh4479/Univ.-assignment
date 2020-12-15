module mux3_32bit(d0, d1, s, y); //Declare moudle
input [31:0]d0, d1; //32bits inputs
input [1:0]s;
output reg [31:0]y; //32bits outputs

always@(s,d0,d1)
begin
	if (s == 2'b00) //if s is 00, output is 0
		y <= 32'h00;
	else if(s == 2'b10) //else if s is 10, output is d0
		y<= d0;
	else if (s == 2'b01) //else if s is 01, output is d1
		y <= d1;
	else ;
end
endmodule