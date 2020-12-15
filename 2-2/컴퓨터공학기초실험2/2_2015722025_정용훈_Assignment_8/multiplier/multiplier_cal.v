module multiplier_cal(clk, reset_n, op_start,op_clear ,multiplier, multiplicand, state, op_done, result,count); //The logic of calculation
   input clk, reset_n, op_start,op_clear; //input
   input [31:0]multiplier, multiplicand;
   input [1:0]state;
   input [4:0]count;
   output reg op_done; //output reg
   output reg[63:0]result;
   
   reg [2:0]radix; //reg
   reg [31:0]u,v,M;
   reg flag;

   wire [31:0]sum,sub; //wire
   wire [31:0]sum2,sub2;
   
   parameter IDLE = 2'b00; //Declare parameter
   parameter EXEC = 2'b01;
   parameter DONE = 2'b10;
   
   always@(posedge clk or negedge reset_n) begin //The device run according to clcok and reset_n signal
   case(state) //case state
   IDLE:begin //when state is IDLE

if(op_clear==1 || reset_n==0) begin //if op_clear is 1 or reset_n is 0
	result=0; //Reset all values to zero
	radix<=0; 
   v <= 32'b0; 
   M <= 32'b0;
   u <= 32'b0;
   op_done <= 0;
	end
   
	else begin //else
   radix<={multiplier[1],multiplier[0],1'b0}; //Declare radix for calculation
   v <= 32'b0;
   M <= multiplicand;
   u <= multiplier;
   op_done <= 0;
	end

   end

EXEC: begin //When state is EXEC

if(count==5'b10000)begin //if count is 10000
result <= {v,u}; //Declare result
op_done<=1;
end

else if(op_start==0) begin //if op_start is 0
radix<=radix; //Keep all values
v<=v;
u<=u;
result=result;
end

else if(op_clear==1 || reset_n==0) begin //if op_clear is 1 or reset_n is 0
result=0; //Reset all values to zero
radix<=0;
v <= 32'b0;
M <= 32'b0;
u <= 32'b0;
op_done <= 0;
end

else if(count!=5'b10000)begin //If count is not 10000, Run next operation
   if(radix == 3'b000)begin //0
      radix <= {u[3:1]};
      {v, u} = {v[31],v,u[31:1]};
      {v, u} = {v[31],v,u[31:1]};
		result = {v,u};
   end
   if(radix == 3'b010)begin //A
      radix <= {u[3:1]};
      {v , u} = {sum[31],sum,u[31:1]};
      {v, u}  = {v[31] ,v ,u[31:1]};
		result = {v,u};
   end
   if(radix == 3'b100)begin //-2A
      radix <= {u[3:1]};
      {v ,u}  = {sub2[31],sub2,u[31:1]};
      {v, u}  = {v[31],v,u[31:1]};
		result = {v,u};
   end
   if(radix == 3'b110)begin //-A
      radix <= {u[3:1]};
      {v ,u}  = {sub[31],sub,u[31:1]};
      {v, u}  = {v[31],v,u[31:1]};
		result = {v,u};
   end
   if(radix == 3'b001)begin //A
      radix <= {u[3:1]};
      {v , u} = {sum[31],sum,u[31:1]};
      {v, u}  = {v[31],v,u[31:1]};
		result = {v,u};
   end
   if(radix == 3'b011)begin //2A
      radix <= {u[3:1]};
      {v , u} = {sum2[31],sum2,u[31:1]};
      {v, u}  = {v[31],v,u[31:1]};
		 result = {v,u};
   end
   if(radix == 3'b101)begin //-A
      radix <= {u[3:1]};
      {v ,u}  = {sub[31],sub,u[31:1]};
      {v, u}  = {v[31],v,u[31:1]};
		result = {v,u};
   end
   if(radix == 3'b111)begin //0
      radix <= {u[3:1]};
      {v, u}  = {v[31],v,u[31:1]};
      {v, u}  = {v[31],v,u[31:1]};
		result = {v,u};
   end
   end
end
   
   DONE: begin //When state is DONE
   //There is no operation
   end
   endcase
   end
   cla32 adder(sum, v, M, 1'b0); //for add
   cla32 adder2(sum2,sum,M,1'b0);
   cla32 subtracter(sub, v, ~M, 1'b1); //for subtract
   cla32 subtracter2(sub2,sub,~M,1'b1);
   endmodule