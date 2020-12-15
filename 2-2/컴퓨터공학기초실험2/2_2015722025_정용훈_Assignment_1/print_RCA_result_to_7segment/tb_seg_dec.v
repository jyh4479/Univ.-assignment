`timescale 1ns/100ps // set timescale

module tb_seg_dec; //Declare the name of the module
reg [3:0] tb_a; ///4-bit Input Declaration
wire [6:0] tb_y; ///4-bit Output Declaration

seg_dec U0_seg_dec(.iHex(tb_a), .oSEG7(tb_y));
//Obtain information of seven-segment and set input and output.

initial //Run the command that determines the value
begin //Notifies the start of a method
tb_a = 4'h0;  // input a:0000
#10; tb_a = 4'h4; //input a:0100
#10; tb_a = 4'hE; //input a:1110
#10; tb_a = 4'h2; //input a:0010 
#10; tb_a = 4'h7; //input a:0111
#10; tb_a = 4'hB; //input a:1011
#10; $finish; // after 10ns and end
end //Notify end of method

endmodule //end of module