`timescale 1ns/100ps //timescale set

module tb_tl_cntr_w_left; //traffic-left logic testbench module

reg tb_clk,tb_reset_n,tb_Ta,tb_Tal,tb_Tb,tb_Tbl; //registers
wire[1:0] tb_La,tb_Lb; //wires

tl_cntr_w_left U0_tl_cntr_w_left(.clk(tb_clk),.reset_n(tb_reset_n),.Ta(tb_Ta),.Tal(tb_Tal),.Tb(tb_Tb),.Tbl(tb_Tbl),.La(tb_La),.Lb(tb_Lb));//instance traffic module

always #1.5 tb_clk=~tb_clk; //setting clock

initial //testbench
begin //start
tb_clk=0; tb_reset_n=1; tb_Ta=0; tb_Tb=0; tb_Tal=0; tb_Tbl=0;// initial set
#1 tb_Ta=1; tb_reset_n=0; //change variables
#3 tb_reset_n=1;
#3 tb_Tal=1; tb_Ta=0;
#3 tb_Tal=0; tb_Tb=1;
#3 tb_Tb=0; tb_Tbl=1;
#3 tb_Tbl=0; tb_Ta=1;
#3 tb_Tal=1; tb_Ta=0;
#3 tb_Tal=0; tb_Tb=1; tb_reset_n=0; //checking reset one more
#3 tb_Tb=0; tb_Tbl=1; tb_reset_n=1;
#3 tb_Tbl=0; tb_Ta=1; tb_Tal=1;
#3 tb_Ta=0; tb_Tb=1; 
#3 tb_Ta=1; tb_Tal=0;
#3 tb_Tbl=1;
#12 tb_Tb=0; 
#9 tb_Tbl=0;
#7 $stop; //stop 
end //end
endmodule
