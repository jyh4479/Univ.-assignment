module ram(clk, cen, wen, addr, din, dout); //The module of memory

   input clk,cen,wen; //inputs
   input [4:0] addr;
   input [31:0] din;

   output reg [31:0] dout; //outputs, regs
   reg [31:0] mem [0:31];

   integer i; //integer


initial begin //for initialize value of memory
for(i=1'b0; i<10'd32; i=i+1) begin
   mem[i]=32'b0;
  end
end



always @ (posedge clk) //practice function when posedge clk
begin
if(cen==1'b1 && wen==1'b1) begin //if cen and wen is 1
   mem[addr]<=din;
   dout<=32'b0;
  end

  
else if(cen==1'b1 && wen==1'b0) begin //if cen is 1 and wen is 0
   dout<=mem[addr];
  end


else if(cen==1'b0) begin //if cen is 0
   dout<=1'b0;
  end

end

endmodule
