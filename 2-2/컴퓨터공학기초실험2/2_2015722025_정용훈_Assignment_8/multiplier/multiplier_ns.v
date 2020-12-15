module multiplier_ns(reset_n,op_start,op_clear,state,next_state,multiplier,multiplicand,count,next_count,next_multiplier,next_multiplicand); //The logic for Declare next state
input op_start,op_clear,reset_n; //input
input [1:0]state;
input [31:0]multiplier, multiplicand;
input [4:0]count;

output reg [1:0]next_state; //output, reg
output reg [4:0]next_count;
output reg [31:0]next_multiplier,next_multiplicand;

reg flag; //for check condition

reg [31:0]prev_multiplier,prev_multiplicand; //Variables for maintaining values

parameter IDLE = 2'b00; //Declare parameter
parameter EXEC = 2'b01;
parameter DONE = 2'b10;

always@(op_start or op_clear or count or state or multiplier or multiplicand) //The condition of running
begin
case(state) //case state
IDLE : begin //When IDLE

if(op_start==0) begin //if op_start is 0
	next_state<=IDLE; //Declare next values
	next_count<=count;
	next_multiplicand<=multiplicand;
	next_multiplier<=multiplier;
	prev_multiplicand<=multiplicand;
	prev_multiplier<=multiplier;
	flag<=1;
	end

else if(multiplier==prev_multiplier&&multiplicand==prev_multiplicand&&flag==0&&reset_n==1) next_state<=IDLE; //The condtion for maintaining values

else //else
begin
	
	if(op_clear!=1&&op_start) //if op_clear is not 1 and op_start is 1
	begin
	next_state<=EXEC; //Declare next values
	next_count<=5'b00000;
	next_multiplicand<=multiplicand;
	next_multiplier<=multiplier;
	prev_multiplicand<=multiplicand;
	prev_multiplier<=multiplier;
	flag<=1;
	end
	
	
	else if(reset_n==0) //if reset_n is 0
	begin
	next_state<=IDLE; //Declare next values
	next_count<=5'b00000;
	next_multiplicand<=0;
	next_multiplier<=0;
	end
	
	else if(op_clear==1) //if op_clear is 1
	begin
	next_state<=IDLE; //Declare next values
	next_count<=5'b00000;
	next_multiplicand<=0;
	next_multiplier<=0;
	flag<=1;
	end
	
	else //else
	begin
	next_state<=IDLE;
	next_count<=0;
	end
end
end

EXEC : begin //When the state is EXEC
if(op_start==0) //if op_start is 0
begin
next_state<=EXEC; //Declare next values
next_count<=count;
next_multiplicand<=multiplicand;
next_multiplier<=multiplier;
end

else begin //else

if(op_clear!=1&&count!=5'b10000) //if op clear is not 1 and count is not 10000
begin
next_state<=EXEC; //Declare next values
next_count<=count+1;
next_multiplicand<=multiplicand;
next_multiplier<=multiplier;
flag<=0;
end

else if(op_clear!=1&&count==5'b10000) //if op_clear is not 1 and count is 10000
begin
next_state<=DONE; //Declare next values
next_count<=5'b00000;
next_multiplicand<=multiplicand;
next_multiplier<=multiplier;
end

else if(op_clear) //if op_clear is 1
begin
next_state<=IDLE; //Declare next values
next_count<=5'b00000;
next_multiplicand<=0;
next_multiplier<=0;
flag<=1;
end

else //else
begin
next_multiplicand<=multiplicand; //Declare next values
next_multiplier<=multiplier;
next_state<=DONE;
end
end
end

DONE : begin //When state is DONE
if(op_clear) begin //if op_clear is 1
next_state<=IDLE; //Declare next values
flag<=1;
end
else
begin
	next_state<=IDLE; //else next_state is IDLE
end
end
endcase
end
endmodule
