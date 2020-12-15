module print_RCA_result_to_7segment(a, b, cin, dec_out); //Name and factor declaration of module
input [3:0] a; //4-bit Input Declaration
input [3:0] b; //4-bit output Declaration
input cin; //Declare the input
output [13:0]dec_out; //14-bit output Declaration

wire[3:0] s; //4-bit output Declaration
wire c; //Declare output

rca U0_rca(.a(a), .b(b), .ci(cin), .s(s), .co(c)); //Import information from another module to determine the value
seg_dec U1_seg_dec(.iHex(s), .oSEG7(dec_out[6:0])); //Import information from another module to determine the value
seg_dec U2_seg_dec(.iHex({3'b000,c}), .oSEG7(dec_out[13:7])); //Import information from another module to determine the value

endmodule //Declare end of module
