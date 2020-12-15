`timescale 1ns/100ps // set timescale

module tb_rca; //Declare the name of the module
reg [3:0] tb_a, tb_b; //4-bit Input Declaration
reg tb_ci; //Declare the input
wire [3:0] tb_s; //4-bit output Declaration
wire tb_co; //Declare the output
wire [4:0] tb_result; //5-bit output Declaration

rca U0_rca(.a(tb_a), .b(tb_b), .ci(tb_ci), .s(tb_s), .co(tb_co));
//Obtain information from the module to determine the correct input and output.

initial //Declare the program to run
begin //Start method
tb_a = 4'h0; tb_b = 4'h0; tb_ci = 0; //0000 , 0000 , 0 (the input value)
#10; tb_a = 4'h5; tb_b = 4'h4; // 0101 , 0100
#10; tb_a = 4'hF; tb_b = 4'hF; // 1111 , 1111
#10; tb_ci = 1; // 1 (the input value of ci)
#10; $stop; // stop the waveform
end //Method end
assign tb_result = {tb_co, tb_s};
endmodule //Indicates the end of the module
