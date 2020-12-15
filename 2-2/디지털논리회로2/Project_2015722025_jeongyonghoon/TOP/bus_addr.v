module bus_addr(address,S0_sel,S1_sel,S2_sel,S3_sel);//Declare module of bust address

   input [7:0] address;//input
   output reg S0_sel,S1_sel,S2_sel,S3_sel;//Declare slave select



always@(address) //practice the function when chnage address
begin

if((address>=8'h00)&&(address<8'h20))begin //check address
S0_sel=1'b1; //Declare signal of address
S1_sel=1'b0;
S2_sel=1'b0;
S3_sel=1'b0;
end

else if((address>=8'h20)&&(address<8'h40))begin //Same as above
S0_sel=1'b0;
S1_sel=1'b1;
S2_sel=1'b0;
S3_sel=1'b0;
end

else if((address>=8'h40)&&(address<8'h60))begin //Same as above
S0_sel=1'b0;
S1_sel=1'b0;
S2_sel=1'b1;
S3_sel=1'b0;
end

else if((address>=8'h60)&&(address<8'h80))begin //Same as above
S0_sel=1'b0;
S1_sel=1'b0;
S2_sel=1'b0;
S3_sel=1'b1;
end

else begin //Same as above
S0_sel=1'b0;
S1_sel=1'b0;
S2_sel=1'b0;
S3_sel=1'b0;
end

end
endmodule
