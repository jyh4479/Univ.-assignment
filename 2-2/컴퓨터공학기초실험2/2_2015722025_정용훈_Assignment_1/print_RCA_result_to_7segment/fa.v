module fa(a,b,ci,s,co); //Name the module and specify the number of factors
input a,b,ci; //Declare factors for input
output s,co; //Declare factors for output
wire c1,c2,sm; //Set of value of output to input of other hardware
ha U0_ha(.a(a),.b(b),.s(sm),.co(c1)); //Gets information from module and sets input and output
ha U1_ha(.a(sm),.b(ci),.s(s),.co(c2)); //Gets information from module and sets input and output
_or2 U2_or2(.a(c1),.b(c2),.y(co)); //Gets information from module and sets input and output
endmodule //Declare module end