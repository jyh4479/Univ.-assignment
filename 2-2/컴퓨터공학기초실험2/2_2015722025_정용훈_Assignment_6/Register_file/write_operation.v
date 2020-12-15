module write_operation(Addr,we,to_reg); //write operation
	input we;//Input List
	input [2:0]Addr;
	output [7:0]to_reg;//Output List
	
	wire[7:0] write_wire;//wire
	
	_3_to_8_decoder U0(.d(Addr),.q(write_wire));//instance 3to 8
	_and2 U1(.a(write_wire[0]),.b(we),.y(to_reg[0]));//intstance and gate
	_and2 U2(.a(write_wire[1]),.b(we),.y(to_reg[1]));
	_and2 U3(.a(write_wire[2]),.b(we),.y(to_reg[2]));
	_and2 U4(.a(write_wire[3]),.b(we),.y(to_reg[3]));
	_and2 U5(.a(write_wire[4]),.b(we),.y(to_reg[4]));
	_and2 U6(.a(write_wire[5]),.b(we),.y(to_reg[5]));
	_and2 U7(.a(write_wire[6]),.b(we),.y(to_reg[6]));
	_and2 U8(.a(write_wire[7]),.b(we),.y(to_reg[7]));
	
endmodule