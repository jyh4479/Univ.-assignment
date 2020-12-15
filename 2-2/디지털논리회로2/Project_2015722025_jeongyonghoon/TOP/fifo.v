module fifo(clk,reset_n,op_clear,rd_en,wr_en,din,dout,data_count);//Declare module of FIFo

   input clk, reset_n, rd_en,wr_en,op_clear; //inputs
   input [31:0] din;

   output [31:0] dout; //outputs
   output [3:0] data_count;

   wire we, re;//wires
   wire [2:0] state,next_state,tail,next_tail,head,next_head;
   wire [3:0] next_data_count;
   wire [31:0] rData,w;


RF U0(.clk(clk),.clear(opclear),.wAddr(tail),.wData(din),.we(we),.rAddr(head),.rData(rData)); //Register file

fifo_cal U1(.state(next_state),.head(head),.tail(tail),.data_count(data_count),.we(we),.re(re),.next_head(next_head),.next_tail(next_tail),.next_data_count(next_data_count)); //fifo calculation of address
fifo_ns U2(.op_clear(op_clear),.wr_en(wr_en),.rd_en(rd_en),.state(state),.data_count(data_count),.next_state(next_state)); //next state

_dff_3_r U3(.clk(clk),.reset_n(reset_n),.d(next_state),.q(state)); //Flip Flop
_dff_3_r U4(.clk(clk),.reset_n(reset_n),.d(next_head),.q(head));
_dff_3_r U5(.clk(clk),.reset_n(reset_n),.d(next_tail),.q(tail));
_dff_4_r U6(.clk(clk),.reset_n(reset_n),.d(next_data_count),.q(data_count));
_dff_for_check U7(.clk(clk),.reset_n(reset_n),.next_data_count(next_data_count),.a(rData),.d(w),.q(dout));//
mx2 U8(.a(rData),.y(w),.en(re)); //mux
endmodule