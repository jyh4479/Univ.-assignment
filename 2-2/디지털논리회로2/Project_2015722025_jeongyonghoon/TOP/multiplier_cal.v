module multiplier_cal(multiplicand,check_radix,count,state,result,next_result); //Declare calculater

   input [31:0] multiplicand; //input
   input [4:0] check_radix;
   input [1:0] state;
   input [31:0] result;
   input [2:0] count;

   output reg [31:0] next_result; //output

   wire [31:0] add1; //addition wires for radix-16
   wire [31:0] add2;
   wire [31:0] add3;
   wire [31:0] add4;
   wire [31:0] add5;
   wire [31:0] add6;
   wire [31:0] add7;
   wire [31:0] add8;

   wire [31:0] sub1; //subtraction wires for radix-16
   wire [31:0] sub2;
   wire [31:0] sub3;
   wire [31:0] sub4;
   wire [31:0] sub5;
   wire [31:0] sub6;
   wire [31:0] sub7;
   wire [31:0] sub8;


   parameter IDLE =2'b00;//Declare paramter of state
   parameter EXEC =2'b01;
   parameter OUT  =2'b10;
   parameter DONE =2'b11;

always@(state or check_radix or result or count or add1 or add2 or add3 or add4 or add5 or add6 or add7 or add8 or sub1 or sub2 or sub3 or sub4 or sub5 or sub6 or sub7 or sub8) begin
//practice function when chnage the value

case(state) //case state

IDLE : begin //when IDLE
   next_result<=32'b0; // reset result
  end



EXEC : begin //State of calculation

if(check_radix==5'b00000||check_radix==5'b11111) begin
   if(count==3'b000) next_result=32'b0;//check count

   next_result=result>>4;//shift
   next_result[31:28]={next_result[27],next_result[27],next_result[27],next_result[27]};//ASR
   end

else if(check_radix==5'b00001||check_radix==5'b00010) begin
   if(count==3'b000) next_result=32'b0;

   next_result=add1>>4;
   next_result[31:28]={next_result[27],next_result[27],next_result[27],next_result[27]};
   end

else if(check_radix==5'b00011||check_radix==5'b00100) begin
   if(count==3'b000) next_result=32'b0;

   next_result=add2>>4;
   next_result[31:28]={next_result[27],next_result[27],next_result[27],next_result[27]};
   end


else if(check_radix==5'b00101||check_radix==5'b00110) begin
   if(count==3'b000) next_result=32'b0;

   next_result=add3>>4;
   next_result[31:28]={next_result[27],next_result[27],next_result[27],next_result[27]};
   end

else if(check_radix==5'b00111||check_radix==5'b01000) begin
   if(count==3'b000) next_result=32'b0;

   next_result=add4>>4;
   next_result[31:28]={next_result[27],next_result[27],next_result[27],next_result[27]};
   end

else if(check_radix==5'b01001||check_radix==5'b01010) begin
   if(count==3'b000) next_result=32'b0;

   next_result=add5>>4;
   next_result[31:28]={next_result[27],next_result[27],next_result[27],next_result[27]};
   end

else if(check_radix==5'b01011||check_radix==5'b01100) begin
   if(count==3'b000) next_result=32'b0;

      next_result=add6>>4;
      next_result[31:28]={next_result[27],next_result[27],next_result[27],next_result[27]};
   end

else if(check_radix==5'b01101||check_radix==5'b01110) begin
   if(count==3'b000) next_result=32'b0;

   next_result=add7>>4;
   next_result[31:28]={next_result[27],next_result[27],next_result[27],next_result[27]};
   end

else if(check_radix==5'b01111) begin
   if(count==3'b000) next_result=32'b0;

   next_result=add8>>4;
   next_result[31:28]={next_result[27],next_result[27],next_result[27],next_result[27]};
   end

else if(check_radix==5'b10000) begin
   if(count==3'b000) next_result=32'b0;

   next_result=sub8>>4;
   next_result[31:28]={next_result[27],next_result[27],next_result[27],next_result[27]};
   end

else if(check_radix==5'b10001||check_radix==5'b10010) begin
   if(count==3'b000) next_result=32'b0;

   next_result=sub7>>4;
   next_result[31:28]={next_result[27],next_result[27],next_result[27],next_result[27]};
   end

else if(check_radix==5'b10011||check_radix==5'b10100) begin
   if(count==3'b000) next_result=32'b0;

   next_result=sub6>>4;
   next_result[31:28]={next_result[27],next_result[27],next_result[27],next_result[27]};
   end

else if(check_radix==5'b10101||check_radix==5'b10110) begin
   if(count==3'b000) next_result=32'b0;

   next_result=sub5>>4;
   next_result[31:28]={next_result[27],next_result[27],next_result[27],next_result[27]};
   end

else if(check_radix==5'b10111||check_radix==5'b11000) begin
   if(count==3'b000) next_result=32'b0;

   next_result=sub4>>4;
   next_result[31:28]={next_result[27],next_result[27],next_result[27],next_result[27]};
   end

else if(check_radix==5'b11001||check_radix==5'b11010) begin
   if(count==3'b000) next_result=32'b0;

   next_result=sub3>>4;
   next_result[31:28]={next_result[27],next_result[27],next_result[27],next_result[27]};
   end

else if(check_radix==5'b11011||check_radix==5'b11100) begin
   if(count==3'b000) next_result=32'b0;

   next_result=sub2>>4;
   next_result[31:28]={next_result[27],next_result[27],next_result[27],next_result[27]};
   end

else if(check_radix==5'b11101||check_radix==5'b11110) begin
   if(count==3'b000) next_result=32'b0;

   next_result=sub1>>4;
   next_result[31:28]={next_result[27],next_result[27],next_result[27],next_result[27]};
   end

else begin
   next_result=32'bx;
   end
end



OUT :begin
  next_result<= result; //Out state just show result
end



DONE :begin // DONE
  next_result<= result; // state nochange
end



default : begin //Default
  next_result<=32'bx;
end
endcase
end


cla_multi U0(.a(result),.b(multiplicand[15:0]),.ci(1'b0),.s(add1),.co());//for add each value
cla_multi U1(.a(add1),.b(multiplicand[15:0]),.ci(1'b0),.s(add2),.co());
cla_multi U2(.a(add2),.b(multiplicand[15:0]),.ci(1'b0),.s(add3),.co());
cla_multi U3(.a(add3),.b(multiplicand[15:0]),.ci(1'b0),.s(add4),.co());
cla_multi U4(.a(add4),.b(multiplicand[15:0]),.ci(1'b0),.s(add5),.co());
cla_multi U5(.a(add5),.b(multiplicand[15:0]),.ci(1'b0),.s(add6),.co());
cla_multi U6(.a(add6),.b(multiplicand[15:0]),.ci(1'b0),.s(add7),.co());
cla_multi U7(.a(add7),.b(multiplicand[15:0]),.ci(1'b0),.s(add8),.co());

cla_multi U10(.a(result),.b(~multiplicand[15:0]),.ci(1'b1),.s(sub1),.co());//for subtraction each value
cla_multi U11(.a(sub1),.b(~multiplicand[15:0]),.ci(1'b1),.s(sub2),.co());
cla_multi U12(.a(sub2),.b(~multiplicand[15:0]),.ci(1'b1),.s(sub3),.co());
cla_multi U13(.a(sub3),.b(~multiplicand[15:0]),.ci(1'b1),.s(sub4),.co());
cla_multi U14(.a(sub4),.b(~multiplicand[15:0]),.ci(1'b1),.s(sub5),.co());
cla_multi U15(.a(sub5),.b(~multiplicand[15:0]),.ci(1'b1),.s(sub6),.co());
cla_multi U16(.a(sub6),.b(~multiplicand[15:0]),.ci(1'b1),.s(sub7),.co());
cla_multi U17(.a(sub7),.b(~multiplicand[15:0]),.ci(1'b1),.s(sub8),.co());

endmodule


module cla_multi(a,b,ci,s,co); //for calculating 16bits
   input [15:0] b;//inputs
   input [31:0] a;
   input ci; 

   output [31:0] s;//outputs
   output co; 

   wire c1,c2,c3;//wires

   assign s[15:0] = a[15:0]; //Declare result of sum

cla4 U0_cla4(.a(a[19:16]),.b(b[3:0]),.ci(ci),.s(s[19:16]),.co(c1));//instance cla4
cla4 U1_cla4(.a(a[23:20]),.b(b[7:4]),.ci(c1),.s(s[23:20]),.co(c2)); 
cla4 U2_cla4(.a(a[27:24]),.b(b[11:8]),.ci(c2),.s(s[27:24]),.co(c3));
cla4 U3_cla4(.a(a[31:28]),.b(b[15:12]),.ci(c3),.s(s[31:28]),.co(co)); 

endmodule

