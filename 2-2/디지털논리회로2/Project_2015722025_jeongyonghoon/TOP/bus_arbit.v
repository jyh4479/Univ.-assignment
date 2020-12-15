module bus_arbit(clk,reset_n,M0_req,M1_req,M0_grant,M1_grant);//Declare module of arbiter

   input clk,reset_n,M0_req,M1_req;//inputs
   output reg M0_grant, M1_grant; //outputs
   reg next_M0_grant, next_M1_grant; //regs



always@(posedge clk or negedge reset_n)//practice function when change variable
begin
if(reset_n==1'b0) begin//check reset_n
   M0_grant<=1'b1; 
   M1_grant<=1'b0; 
  end

else begin//else
   M0_grant<=next_M0_grant;
   M1_grant<=next_M1_grant;
  end
end


/////////////////////////////////////////////////

always@(M0_grant,M1_grant,M0_req,M1_req)//practice function when change variable
begin
case({M0_grant,M1_grant})
2'b10: begin
   if((M0_req==1'b0) && (M1_req==1'b1)) begin //check signal of request
      next_M0_grant=1'b0;
      next_M1_grant=1'b1;
     end

   else begin //else on M0 signal
      next_M0_grant=1'b1;
      next_M1_grant=1'b0;
     end
   end


2'b01: begin
   if(M1_req==1'b0) begin //check signal of request
      next_M0_grant=1'b1;
      next_M1_grant=1'b0;
     end

   else begin
      next_M0_grant=M0_grant; //keep signal
      next_M1_grant=M1_grant;
     end
   end


default: begin//default
   next_M0_grant = 1'bx;
   next_M1_grant = 1'bx;
  end
 endcase
end
endmodule