module TOP(clk, reset_n, M0_req, M0_wr, M0_address, M0_dout, M0_grant, M1_grant, M_din, m_interrupt,multi_opdone);//module of TOP

   input clk, reset_n; //inputs
   input M0_req, M0_wr;
   input [7:0]M0_address;
   input [31:0]M0_dout;


   output M0_grant, M1_grant; //outputs
   output[31:0]M_din;
   output m_interrupt, multi_opdone;

   wire M1_req, M1_wr; //wires
   wire [7:0]M1_address;
   wire [31:0]M1_dout;

   wire S0_sel, S1_sel, S2_sel, S3_sel, S_wr;

   wire [7:0]S_address;
   wire [31:0]S0_dout, S1_dout, S2_dout, S3_dout, S_din;

	// bus
	BUS U0_bus (
		.clk(clk),
		.reset_n(reset_n),
		.M0_req(M0_req),
		.M0_wr(M0_wr),
		.M0_address(M0_address),
		.M0_dout(M0_dout),
		.M1_req(M1_req),
		.M1_wr(M1_wr),
		.M1_address(M1_address),
		.M1_dout(M1_dout),
		.S0_dout(S0_dout),
		.S1_dout(S1_dout),
		.S2_dout(S2_dout),
		.S3_dout(S3_dout),
		.M0_grant(M0_grant),
		.M1_grant(M1_grant),
		.M_din(M_din),
		.S0_sel(S0_sel),
		.S1_sel(S1_sel),
		.S2_sel(S2_sel),
		.S3_sel(S3_sel),
		.S_address(S_address),
		.S_wr(S_wr),
		.S_din(S_din)
	);
	
	// M1, S0 (0x00 ~ 0x0F)
	MATRIX_Top U1_MATRIX(
	.clk(clk), 
	.reset_n(reset_n),
	.S_sel(S0_sel), 
	.S_wr(S_wr),
	.S_address(S_address),
	.S_din(S_din),
	.S_dout(S0_dout), 
	.m_interrupt(m_interrupt),
	.M1_wr(M1_wr),
	.M1_req(M1_req),
	.M1_address(M1_address),
	.M1_dout(M1_dout),
	.M_din(M_din),
	.multi_done(multi_opdone)
	);

	// ram (A matrix)
	// S1 (0x10 ~ 0x1F)
	ram U2_A (
		.clk(clk),
		.cen(S1_sel),
		.wen(S_wr),
		.addr(S_address[4:0]),
		.din(S_din),
		.dout(S1_dout)
	);

	// ram (B matrix)
	// S2 (0x20 ~ 0x3F)
	ram U3_B (
		.clk(clk),
		.cen(S2_sel),
		.wen(S_wr),
		.addr(S_address[4:0]),
		.din(S_din),
		.dout(S2_dout)
	);

	// ram (A*B Matrix)
	// S3 (0x40 ~ 0x5F)
	ram U4_result (
		.clk(clk),
		.cen(S3_sel),
		.wen(S_wr),
		.addr(S_address[4:0]),
		.din(S_din),
		.dout(S3_dout)
	);
endmodule