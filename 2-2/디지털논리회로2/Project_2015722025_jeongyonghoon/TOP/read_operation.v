module read_operation(Addr,Data,reg_data0,reg_data1,reg_data2,reg_data3,reg_data4,reg_data5,reg_data6,reg_data7); //Declare module of read

   input [31:0] reg_data0,reg_data1,reg_data2,reg_data3,reg_data4,reg_data5,reg_data6,reg_data7;//inputs
   input [2:0] Addr;

   output [31:0] Data; //output

   wire [31:0] data_wire; //wires
   wire [31:0] ff_wire;


_8_to_1_MUX U0(.a(reg_data0),.b(reg_data1),.c(reg_data2),.d(reg_data3),.e(reg_data4),.f(reg_data5),.g(reg_data6),.h(reg_data7),.sel(Addr),.d_out(Data));//instance 8 to 1 Mux

endmodule
