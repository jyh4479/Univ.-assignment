module mux2(d0,d1,sel,dout); //module of mux2
   input d0,d1; //inputs
   input [1:0] sel;
   output reg dout; //output reg

always@(d0,d1,sel) //Run function according to variable
begin
  case(sel) //case
   2'b10: dout=d0; //dout decision
   2'b01: dout=d1;

   default: dout=1'bx; //defalut
   endcase
  end
endmodule
//////////////////////////////////////////////

module mux2_8bit(d0,d1,sel,dout); //module of 8bits mux2
   input [7:0]d0,d1; //inputs
   input [1:0]sel;
   output reg [7:0] dout; //output reg

always@(d0,d1,sel) //Run function according to variable
begin
  case(sel) //case
   2'b10: dout=d0; //dout decision
   2'b01: dout=d1;

   default: dout=8'h0; //defalut
   endcase
  end
endmodule
//////////////////////////////////////////////

module mux2_32bit(d0,d1,sel,dout); //module of 32bits mux2
   input [31:0] d0,d1; //inputs
   input [1:0] sel;
   output reg [31:0] dout; //output reg

always@(d0,d1,sel) //Run function according to variable
begin
   case(sel) //case
   2'b10: dout=d0; //dout decision
   2'b01: dout=d1;

   default: dout=32'h0; //defalut
   endcase
  end
endmodule
//////////////////////////////////////////////

module mux5_32bit(d0,d1,d2,d3,d4,sel,dout); //module of 32bits mux5
   input [31:0] d0,d1,d2,d3,d4; //inputs
   input [3:0] sel;
   output reg [31:0] dout; //output reg

always@(d0,d1,d2,d3,d4,sel) //Run function according to variable
begin
   case(sel) //case
   4'b1000: dout=d0; //dout decision
   4'b0100: dout=d1;
   4'b0010: dout=d2;
   4'b0001: dout=d3;

   default: dout=d4; //defalut
   endcase
  end
endmodule
//////////////////////////////////////////////

module mx2(a,y,en); //Declare mux

   input [31:0] a; //inputs
   input en;

   output reg [31:0] y; //output reg

always@(a or en) //practice function when a, en change
begin
   if(en==1'b0) y=32'h00000000;//check enable signal

   else y=a; //out data
end

endmodule

//End of mux
