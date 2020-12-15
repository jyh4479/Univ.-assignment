module write_operation(Addr,we,grant_signal); //Declare module of write logic

   input we; //inputs
   input [2:0] Addr;

   output [7:0] grant_signal;//output

   wire [7:0] check_signal;//wrie

_and2 U0(.a(we),.b(check_signal[0]),.y(grant_signal[0])); //and gates
_and2 U1(.a(we),.b(check_signal[1]),.y(grant_signal[1]));
_and2 U2(.a(we),.b(check_signal[2]),.y(grant_signal[2]));
_and2 U3(.a(we),.b(check_signal[3]),.y(grant_signal[3]));
_and2 U4(.a(we),.b(check_signal[4]),.y(grant_signal[4]));
_and2 U5(.a(we),.b(check_signal[5]),.y(grant_signal[5]));
_and2 U6(.a(we),.b(check_signal[6]),.y(grant_signal[6]));
_and2 U7(.a(we),.b(check_signal[7]),.y(grant_signal[7]));
_3_to_8_decoder U8(.d(Addr),.q(check_signal)); //Declare 3 to decoder

endmodule
