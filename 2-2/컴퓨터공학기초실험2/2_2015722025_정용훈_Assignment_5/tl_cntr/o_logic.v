module o_logic(q,La,Lb); //output logic
	input [1:0]q; //inputs
	output [1:0]La,Lb; //outputs
	
	_and2 U0_and2(.a(q[0]),.b(q[1]),.y(Lb[0])); //Lb0
	_inv U1_inv(.a(q[1]),.y(Lb[1])); //Lb1
	_and2 U2_and2(.a(q[0]),.b(~q[1]),.y(La[0])); //La0
	assign La[1]=q[1]; //La1
endmodule