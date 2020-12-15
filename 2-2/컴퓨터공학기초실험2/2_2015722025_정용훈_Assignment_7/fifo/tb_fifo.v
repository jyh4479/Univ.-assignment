`timescale 1ns/100ps //time scale

module tb_fifo; //start module
reg tb_clk,tb_reset_n,tb_rd_en,tb_wr_en; //reg
reg [31:0] tb_din;
wire [31:0] tb_dout; //wire
wire [3:0] tb_data_count;
wire tb_full,tb_empty,tb_wr_ack,tb_wr_err,tb_rd_ack,tb_rd_err;



fifo U0_fifo(.clk(tb_clk),.reset_n(tb_reset_n),.rd_en(tb_rd_en) //instance fifo
,.wr_en(tb_wr_en),.din(tb_din),.dout(tb_dout),.data_count(tb_data_count)
,.full(tb_full),.empty(tb_empty),.wr_ack(tb_wr_ack),.wr_err(tb_wr_err),.rd_ack(tb_rd_ack),.rd_err(tb_rd_err));

always # 5 tb_clk=~tb_clk; //for clock
initial
begin //begin test
tb_clk=1'b0; tb_reset_n=1'b0; tb_rd_en=1'b0;tb_wr_en=1'b0;tb_din=32'h0;
#12 tb_reset_n=1'b1; 
#10 tb_rd_en=1'b1; 
#10 tb_rd_en=1'b0; tb_wr_en=1'b1;tb_din=32'h00000011;
#10 tb_din=32'h00000020;
#10 tb_din=32'h00000015;
#10 tb_din=32'h00000072;
#10 tb_din=32'h00000020;
#10 tb_din=32'h00000025;
#10 tb_din=32'h00000044;
#10 tb_din=32'h00000055;
#10 tb_din=32'h00000066;
#10 tb_din=32'h000000aa;
#10 tb_din=32'h000000ff;
#10 tb_wr_en=1'b0;
#30 tb_rd_en=1'b1;
#60 tb_wr_en=1'b1; tb_rd_en=1'b0;
#10 tb_din=32'h000000cc;
#10 tb_din=32'h00000001;
#10 tb_din=32'h00000002;
#10 tb_din=32'h00000003;
#10 tb_din=32'h00000005;
#10 tb_wr_en=1'b0; tb_rd_en=1'b1;
#30 tb_rd_en=1'b0; 
#10 tb_rd_en=1'b1;
#100 $stop;
end //end test
endmodule //end module