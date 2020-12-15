module adder_cal(din,state,count,result,next_result); //Declare module of adder calculation

   input [1:0] state,count; //inputs
   input [31:0] result,din;

   output reg [31:0] next_result; //output reg

   wire [31:0] add; //wire

   parameter IDLE =2'b00;//Declare state parameter
   parameter EXEC =2'b01;
   parameter OUT  =2'b10;
   parameter DONE =2'b11;

   parameter zero =2'b00;//Declare count parameter
   parameter one =2'b01;
   parameter two =2'b10;

always@(state or count or result or din or add) //practice function when change variable
begin
case(state) //check state

IDLE : next_result<=32'b0;//Declare IDLE


EXEC : begin
case(count) //check count
   zero : next_result<=result;
   one : next_result<=din;
   two : next_result<=add;

     default : next_result<=32'bx;
   endcase
end


OUT : next_result<= result; //Declare OUT state



DONE : next_result<= result; //Declare DONE state

default : next_result<=32'bx; //default
endcase 
end

cla_adder U0(result,din,1'b0,add); //Declare cla for add two inputs
endmodule


module cla_adder(a,b,ci,s,co);//Declare module of 32bits cla

   input [31:0] a,b;//inputs
   input ci;

   output [31:0] s;//outputs
   output co;

   wire c1,c2,c3,c4,c5,c6,c7;//wires


cla4 U0(.a(a[3:0]),.b(b[3:0]),.ci(ci),.s(s[3:0]),.co(c1)); //Declare 4bits cla for 32bits
cla4 U1(.a(a[7:4]),.b(b[7:4]),.ci(c1),.s(s[7:4]),.co(c2));
cla4 U2(.a(a[11:8]),.b(b[11:8]),.ci(c2),.s(s[11:8]),.co(c3));
cla4 U3(.a(a[15:12]),.b(b[15:12]),.ci(c3),.s(s[15:12]),.co(c4));
cla4 U4(.a(a[19:16]),.b(b[19:16]),.ci(c4),.s(s[19:16]),.co(c5));
cla4 U5(.a(a[23:20]),.b(b[23:20]),.ci(c5),.s(s[23:20]),.co(c6));
cla4 U6(.a(a[27:24]),.b(b[27:24]),.ci(c6),.s(s[27:24]),.co(c7));
cla4 U7(.a(a[31:28]),.b(b[31:28]),.ci(c7),.s(s[31:28]),.co(co));

endmodule

module cla4(a,b,ci,s,co);//Declare module of cla4

   input [3:0]a,b;//inputs
   input ci; 

   output [3:0]s;//outputs
   output co;

   wire c1,c2,c3;//wires


clb4 U0_clb4(.a(a),.b(b),.ci(ci),.c1(c1),.c2(c2),.c3(c3),.co(co));//Declare cla block

fa_v2 U0_fa_v2(.a(a[0]),.b(b[0]),.ci(ci),.s(s[0]));//Declare full adder version 2
fa_v2 U1_fa_v2(.a(a[1]),.b(b[1]),.ci(c1),.s(s[1])); 
fa_v2 U2_fa_v2(.a(a[2]),.b(b[2]),.ci(c2),.s(s[2])); 
fa_v2 U3_fa_v2(.a(a[3]),.b(b[3]),.ci(c3),.s(s[3])); 

endmodule

