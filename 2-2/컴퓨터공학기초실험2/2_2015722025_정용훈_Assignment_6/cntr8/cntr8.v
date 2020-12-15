module cntr8(clk, reset_n, inc, load, d_in, d_out, o_state); //cntr8
	input clk, reset_n, inc, load; //input
	input [7:0] d_in;
	output [7:0] d_out; //output
	output [2:0] o_state;
	
	wire [2:0] next_state; //wire
	wire [2:0] state;
	
	assign o_state = state;
		//instance _register3_r
	_register3_r U0_reg3r (.clk(clk),.reset_n(reset_n),
								.d(next_state),.q(state));
	//instance ns_logic		
	ns_logic U1_ns_logic  (.load(load),.inc(inc),.state(o_state),
								.next_state(next_state));	
	//instance os_logic							
	os_logic U2_os_logic  (.state(state),.d_in(d_in),
								.d_out(d_out)); 
endmodule