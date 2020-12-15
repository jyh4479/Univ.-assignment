module master_out(count,M1_address,rData,M1_dout,M1_req,M1_wr); //Declare module of out logic

   input [2:0] count; //inputs
   input [7:0] M1_address;
   input [31:0] rData;

   output reg M1_req,M1_wr; //outputs
   output reg [31:0] M1_dout;

always@(count or M1_address or rData) //practice function when change variable
begin
case(count)//case of count
3'b0 : begin //IDLE
      M1_dout<=32'b0;
      M1_req<=1'b0;
      M1_wr<=1'b0;
      end


default : begin //EXEC
      M1_dout<=rData;
      M1_req<=1'b1;
      M1_wr<=1'b1;
      end
endcase
end

endmodule