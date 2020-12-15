module ha(a,b,s,co); //declare module's name and variables of input and output
input a,b; //decalre the input of hardware
output s,co; //declare the output of hardware
_xor2 U0_xor2(.a(a), .b(b), .y(s)); //Obtain information from xor gate to determine input and output of module ha
_and2 U1_and2(.a(a), .b(b), .y(co));//Obtain information from xor gate to determine input and output of module ha
endmodule //end the module's method

