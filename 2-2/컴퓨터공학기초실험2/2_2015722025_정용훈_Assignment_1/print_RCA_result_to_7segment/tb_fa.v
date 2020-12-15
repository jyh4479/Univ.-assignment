`timescale 1ns/100ps // set timescale

module tb_fa; //Declare the name of the module
reg tb_a, tb_b, tb_ci; //Declare input to module
wire tb_s, tb_co; //Output declaration for module

fa U0_fa(.a(tb_a), .b(tb_b), .ci(tb_ci), .s(tb_s), .co(tb_co));
//Obtain information of Fulladder and set input and output.

initial //Run the command that determines the value
begin //Notifies the start of a method

tb_a = 0; tb_b = 0; tb_ci = 0; //Enter the 0 to a, b and ci
#10; tb_a = 0; tb_b = 0; tb_ci = 1; //Wait for the set amount of time then set 0,0,1
#10; tb_a = 0; tb_b = 1; tb_ci = 0; //Wait for the set amount of time then set 0,1,0
#10; tb_a = 0; tb_b = 1; tb_ci = 1; //Wait for the set amount of time then set 0,1,1
#10; tb_a = 1; tb_b = 0; tb_ci = 0; //Wait for the set amount of time then set 1,0,0
#10; tb_a = 1; tb_b = 0; tb_ci = 1; //Wait for the set amount of time then set 1,0,1
#10; tb_a = 1; tb_b = 1; tb_ci = 0; //Wait for the set amount of time then set 1,1,0
#10; tb_a = 1; tb_b = 1; tb_ci = 1; //Wait for the set amount of time then set 1,1,1
#10; $stop; //Wait for the set amount of time then stop the program

end //Notify end of method
endmodule //Notify end of module