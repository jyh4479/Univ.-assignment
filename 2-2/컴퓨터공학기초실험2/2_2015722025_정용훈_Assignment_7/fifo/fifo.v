module fifo(clk, reset_n, rd_en, wr_en, din, dout,data_count,full,empty,wr_ack,wr_err,rd_ack,rd_err); //FIFO
	input clk,reset_n,rd_en,wr_en; //Input
	input [31:0]din;
	output [31:0]dout; //output
	output full,empty;
	output wr_ack,wr_err,rd_ack,rd_err;
	output [3:0]data_count;
	
	wire [2:0]head,next_head; //wires
	wire [2:0]tail,next_tail;
	wire [2:0]state,next_state;
	wire [3:0]next_data_count;
	wire we,re;
	wire [31:0]to_mux,to_ff;
	//instance
	fifo_ns U0_fifo_ns(.wr_en(wr_en), .rd_en(rd_en), .state(state), .data_count(data_count), .next_state(next_state)); //next state
	fifo_cal U1_fifo_cal(.state(next_state),.head(head),.tail(tail),.data_count(data_count),.we(we),.re(re),.next_head(next_head),.next_tail(next_tail),.next_data_count(next_data_count)); //calculator
	fifo_out U2_fifo_out(.state(state),.data_count(data_count),.full(full),.empty(empty),.wr_ack(wr_ack),.wr_err(wr_err),.rd_ack(rd_ack),.rd_err(rd_err)); //output
	Register_file U3_register_file(.clk(clk),.reset_n(reset_n),.wAddr(tail),.wData(din),.we(we),.rAddr(head),.rData(to_mux)); //Register file
	_dff_32_r U4_dout(.clk(clk), .reset_n(reset_n), .d(to_ff), .q(dout)); //Data out
	_dff_3_r U5_head(.clk(clk), .reset_n(reset_n), .d(next_head), .q(head)); //head of data
	_dff_3_r U6_tail(.clk(clk), .reset_n(reset_n), .d(next_tail), .q(tail)); //tail of data
	_dff_3_r U7_sate(.clk(clk), .reset_n(reset_n), .d(next_state), .q(state)); //state
	_dff_4_r U8_data_count(.clk(clk), .reset_n(reset_n), .d(next_data_count), .q(data_count)); //number of data
	mx2 U9_mx2(.d0(to_mux),.d1(32'h00000000),.s(re),.y(to_ff)); //mux
endmodule