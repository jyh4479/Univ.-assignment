module RF(clk,clear,wAddr,wData,we,rAddr,rData); //module of Register file

   input clk, we,clear; //inputs
   input [2:0] wAddr,rAddr;
   input [31:0] wData;

   output [31:0] rData;//output

   wire [7:0] grant_signal;//wires
   wire [31:0] reg_data[7:0];

write_operation U0_write_operation(.Addr(wAddr),.we(we),.grant_signal(grant_signal)); //Write operation logic

register32_8 U0_register32_8(.clk(clk),.clear(clear),.en(grant_signal),.d_in(wData),.d_out0(reg_data[0]),.d_out1(reg_data[1]),.d_out2(reg_data[2]),.d_out3(reg_data[3]),.d_out4(reg_data[4]),.d_out5(reg_data[5]),.d_out6(reg_data[6]),.d_out7(reg_data[7])); //32 bits Register

read_operation U0_read_operation(.Addr(rAddr),.Data(rData),.reg_data0(reg_data[0][31:0]),.reg_data1(reg_data[1][31:0]),.reg_data2(reg_data[2][31:0]),.reg_data3(reg_data[3][31:0]),.reg_data4(reg_data[4][31:0]),.reg_data5(reg_data[5][31:0]),.reg_data6(reg_data[6][31:0]),.reg_data7(reg_data[7][31:0]));
//Read operation logic

endmodule