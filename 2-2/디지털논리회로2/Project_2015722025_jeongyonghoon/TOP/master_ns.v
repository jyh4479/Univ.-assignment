module master_ns(count,rAddr,m_interrupt,S_sel,S_wr,op_clear,M1_address,next_count,next_M1_address); //Declare next sate of master

   input m_interrupt,S_sel,S_wr,op_clear; // inputs
   input [7:0] M1_address;
   input [2:0] rAddr,count;

   output reg [2:0] next_count; // outputs, regs
   output reg [7:0] next_M1_address;

   wire [7:0] add_address; //wire

   parameter zero=3'b000;//Declare count of parameter
   parameter one=3'b001;
   parameter two=3'b010;
   parameter three=3'b011;
   parameter four=3'b100;
   parameter five=3'b101;
   parameter six=3'b110;
   parameter seven=3'b111;

always@(count or m_interrupt or S_sel or S_wr or op_clear or M1_address or add_address) // always condition
begin
case(count)
zero : begin
   if(op_clear==1'b1) begin //check clear
      next_count<=3'b0;
      next_M1_address<=8'b00000000;
      end

   else if(m_interrupt==1'b0) begin //check interrupt
      next_count<=3'b0;
      next_M1_address<=8'b00000000;
      end

   else begin //else
      next_count<=3'b001;
      next_M1_address<=8'b01100000;
      end
    end


one : begin
         if(op_clear==1'b1) begin //check clear
            next_count<=1'b0;
            next_M1_address<=8'b00000000;
            end

         else if(S_wr==1'b0) begin //check write enable
            next_count<=count;
            next_M1_address<=8'b01100000;
            end

         else begin //else
            next_count<=3'b010;
            next_M1_address<=8'b00000110;
            end
         end


two : begin
         if(op_clear==1'b1) begin //check clear
            next_count<=1'b0;
            next_M1_address<=8'b00000000;
            end

         else begin //else
            next_count<=3'b011;
            next_M1_address<=8'b01100001;
            end
      end


three : begin
         if(op_clear==1'b1) begin //check clear
            next_count<=1'b0;
            next_M1_address<=8'b00000000;
            end

         else begin //else
            next_count<=3'b100;
            next_M1_address<=8'b00000110;
            end
      end


four : begin
         if(op_clear==1'b1) begin //check clear
            next_count<=1'b0;
            next_M1_address<=8'b00000000;
            end

         else begin //else
            next_count<=3'b101;
            next_M1_address<=8'b01100010;
            end
      end


five : begin
         if(op_clear==1'b1) begin //check clear
            next_count<=1'b0;
            next_M1_address<=8'b00000000;
            end

         else begin //else
            next_count<=3'b110;
            next_M1_address<=8'b00000110;
            end
      end


six : begin
         if(op_clear==1'b1) begin //check clear
            next_count<=1'b0;
            next_M1_address<=8'b00000000;
            end

         else begin //else
            next_count<=3'b111;
            next_M1_address<=8'b01100011;
            end
      end


seven : begin
         if(op_clear==1'b1) begin //check clear
            next_count<=1'b0;
            next_M1_address<=8'b00000000;
            end

         else begin //else
            next_count<=3'b000;
            next_M1_address<=8'b00000000;
            end
      end
endcase
end
endmodule




