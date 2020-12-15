module slave(M_din,S_address,S_din,S_sel,S_wr,adder_op_done,clk,reset_n,result,fifo_data_count0,fifo_data_count1,
S_dout,adder_op_start,m_interrupt,op_clear,multi_op_start,multiplicand,multiplicand_we,multiplier,multiplier_we,rAddr);//Declare module of Slave

   input [31:0] M_din,S_din,result;//inputs
   input [7:0] S_address;
   input S_sel,S_wr,clk,reset_n,adder_op_done;
   input [3:0] fifo_data_count0,fifo_data_count1;//data count of FIFO

   output [31:0]S_dout;//outputs
   output m_interrupt;

   output reg [31:0] multiplicand,multiplier;//outputs and regs
   output reg adder_op_start,multi_op_start,op_clear,multiplicand_we,multiplier_we;
   output reg [2:0] rAddr;

   reg s_interrupt;//regs
   reg [2:0] next_rAddr;

   wire m_interrupt,we,we2,multiop_start,addop_start,clear,interrupt;//wires
   wire [31:0] S_dout;

   parameter Amatrix=8'b00000000;//Declare parameter of offset
   parameter Bmatrix=8'b00000001;
   parameter INTERRUPT=8'b00000010;
   parameter MULTISTART=8'b00000011;
   parameter ADDSTART=8'b00000100;
   parameter OP_CLEAR=8'b00000101;
   parameter READADDR=8'b00000110;

   _and2 U1_and2(S_sel,(S_address!=Amatrix)?1'b0:((fifo_data_count1 < 4'b1000)?S_wr:1'b0),we);//0x0
   _and2 U2_and2(S_sel,(S_address!=Bmatrix)?1'b0:((fifo_data_count0 < 4'b1000)?S_wr:1'b0),we2);//0x1
   _and2 U6_and2(S_sel,(S_address==INTERRUPT)?((S_wr==1'b1)?((S_din==1'b1)?1'b1:1'b0):1'b0):1'b0,interrupt);//0x2
   _and2 U3_and2(S_sel,(S_address==MULTISTART)?((S_wr==1'b1)?((S_din==1'b1)?1'b1:1'b0):1'b0):1'b0,multiop_start);//0x3
   _and2 U4_and2(S_sel,(S_address==ADDSTART)?((S_wr==1'b1)?((S_din==1'b1)?1'b1:1'b0):1'b0):1'b0,addop_start);//0x4
   _and2 U5_and2(S_sel,(S_address==OP_CLEAR)?((S_wr==1'b1)?((S_din==1'b1)?1'b1:1'b0):1'b0):1'b0,clear);//0x5


always@(posedge clk or negedge reset_n)//practice function when change variable
begin
if(reset_n==1'b0) begin//check reset signal
   multiplicand<=32'b0;
   multiplicand_we<=1'b0;

   multiplier<=32'b0;
   multiplier_we<=1'b0;

   multi_op_start<=1'b0;

   adder_op_start<=1'b0;

   op_clear<=1'b0;

   rAddr<=3'b0;
  end

else begin//there is not reset signal
   multiplicand<=M_din;
   multiplicand_we<=we;

   multiplier<=M_din;
   multiplier_we<=we2;

   multi_op_start<=multiop_start;

   adder_op_start<=addop_start;

   op_clear<=clear;

   rAddr<=next_rAddr;
  end
end


always@(S_address or s_interrupt or interrupt)//practice function when change variable
begin
if(S_address==INTERRUPT) s_interrupt<=interrupt;//check address of interrupt

else s_interrupt<=s_interrupt;//else
end


always@(result or S_address or rAddr or m_interrupt or S_wr or S_sel)//practice function when change variable
begin
if(m_interrupt==1'b1) next_rAddr<=rAddr;//check signal of interrupt

else if(S_address==READADDR && S_wr==1'b1) next_rAddr<=rAddr+3'b1;

else if(S_address!=READADDR && S_wr==1'b1) next_rAddr<=rAddr;

else next_rAddr<=3'b0;
end


assign S_dout=result;
_and2 U0_and2(s_interrupt,adder_op_done,m_interrupt);


endmodule

