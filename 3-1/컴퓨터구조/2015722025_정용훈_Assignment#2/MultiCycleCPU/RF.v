`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    13:26:06 03/08/2019 
// Design Name: 
// Module Name:    RF 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module RF(i_clk,i_rst_n,i_Read_reg1,i_Read_reg2,i_Write_reg,i_Write_data,
          RegWrite, o_Read_data1, o_Read_data2);
  input i_clk,i_rst_n,RegWrite;                     //input 1bit clock, reset, write signal
  input [4:0] i_Read_reg1, i_Read_reg2, i_Write_reg;//input 5bit 3 registers
  input [31:0] i_Write_data;                        //input 32bit data
  output [31:0] o_Read_data1, o_Read_data2;         //output 32bit datas
  
  //32 registers and next_registers
  reg [31:0] register1, next_register1;
  reg [31:0] register2, next_register2;
  reg [31:0] register3, next_register3;
  reg [31:0] register4, next_register4;
  reg [31:0] register5, next_register5;
  reg [31:0] register6, next_register6;
  reg [31:0] register7, next_register7;
  reg [31:0] register8, next_register8;
  reg [31:0] register9, next_register9;
  reg [31:0] register10, next_register10;
  reg [31:0] register11, next_register11;
  reg [31:0] register12, next_register12;
  reg [31:0] register13, next_register13;
  reg [31:0] register14, next_register14;
  reg [31:0] register15, next_register15;
  reg [31:0] register16, next_register16;
  reg [31:0] register17, next_register17;
  reg [31:0] register18, next_register18;
  reg [31:0] register19, next_register19;
  reg [31:0] register20, next_register20;
  reg [31:0] register21, next_register21;
  reg [31:0] register22, next_register22;
  reg [31:0] register23, next_register23;
  reg [31:0] register24, next_register24;
  reg [31:0] register25, next_register25;
  reg [31:0] register26, next_register26;
  reg [31:0] register27, next_register27;
  reg [31:0] register28, next_register28;
  reg [31:0] register29, next_register29;
  reg [31:0] register30, next_register30;
  reg [31:0] register31, next_register31;
  reg [31:0] register32, next_register32;

  //sequence logic. positive edge clock, negative edge reset
  //if reset : initialize
  //else : register <= next_register
  always @(posedge i_clk or negedge i_rst_n)begin
    if(i_rst_n==1'b0) begin 
      register1<=32'b0;
      register2<=32'b0;
      register3<=32'b0;
      register4<=32'b0;
      register5<=32'b0;
      register6<=32'b0;
      register7<=32'b0;
      register8<=32'b0;
      register9<=32'b0;
      register10<=32'b0;
      register11<=32'b0;
      register12<=32'b0;
      register13<=32'b0;
      register14<=32'b0;
      register15<=32'b0;
      register16<=32'b0;
      register17<=32'b0;
      register18<=32'b0;
      register19<=32'b0;
      register20<=32'b0;
      register21<=32'b0;
      register22<=32'b0;
      register23<=32'b0;
      register24<=32'b0;
      register25<=32'b0;
      register26<=32'b0;
      register27<=32'b0;
      register28<=32'b0;
      register29<=32'b0;
      register30<=32'b0;
      register31<=32'b0;
      register32<=32'b0;
    end
    else  begin
      register1<=0;
      register2<=next_register2;
      register3<=next_register3;
      register4<=next_register4;
      register5<=next_register5;
      register6<=next_register6;
      register7<=next_register7;
      register8<=next_register8;
      register9<=next_register9;
      register10<=next_register10;
      register11<=next_register11;
      register12<=next_register12;
      register13<=next_register13;
      register14<=next_register14;
      register15<=next_register15;
      register16<=next_register16;
      register17<=next_register17;
      register18<=next_register18;
      register19<=next_register19;
      register20<=next_register20;
      register21<=next_register21;
      register22<=next_register22;
      register23<=next_register23;
      register24<=next_register24;
      register25<=next_register25;
      register26<=next_register26;
      register27<=next_register27;
      register28<=next_register28;
      register29<=next_register29;
      register30<=next_register30;
      register31<=next_register31;
      register32<=next_register32;
    end   
end

//combinatinal logic : wirte
//if equal, write write_data to one next_register
//but not equal, write previous value
//This code has 32 always sentence
always@(RegWrite or i_Write_reg or i_Write_data or register1) begin
  if(RegWrite == 1'b1 && i_Write_reg==5'b00000) 
    next_register1 <= 0;
else
  next_register1 <= 0;
end

always@(RegWrite or i_Write_reg or i_Write_data or register2) begin
  if(RegWrite == 1'b1 && i_Write_reg==5'b00001) 
    next_register2 <= i_Write_data;
else
  next_register2 <= register2;
end

always@(RegWrite or i_Write_reg or i_Write_data or register3) begin
  if(RegWrite == 1'b1 && i_Write_reg==5'b00010) 
    next_register3 <= i_Write_data;
else
  next_register3 <= register3;
end

always@(RegWrite or i_Write_reg or i_Write_data or register4) begin
  if(RegWrite == 1'b1 && i_Write_reg==5'b00011) 
    next_register4 <= i_Write_data;
else
  next_register4 <= register4;
end

always@(RegWrite or i_Write_reg or i_Write_data or register5) begin
  if(RegWrite == 1'b1 && i_Write_reg==5'b00100) 
    next_register5 <= i_Write_data;
else
  next_register5 <= register5;
end

always@(RegWrite or i_Write_reg or i_Write_data or register6) begin
  if(RegWrite == 1'b1 && i_Write_reg==5'b00101) 
    next_register6 <= i_Write_data;
else
  next_register6 <= register6;
end

always@(RegWrite or i_Write_reg or i_Write_data or register7) begin
  if(RegWrite == 1'b1 && i_Write_reg==5'b00110) 
    next_register7 <= i_Write_data;
else
  next_register7 <= register7;
end

always@(RegWrite or i_Write_reg or i_Write_data or register8) begin
  if(RegWrite == 1'b1 && i_Write_reg==5'b00111) 
    next_register8 <= i_Write_data;
else
  next_register8 <= register8;
end

always@(RegWrite or i_Write_reg or i_Write_data or register9) begin
  if(RegWrite == 1'b1 && i_Write_reg==5'b01000) 
    next_register9 <= i_Write_data;
else
  next_register9 <= register9;
end

always@(RegWrite or i_Write_reg or i_Write_data or register10) begin
  if(RegWrite == 1'b1 && i_Write_reg==5'b01001) 
    next_register10 <= i_Write_data;
else
  next_register10 <= register10;
end

always@(RegWrite or i_Write_reg or i_Write_data or register11) begin
  if(RegWrite == 1'b1 && i_Write_reg==5'b01010) 
    next_register11 <= i_Write_data;
else
  next_register11 <= register11;
end

always@(RegWrite or i_Write_reg or i_Write_data or register12) begin
  if(RegWrite == 1'b1 && i_Write_reg==5'b01011) 
    next_register12 <= i_Write_data;
else
  next_register12 <= register12;
end

always@(RegWrite or i_Write_reg or i_Write_data or register13) begin
  if(RegWrite == 1'b1 && i_Write_reg==5'b01100) 
    next_register13 <= i_Write_data;
else
  next_register13 <= register13;
end

always@(RegWrite or i_Write_reg or i_Write_data or register14) begin
  if(RegWrite == 1'b1 && i_Write_reg==5'b01101) 
    next_register14 <= i_Write_data;
else
  next_register14 <= register14;
end

always@(RegWrite or i_Write_reg or i_Write_data or register15) begin
  if(RegWrite == 1'b1 && i_Write_reg==5'b01110) 
    next_register15 <= i_Write_data;
else
  next_register15 <= register15;
end

always@(RegWrite or i_Write_reg or i_Write_data or register16) begin
  if(RegWrite == 1'b1 && i_Write_reg==5'b01111) 
    next_register16 <= i_Write_data;
else
  next_register16 <= register16;
end

always@(RegWrite or i_Write_reg or i_Write_data or register17) begin
  if(RegWrite == 1'b1 && i_Write_reg==5'b10000) 
    next_register17 <= i_Write_data;
else
  next_register17 <= register17;
end

always@(RegWrite or i_Write_reg or i_Write_data or register18) begin
  if(RegWrite == 1'b1 && i_Write_reg==5'b10001) 
    next_register18 <= i_Write_data;
else
  next_register18 <= register18;
end

always@(RegWrite or i_Write_reg or i_Write_data or register19) begin
  if(RegWrite == 1'b1 && i_Write_reg==5'b10010) 
    next_register19 <= i_Write_data;
else
  next_register19 <= register19;
end

always@(RegWrite or i_Write_reg or i_Write_data or register20) begin
  if(RegWrite == 1'b1 && i_Write_reg==5'b10011) 
    next_register20 <= i_Write_data;
else
  next_register20 <= register20;
end

always@(RegWrite or i_Write_reg or i_Write_data or register21) begin
  if(RegWrite == 1'b1 && i_Write_reg==5'b10100) 
    next_register21 <= i_Write_data;
else
  next_register21 <= register21;
end

always@(RegWrite or i_Write_reg or i_Write_data or register22) begin
  if(RegWrite == 1'b1 && i_Write_reg==5'b10101) 
    next_register22 <= i_Write_data;
else
  next_register22 <= register22;
end

always@(RegWrite or i_Write_reg or i_Write_data or register23) begin
  if(RegWrite == 1'b1 && i_Write_reg==5'b10110) 
    next_register23 <= i_Write_data;
else
  next_register23 <= register23;
end

always@(RegWrite or i_Write_reg or i_Write_data or register24) begin
  if(RegWrite == 1'b1 && i_Write_reg==5'b10111) 
    next_register24 <= i_Write_data;
else
  next_register24 <= register24;
end

always@(RegWrite or i_Write_reg or i_Write_data or register25) begin
  if(RegWrite == 1'b1 && i_Write_reg==5'b11000) 
    next_register25 <= i_Write_data;
else
  next_register25 <= register25;
end

always@(RegWrite or i_Write_reg or i_Write_data or register26) begin
  if(RegWrite == 1'b1 && i_Write_reg==5'b11001) 
    next_register26 <= i_Write_data;
else
  next_register26 <= register26;
end

always@(RegWrite or i_Write_reg or i_Write_data or register27) begin
  if(RegWrite == 1'b1 && i_Write_reg==5'b11010) 
    next_register27 <= i_Write_data;
else
  next_register27 <= register27;
end

always@(RegWrite or i_Write_reg or i_Write_data or register28) begin
  if(RegWrite == 1'b1 && i_Write_reg==5'b11011) 
    next_register28 <= i_Write_data;
else
  next_register28 <= register28;
end

always@(RegWrite or i_Write_reg or i_Write_data or register29) begin
  if(RegWrite == 1'b1 && i_Write_reg==5'b11100) 
    next_register29 <= i_Write_data;
else
  next_register29 <= register29;
end

always@(RegWrite or i_Write_reg or i_Write_data or register30) begin
  if(RegWrite == 1'b1 && i_Write_reg==5'b11101) 
    next_register30 <= i_Write_data;
else
  next_register30 <= register30;
end

always@(RegWrite or i_Write_reg or i_Write_data or register31) begin
  if(RegWrite == 1'b1 && i_Write_reg==5'b11110) 
    next_register31 <= i_Write_data;
else
  next_register31 <= register31;
end

always@(RegWrite or i_Write_reg or i_Write_data or register32) begin
  if(RegWrite == 1'b1 && i_Write_reg==5'b11111) 
    next_register32 <= i_Write_data;
else
  next_register32 <= register32;
end

//combinational logic: read(output)
//output value that register has
//we use condition operation. because always sentence has long code.
//default : 32'h0000_0000
assign o_Read_data1 = (i_Read_reg1 == 5'b00000) ? register1 : ((i_Read_reg1 == 5'b00001) ? register2 : ((i_Read_reg1 == 5'b00010) ? register3 : ((i_Read_reg1 == 5'b00011) ? register4 : 
                      ((i_Read_reg1 == 5'b00100) ? register5 : ((i_Read_reg1 == 5'b00101) ? register6 : ((i_Read_reg1 == 5'b00110) ? register7 : ((i_Read_reg1 == 5'b00111) ? register8 :
                      ((i_Read_reg1 == 5'b01000) ? register9 : ((i_Read_reg1 == 5'b01001) ? register10 : ((i_Read_reg1 == 5'b01010) ? register11 : ((i_Read_reg1 == 5'b01011) ? register12 :
                      ((i_Read_reg1 == 5'b01100) ? register13 : ((i_Read_reg1 == 5'b01101) ? register14 : ((i_Read_reg1 == 5'b01110) ? register15 : ((i_Read_reg1 == 5'b01111) ? register16 :
                      ((i_Read_reg1 == 5'b10000) ? register17 : ((i_Read_reg1 == 5'b10001) ? register18 : ((i_Read_reg1 == 5'b10010) ? register19 : ((i_Read_reg1 == 5'b10011) ? register20 :
                      ((i_Read_reg1 == 5'b10100) ? register21 : ((i_Read_reg1 == 5'b10101) ? register22 : ((i_Read_reg1 == 5'b10110) ? register23 : ((i_Read_reg1 == 5'b10111) ? register24 :
                      ((i_Read_reg1 == 5'b11000) ? register25 : ((i_Read_reg1 == 5'b11001) ? register26 : ((i_Read_reg1 == 5'b11010) ? register27 : ((i_Read_reg1 == 5'b11011) ? register28 :
                      ((i_Read_reg1 == 5'b11100) ? register29 : ((i_Read_reg1 == 5'b11101) ? register30 : ((i_Read_reg1 == 5'b11110) ? register31 : 
                      ((i_Read_reg1 == 5'b11111) ? register32 : 32'h00000000)))))))))))))))))))))))))))))));
  
assign o_Read_data2 = (i_Read_reg2 == 5'b00000) ? register1 : ((i_Read_reg2 == 5'b00001) ? register2 : ((i_Read_reg2 == 5'b00010) ? register3 : ((i_Read_reg2 == 5'b00011) ? register4 : 
                      ((i_Read_reg2 == 5'b00100) ? register5 : ((i_Read_reg2 == 5'b00101) ? register6 : ((i_Read_reg2 == 5'b00110) ? register7 : ((i_Read_reg2 == 5'b00111) ? register8 :
                      ((i_Read_reg2 == 5'b01000) ? register9 : ((i_Read_reg2 == 5'b01001) ? register10 : ((i_Read_reg2 == 5'b01010) ? register11 : ((i_Read_reg2 == 5'b01011) ? register12 :
                      ((i_Read_reg2 == 5'b01100) ? register13 : ((i_Read_reg2 == 5'b01101) ? register14 : ((i_Read_reg2 == 5'b01110) ? register15 : ((i_Read_reg2 == 5'b01111) ? register16 :
                      ((i_Read_reg2 == 5'b10000) ? register17 : ((i_Read_reg2 == 5'b10001) ? register18 : ((i_Read_reg2 == 5'b10010) ? register19 : ((i_Read_reg2 == 5'b10011) ? register20 :
                      ((i_Read_reg2 == 5'b10100) ? register21 : ((i_Read_reg2 == 5'b10101) ? register22 : ((i_Read_reg2 == 5'b10110) ? register23 : ((i_Read_reg2 == 5'b10111) ? register24 :
                      ((i_Read_reg2 == 5'b11000) ? register25 : ((i_Read_reg2 == 5'b11001) ? register26 : ((i_Read_reg2 == 5'b11010) ? register27 : ((i_Read_reg2 == 5'b11011) ? register28 :
                      ((i_Read_reg2 == 5'b11100) ? register29 : ((i_Read_reg2 == 5'b11101) ? register30 : ((i_Read_reg2 == 5'b11110) ? register31 : 
                      ((i_Read_reg2 == 5'b11111) ? register32 : 32'h00000000)))))))))))))))))))))))))))))));                      
endmodule
