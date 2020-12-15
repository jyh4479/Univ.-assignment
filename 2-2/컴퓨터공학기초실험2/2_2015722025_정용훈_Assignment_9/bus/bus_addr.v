module bus_addr(s_address,s0_sel, s1_sel); // address decoder module
input [7:0]s_address;
output reg s0_sel, s1_sel;
//check range of address 
always@(s_address)
	begin
	if((s_address >= 8'h00)&&(s_address <8'h20)) //if the address is 0x00=<s_address <0x20,
		{s0_sel, s1_sel} <= 2'b10;						//s0_sel = 1, s1_sel = 0
	else if((s_address >= 8'h20)&&(s_address < 8'h40))//if the address is 0x20=<s_address <0x40,
		{s0_sel, s1_sel} <= 2'b01;							  // s0_sel = 0, s1_sel = 1
	else																// else print 0
		{s0_sel, s1_sel} <= 2'b00;
end
endmodule