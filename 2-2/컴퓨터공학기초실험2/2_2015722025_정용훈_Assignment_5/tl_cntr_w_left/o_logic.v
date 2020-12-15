module o_logic(q,La,Lb); //output logic
	input [2:0]q; //inputs
	output [1:0]La,Lb; //outputs
	
	wire [1:0]w1; //wires
	
	//La1
	_and2 U0_and2(.a(q[1]),.b(~q[0]),.y(w1[0]));
	_or2 U1_or2(.a(w1[0]),.b(q[2]),.y(La[1]));
	
	//La0
	_or2 U2_or2(.a(q[0]),.b(q[2]),.y(La[0]));
	
	//Lb1
	_and2 U3_and2(.a(q[1]),.b(~q[0]),.y(w1[1]));
	_or2 U4_or2(.a(~q[2]),.b(w1[1]),.y(Lb[1]));
	
	//Lb0
	_or2 U5_or2(.a(~q[2]),.b(q[0]),.y(Lb[0]));
endmodule