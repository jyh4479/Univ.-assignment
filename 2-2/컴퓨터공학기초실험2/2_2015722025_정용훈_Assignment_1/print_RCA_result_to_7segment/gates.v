module _xor2(a,b,y); //Name and factor declaration of module
input a, b; //Declare factor for using input
output y; //Declare factor for using output
wire inv_a, inv_b; //Set of value of output to input of other hardware
wire w0, w1; //Set of value of output to input of other hardware
_inv U0_inv(.a(a), .y(inv_a)); //Gets information from module and sets input and output
_inv U1_inv(.a(b), .y(inv_b)); //Gets information from module and sets input and output
_and2 U2_and2(.a(inv_a), .b(b), .y(w0)); //Gets information from module and sets input and output
_and2 U3_and2(.a(a),.b(inv_b), .y(w1)); //Gets information from module and sets input and output
_or2 U4_or2(.a(w0), .b(w1),.y(y)); //Gets information from module and sets input and output
endmodule //Declare module end

module _or2(a,b,y); //Name and factor declaration of module
input a,b; //Declare factor for using input
output y; //Declare factor for using output
assign y=a|b; //Entering Features for Hardware
endmodule //Declare module end

module _inv(a,y); //Name and factor declaration of module
input a; //Declare factor for using input
output y; //Declare factor for using output
assign y=~a; //Entering Features for Hardware
endmodule //Declare module end

module _and2(a,b,y); //Name and factor declaration of module
input a,b; //Declare factor for using input
output y; //Declare factor for using output
assign y=a&b; //Entering Features for Hardware
endmodule //Declare module end

module _nand2(a,b,y); //Name and factor declaration of module
input a,b; //Declare factor for using input
output y; //Declare factor for using output
assign y=~(a&b); //Entering Features for Hardware
endmodule //Declare module end



