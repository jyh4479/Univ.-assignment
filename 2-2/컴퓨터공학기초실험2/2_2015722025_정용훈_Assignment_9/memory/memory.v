module memory(clk, cen, wen, addr, din, dout);//Declae moudle
   input clk, cen, wen; //input
   input [4:0]addr; //address
   input [31:0]din; //data
   output reg [31:0]dout; //output reg

   reg [31:0] mem [0:31];
   integer i;

   initial begin //setting all memory to 0
      for(i=0; i<32; i=i+1)
            mem[i]<=5'b0;
   end
   
   always @(posedge clk)
          begin
                  if(cen==1&&wen==1) //if cen and wen is 1
                         begin
                         mem[addr]<=din; dout<=32'b0; //save data to memory
                         end
                  else if(cen==1&&wen==0) dout<=mem[addr]; //if cen is 1 and wen is 0 read data
                  else dout<=32'b0; //else
          end
endmodule