module MATRIX_Top/*matrix*/(M_din,S_din,S_address,S_sel,S_wr,clk,reset_n,m_interrupt,multi_done,S_dout,M1_address,M1_dout,M1_req,M1_wr);
//The module of Top matrix that contains 3 fifo, 1 multiplier, 1 adder, 1 slave, 1 master

   input S_sel,S_wr,clk,reset_n;//inputs
   input [31:0] M_din,S_din;
   input [7:0] S_address;


   output m_interrupt,multi_done,M1_req,M1_wr;//outputs
   output [31:0] S_dout;
   output [7:0] M1_address;
   output [31:0] M1_dout;

   wire adder_op_start,multi_op_start,multiplicand_we,multiplier_we,adder_op_done,op_clear,fifo_write,Register_we,S_sel,m_interrupt,fifo_read;//wires
   wire [31:0] S_dout,multiplicand,multiplier,result,multi_out_result,adder_out_result,fifo_multiplier,fifo_multiplicand;
   wire [2:0] rAddr,wAddr;
   wire [3:0] data_count0,data_count1;
   wire [3:0] fifo_data_count2;
   wire [31:0] multi_result;
   wire adder_fifo_read;



//////////////////////////////////////////////Multiplier//////////////////////////////////////////////
fifo U0_multi_fifo0(.clk(clk),.reset_n(reset_n),.op_clear(op_clear),.rd_en(fifo_read),.wr_en(multiplier_we),.din(multiplier),.dout(fifo_multiplier),
.data_count(data_count0));//fifo0
fifo U1_multi_fifo1(.clk(clk),.reset_n(reset_n),.op_clear(op_clear),.rd_en(fifo_read),.wr_en(multiplicand_we),.din(multiplicand),.dout(fifo_multiplicand),//fifo1
.data_count(data_count1));
multiplier U3_multiplier(.fifo_data_count0(data_count0),.fifo_data_count1(data_count1),.clk(clk),.reset_n(reset_n),.op_start(multi_op_start),.op_clear(op_clear),.multiplicand(fifo_multiplicand),.multiplier(fifo_multiplier),.out_result(multi_out_result),.op_done(multi_done),.fifo_read(fifo_read),.fifo_write(fifo_write));//multiplier


//////////////////////////////////////////////Adder//////////////////////////////////////////////
fifo U0_fifo2(.clk(clk),.reset_n(reset_n),.op_clear(op_clear),.rd_en(adder_fifo_read),.wr_en(fifo_write),.din(multi_out_result),.dout(multi_result),.data_count(fifo_data_count2));//fifo2
adder U1_adder(.din(multi_result),.op_start(adder_op_start),.clk(clk),.fifo_data_count(fifo_data_count2),.op_clear(op_clear),.reset_n(reset_n),.Register_we(Register_we),.op_done(adder_op_done),.out_result(adder_out_result),.fifo_read(adder_fifo_read),.wAddr(wAddr));//adder


//////////////////////////////////////////////RF//////////////////////////////////////////////
RF U2_Register_file(.clk(clk),.clear(op_clear),.wAddr(wAddr),.wData(adder_out_result),.we(Register_we),.rAddr(rAddr),.rData(result));//Register file


//////////////////////////////////////////////Slave//////////////////////////////////////////////
slave U0_slave(.M_din(M_din),.S_address(S_address),.S_din(S_din),.S_sel(S_sel),.S_wr(S_wr),.adder_op_done(adder_op_done),.clk(clk),.reset_n(reset_n),.result(result),.fifo_data_count0(data_count0),.fifo_data_count1(data_count1),.S_dout(S_dout),.adder_op_start(adder_op_start),.m_interrupt(m_interrupt),.op_clear(op_clear),.multi_op_start(multi_op_start),.multiplicand(multiplicand),.multiplicand_we(multiplicand_we),.multiplier(multiplier),.multiplier_we(multiplier_we),.rAddr(rAddr));//Slave


//////////////////////////////////////////////Master//////////////////////////////////////////////
master U0_master(.rAddr(rAddr),.clk(clk),.reset_n(reset_n),.S_sel(S_sel),.S_wr(S_wr),.op_clear(op_clear),.m_interrupt(m_interrupt),.rData(S_dout),.M1_address(M1_address),.M1_dout(M1_dout),.M1_req(M1_req),.M1_wr(M1_wr));//master

endmodule



