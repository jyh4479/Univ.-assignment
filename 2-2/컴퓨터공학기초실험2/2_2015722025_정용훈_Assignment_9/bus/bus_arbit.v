module bus_arbit(M0_req,M1_req,reset_n,clk, out); //Declare module of arbiter
input clk, reset_n, M0_req, M1_req; //input
output reg [1:0] out; //output reg
reg [1:0]next; //reg

parameter M0_GRANT = 2'b01; //Delcare parameter of grant
parameter M1_GRANT = 2'b10;

initial
begin
	out <= M0_GRANT; //Initial setting
end

always@(posedge clk or negedge reset_n)
begin
	if(reset_n == 1'b0) 
	begin
		if(out != M0_GRANT)  out<= 2'b00; //if out is not M0 grant, out is 00
	end
	else	out <= next;						//else out is next
end


always@(M0_req, M1_req)
begin 
	if((M0_req==0 && M1_req ==0)||M0_req ==1) next <= M0_GRANT; // M0_req, M1_req are 0 or M0_req is 0,save_GRANT M0 to next
	else if((M0_req ==0)&&(M1_req==1)) next <= M1_GRANT;			//	M0_req, is 0 and M1_req is 1,save_GRANT M1 to next
	else if(M1_req == 1) next <= M1_GRANT;								// M1_req is 1, M1_GRANT
	else if(M1_req == 0) next <= M0_GRANT;								// M1_req is 0  M0_GRANT
	else ;
end

endmodule