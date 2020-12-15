module fifo_cal(state,head,tail,data_count,we,re,next_head,next_tail,next_data_count); //fifo calculator
	input [2:0]state,head,tail; //input
	input [3:0]data_count;
	output reg we,re; //output reg
	output reg[2:0]next_head,next_tail;
	output reg[3:0]next_data_count;
	
	parameter INIT = 3'b000; //declare parameter
	parameter NO_OP = 3'b001;
	parameter WRITE = 3'b010;
	parameter WR_ERROR = 3'b011;
	parameter READ = 3'b100;
	parameter RD_ERROR = 3'b101;

	always@(state,head,tail,data_count) //practice the option according to each parameter when change
	begin //start option
		case(state) //case state
		INIT : begin //if sate is INIT
			next_head=3'b000;
			next_tail=3'b000;
			next_data_count=4'b0000;
			we=1'b0;
			re=1'b0;
		end

		READ : begin //if state is READ
			next_head=head+3'b001;
			next_tail=tail;
			next_data_count=data_count-4'b0001;
			we=1'b0;
			re=1'b1;
		end

		WRITE : begin //if state is WRITE
			next_head=head;
			next_tail=tail+3'b001;
			next_data_count=data_count+4'b001;
			we=1'b1;
			re=1'b0;
		end

		NO_OP : begin //if state is NO_OP
			next_head=head;
			next_tail=tail;
			next_data_count=data_count;
		end

		WR_ERROR : begin //if state is WR_ERROR
		next_head=head;
			next_tail=tail;
			next_data_count=data_count;
			we=1'b0;
			re=1'b0;
		end

		RD_ERROR : begin //if state is RD_ERROR
		next_head=head;
			next_tail=tail;
			next_data_count=data_count;
			we=1'b0;
			re=1'b0;
		end

		default	:	begin //Defalut option
			next_head = 3'bx;
			next_tail = 3'bx;
			next_data_count = 4'bx;
			we = 1'bx;
			re = 1'bx;
		end
		endcase
	end
endmodule