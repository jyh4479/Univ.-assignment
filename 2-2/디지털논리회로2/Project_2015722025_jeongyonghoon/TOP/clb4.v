module clb4(a,b,ci,c1,c2,c3,co);//Declare cla block

   input [3:0] a,b;//inputs
   input ci;

   output c1,c2,c3,co; //outputs

   wire [3:0] g,p;//wires
   wire w0_c1;
   wire w0_c2, w1_c2;
   wire w0_c3, w1_c3, w2_c3;
   wire w0_co, w1_co, w2_co, w3_co;


_and2 U0_and2(.a(a[0]),.b(b[0]),.y(g[0])); // calculate Generate
_and2 U1_and2(.a(a[1]),.b(b[1]),.y(g[1]));
_and2 U2_and2(.a(a[2]),.b(b[2]),.y(g[2]));
_and2 U3_and2(.a(a[3]),.b(b[3]),.y(g[3]));

_or2 U0_or(.a(a[0]),.b(b[0]),.y(p[0])); // calculate Propergate
_or2 U1_or(.a(a[1]),.b(b[1]),.y(p[1]));
_or2 U2_or(.a(a[2]),.b(b[2]),.y(p[2]));
_or2 U3_or(.a(a[3]),.b(b[3]),.y(p[3]));


/////////////calculate each C/////////////
_and2 U4_and2(.a(p[0]),.b(ci),.y(w0_c1));
_or2 U4_or(.a(w0_c1),.b(g[0]),.y(c1));

_and2 U5_and2(.a(p[1]),.b(g[0]),.y(w0_c2));
_and3 U0_and3(.a(p[1]),.b(p[0]),.c(ci),.y(w1_c2));
_or3 U0_or3(.a(w0_c2),.b(w1_c2),.c(g[1]),.y(c2));

_and2 U6_and2(.a(p[2]),.b(g[1]),.y(w0_c3));
_and3 U1_and3(.a(p[2]),.b(p[1]),.c(g[0]),.y(w1_c3));
_and4 U0_and4(.a(p[2]),.b(p[1]),.c(p[0]),.d(ci),.y(w2_c3));
_or4 U0_or4(.a(g[2]),.b(w0_c3),.c(w1_c3),.d(w2_c3),.y(c3));

_and2 U7_and2(.a(p[3]),.b(g[2]),.y(w0_co));
_and3 U2_and3(.a(p[3]),.b(p[2]),.c(g[1]),.y(w1_co));
_and4 U1_and4(.a(p[3]),.b(p[2]),.c(p[1]),.d(g[0]),.y(w2_co));
_and5 U0_and5(.a(p[3]),.b(p[2]),.c(p[1]),.d(p[0]),.e(ci),.y(w3_co));
_or5 U0_or5(.a(g[3]),.b(w0_co),.c(w1_co),.d(w2_co),.e(w3_co),.y(co));

endmodule


