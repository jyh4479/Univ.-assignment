module mux2_32bit(d0, d1, s, y); //Delcare module
input [31:0]d0, d1; //32bits input
input s;
output reg [31:0]y; //32bits output

always@(s, d0,d1)
begin
	if (s == 0) //if s is 0, output is d0
		y <= d0;
	else //else, output is d1
		y<= d1;
end
endmodule