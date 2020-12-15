module mux2(d0, d1, s, y); //Declare mux2
input d0, d1; //input
input s;
output reg y; //out put

always@(s,d0,d1)
begin
	if (s == 0) //if s is 0, output is d0
		y <= d0;
	else //else, output is d1
		y<= d1; 
end
endmodule