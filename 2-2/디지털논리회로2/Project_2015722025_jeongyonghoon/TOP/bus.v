module BUS(clk, reset_n, M0_req, M0_wr, M0_address, M1_req, M1_wr, M1_address,M0_dout, M1_dout, S0_dout, S1_dout,S2_dout,S3_dout,
M0_grant, M1_grant, M_din, S0_sel,S1_sel,S2_sel,S3_sel, S_address, S_wr, S_din);//Declare module of bus

   input clk,reset_n,M0_req, M1_req,M0_wr,M1_wr; //inputs
   input [7:0] M0_address,M1_address;
   input [31:0] M0_dout,M1_dout,S0_dout,S1_dout,S2_dout,S3_dout;

   output M0_grant, M1_grant,S0_sel,S1_sel,S2_sel,S3_sel,S_wr; //outputs
   output [7:0] S_address;
   output [31:0] M_din,S_din;

   wire [3:0] w0_sel; //wire


//instance
bus_addr U0(.address(S_address), .S0_sel(S0_sel), .S1_sel(S1_sel),.S2_sel(S2_sel),.S3_sel(S3_sel));//The moudles of adress
bus_arbit U1(.clk(clk), .reset_n(reset_n),.M0_req(M0_req),.M1_req(M1_req),.M0_grant(M0_grant), .M1_grant(M1_grant)); //arbiter

////////////////mux////////////////
mux2 U2(.d0(M0_wr),.d1(M1_wr),.sel({M0_grant,M1_grant}),.dout(S_wr));
mux2_8bit U3(.d0(M0_address),.d1(M1_address),.sel({M0_grant,M1_grant}),.dout(S_address));
mux2_32bit U4(.d0(M0_dout),.d1(M1_dout),.sel({M0_grant,M1_grant}),.dout(S_din));
mux5_32bit U5(.d0(S0_dout), .d1(S1_dout), .d2(S2_dout),.d3(S3_dout),.d4(32'h0), .sel(w0_sel), .dout(M_din));

/////////// /flip flop/////////////
_dff_4_r U6(.clk(clk), .reset_n(reset_n), .d({S0_sel,S1_sel,S2_sel,S3_sel}), .q(w0_sel));

endmodule
