module master(rAddr,clk,reset_n,S_sel,S_wr,op_clear,m_interrupt,rData,M1_address,M1_dout,M1_req,M1_wr);//Declare module of master

   input clk,reset_n,S_sel,S_wr,op_clear,m_interrupt; //inputs
   input [31:0] rData;
   input [2:0] rAddr;

   output M1_req,M1_wr;//outputs
   output [7:0] M1_address;
   output [31:0] M1_dout;

   wire [2:0]count,next_count;//wires
   wire [7:0] next_M1_address;

master_ns U0(count,rAddr,m_interrupt,S_sel,S_wr,op_clear,M1_address,next_count,next_M1_address);//next state of master

master_out U1(count,M1_address,rData,M1_dout,M1_req,M1_wr);//output logic

_dff_3_r U2(.clk(clk),.reset_n(reset_n),.d(next_count),.q(count));//flip flop
_dff_8_r U3(.clk(clk),.reset_n(reset_n),.d(next_M1_address),.q(M1_address));

endmodule