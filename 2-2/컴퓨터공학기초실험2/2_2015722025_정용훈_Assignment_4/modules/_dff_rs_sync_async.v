module _dff_rs_sync_async(clk, set_n, reset_n, d, q_sync, q_async); //The module has sync and async flip flop
	input clk, set_n, reset_n, d;
	output q_sync, q_async;
	
	_dff_rs_sync U0_dff_rs_sync(.clk(clk), //instance sync
		.set_n(set_n), .reset_n(reset_n),
		.d(d), .q(q_sync));
	_dff_rs_async U0_dff_rs_async0(.clk(clk), //instance async
		.set_n(set_n), .reset_n(reset_n),
		.d(d), .q(q_async));
		
endmodule