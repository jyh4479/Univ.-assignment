module tb_TOP;

reg clk, reset_n;
reg M0_req, M0_wr;
reg[7:0]M0_address;
reg[31:0]M0_dout;
reg wr;

wire M0_grant, M1_grant;
wire [31:0]	M_din;
wire			m_interrupt, multi_opdone;

TOP U0_TOP(clk, reset_n, M0_req, M0_wr, M0_address, M0_dout, M0_grant, M1_grant, M_din, m_interrupt, multi_opdone);
always #5 clk = ~clk;

initial
begin
clk=0; reset_n=0; M0_req=0; M0_wr=0; M0_address=0; M0_dout=0; wr=0; #10;
M0_req=1; reset_n = 1; #10; //testbench master

M0_wr=1;  M0_address=32; M0_dout=10; #10;
M0_wr=1;  M0_address=33; M0_dout=11; #10;
M0_wr=1;  M0_address=34; M0_dout=12; #10;
M0_wr=1;  M0_address=35; M0_dout=13; #10;//A Matrix write


M0_wr=1;  M0_address=64; M0_dout=14; #10;
M0_wr=1;  M0_address=65; M0_dout=16; #10;
M0_wr=1;  M0_address=66; M0_dout=15; #10;
M0_wr=1;  M0_address=67; M0_dout=17; #10;//B Matrix write

M0_wr=0;  M0_address=32; M0_dout=10; #10;
M0_wr=1;  M0_address=0; M0_dout=0; #10;
M0_wr=0;  M0_address=33; M0_dout=11; #10;
M0_wr=1;  M0_address=0; M0_dout=0; #10;
M0_wr=0;  M0_address=32; M0_dout=10; #10;
M0_wr=1;  M0_address=0; M0_dout=0; #10;
M0_wr=0;  M0_address=33; M0_dout=11; #10;
M0_wr=1;  M0_address=0; M0_dout=0; #10;
M0_wr=0;  M0_address=34; M0_dout=12; #10;
M0_wr=1;  M0_address=0; M0_dout=0; #10;
M0_wr=0;  M0_address=35; M0_dout=13; #10;
M0_wr=1;  M0_address=0; M0_dout=0; #10;
M0_wr=0;  M0_address=34; M0_dout=12; #10;
M0_wr=1;  M0_address=0; M0_dout=0; #10;
M0_wr=0;  M0_address=35; M0_dout=13; #10;
M0_wr=1;  M0_address=0; M0_dout=0; #10;//A Matrix read and send MATRIX_top's A_FIFO

M0_wr=0; M0_address=64; M0_dout=14; #10;
M0_wr=1;  M0_address=1; M0_dout=0; #10;
M0_wr=0; M0_address=65; M0_dout=16; #10;
M0_wr=1;  M0_address=1; M0_dout=0; #10;
M0_wr=0; M0_address=66; M0_dout=15; #10;
M0_wr=1;  M0_address=1; M0_dout=0; #10;
M0_wr=0; M0_address=67; M0_dout=17; #10;
M0_wr=1;  M0_address=1; M0_dout=0; #10;
M0_wr=0; M0_address=64; M0_dout=14; #10;
M0_wr=1;  M0_address=1; M0_dout=0; #10;
M0_wr=0; M0_address=65; M0_dout=16; #10;
M0_wr=1;  M0_address=1; M0_dout=0; #10;
M0_wr=0; M0_address=66; M0_dout=15; #10;
M0_wr=1;  M0_address=1; M0_dout=0; #10;
M0_wr=0; M0_address=67; M0_dout=17; #10;
M0_wr=1;  M0_address=1; M0_dout=0; #10;//B Matrix read and send MATRIX_top's B_FIFO


M0_address=8'b00000011; M0_wr=1'b1; M0_req=1'b0; M0_dout=32'b1; //multiplication start

while(multi_opdone!=1'b1)//repeat function until turn on the opdone
begin
   #10;
end

M0_address=8'b000000010;//interrupt
#10 M0_address=8'b00000100;//start addition

while(m_interrupt!=1'b1)//repeat function until turn on the interrupt
begin
   #10;
end

#10 M0_address=8'b00000110; M0_wr=1'b0;//read result

while(M1_grant!=1'b0)//check grant
begin
   #10;
end

#90 M0_address=8'b00000101;
#20 $stop;
end
endmodule
