`timescale 1ns/100ps // set timescale

module tb_ha; //Declare the name of the module
reg tb_a, tb_b; //Determine the input of a module.
wire tb_s, tb_co; //Determine the output of a module.

ha U0_ha(.a(tb_a), .b(tb_b), .s(tb_s), .co(tb_co));
//Obtain information from the module to determine the correct input and output.

initial //Declare the program to run
begin //Start method
tb_a = 0; tb_b = 0; //Enter 0 in a and 0 in b
#10; tb_a = 0; tb_b = 1; //Wait for the declared time then Enter 0 in a and 1 in b
#10; tb_a = 1; tb_b = 0; //Wait for the declared time then Enter 1 in a and 0 in b
#10; tb_a = 1; tb_b = 1; //Wait for the declared time then Enter 1 in a and 1 in b
#10; $stop; //Wait for the declared time 
end //Method end
endmodule //Indicates the end of the module