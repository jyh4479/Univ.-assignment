module tl_cntr_w_left(clk,reset_n,Ta,Tal,Tb,Tbl,La,Lb); //The tl_cntr_left
	input clk,reset_n,Ta,Tb,Tal,Tbl; //inputs
	output [1:0]La,Lb; //outputs
	wire [2:0]w1,w2; //wires
	
	ns_logic U0_ns_logic(.Ta(Ta),.Tal(Tal),.Tb(Tb),.Tbl(Tbl),.s(w2),.d(w1)); //next state
	_register3_r U1_register3(.clk(clk),.reset(reset_n),.d(w1),.q(w2)); //register
	o_logic U2_o_logic(.q(w2),.La(La),.Lb(Lb)); //output logic
endmodule