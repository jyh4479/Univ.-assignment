module tl_cntr(clk,reset_n,Ta,Tb,La,Lb); //The tl_cntr
	input clk,reset_n,Ta,Tb; //inputs
	output [1:0]La,Lb; //outputs
	
	wire [1:0]w1,w2; //wires
	
	ns_logic U0_ns_logic(Ta,Tb,w2,w1); //next state
	_register2_r U1_register2_r(clk,reset_n,w1,w2); //register
	o_logic U2_o_logic(w2,La,Lb); //output logic
endmodule