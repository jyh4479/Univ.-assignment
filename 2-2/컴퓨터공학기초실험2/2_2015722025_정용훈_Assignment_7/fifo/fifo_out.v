module fifo_out(state,data_count,full,empty,wr_ack,wr_err,rd_ack,rd_err); //The output of fifo
	input [2:0]state; //input
	input [3:0]data_count;
	output reg full,empty,wr_ack,wr_err,rd_ack,rd_err; //output reg

	parameter INIT=3'b000; //Declare parameter
	parameter NO_OP=3'b001;
	parameter WRITE=3'b010;
	parameter WR_ERROR=3'b011;
	parameter READ=3'b100;
	parameter RD_ERROR=3'b101;

always@(state) //When state change
begin //start option
	case(state) //case state
	INIT : begin //If the state is INIT
	wr_ack<=1'b0;wr_err<=1'b0;
	rd_ack<=1'b0;rd_err<=1'b0;
	full=0;
	empty=1;
	end

	NO_OP : begin //If the state is NO_OP
	wr_ack<=1'b0;wr_err<=1'b0;
	rd_ack<=1'b0;rd_err<=1'b0;
	full=0;empty=0;
	end

	WRITE : begin //If the state is WRITE
	wr_ack<=1'b1;wr_err<=1'b0;
	rd_ack<=1'b0;rd_err<=1'b0;
	full=0;
	empty=0;
	end

	WR_ERROR : begin //If the state is WR_ERROR
	wr_ack<=1'b0;wr_err<=1'b1;
	rd_ack<=1'b0;rd_err<=1'b0;
	full=1;
	empty=0;
	end

	READ : begin //If the state is READ
	wr_ack<=1'b0;wr_err<=1'b0;
	rd_ack<=1'b1;rd_err<=1'b0;
	full=0;
	empty=0;
	end

	RD_ERROR : begin //If the state is RD_ERROR
	wr_ack<=1'b0;wr_err<=1'b0;
	rd_ack<=1'b0;rd_err<=1'b1;
	full=0;
	empty=1;
	end

	default : begin //default
	wr_ack<=1'bx;wr_err<=1'bx;
	rd_ack<=1'bx;rd_err<=1'bx;
	full=1'bx;
	empty=1'bx;
	end
	endcase
end
endmodule