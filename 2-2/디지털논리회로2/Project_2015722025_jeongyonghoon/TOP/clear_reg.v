module clear_reg(op_clear,d_out0,d_out1,d_out2,d_out3,d_out4,d_out5,d_out6,d_out7);
input op_clear;
output reg [31:0] d_out0,d_out1,d_out2,d_out3,d_out4,d_out5,d_out6,d_out7;


always@(op_clear)
begin
if(op_clear==1'b1)
	begin
	d_out0<=32'b0;
	d_out1<=32'b0;
	d_out2<=32'b0;
	d_out3<=32'b0;
	d_out4<=32'b0;
	d_out5<=32'b0;
	d_out6<=32'b0;
	d_out7<=32'b0;
	end
end

endmodule


