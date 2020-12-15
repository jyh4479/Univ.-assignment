module mux2_8bit(d0, d1, s, y); //Declare module
input [7:0]d0, d1; //8bits input
input s;
output reg [7:0]y; //8bits output

always@(s, d0,d1)
begin
	if (s == 0) //if s is 0, output is d0
		y <= d0;
	else //else, output is d1
		y<= d1;
end
endmodule