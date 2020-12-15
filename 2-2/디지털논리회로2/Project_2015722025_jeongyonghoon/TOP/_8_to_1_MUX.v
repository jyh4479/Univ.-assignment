module _8_to_1_MUX(a,b,c,d,e,f,g,h,sel,d_out); // 8to1MUX module
input [31:0] a,b,c,d,e,f,g,h; // 32bit input variables
input [2:0] sel; // 3bit input variable
output reg [31:0] d_out; // 32bit output reg variable

always@(sel or a or b or c or d or e or f or g or h) // change input
begin
case(sel) // condition
3'b000 : d_out = a; // select d_out
3'b001 : d_out = b;
3'b010 : d_out = c;
3'b011 : d_out = d;
3'b100 : d_out = e;
3'b101 : d_out = f;
3'b110 : d_out = g;
3'b111 : d_out = h;
default : d_out = 32'hx; // default case
endcase
end
endmodule
