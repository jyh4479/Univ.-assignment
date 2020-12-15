module fifo_ns(wr_en,rd_en,state,data_count,next_state); //fifo next state
	input wr_en,rd_en; //input
	input [2:0]state;
	input [3:0]data_count;
	output reg[2:0]next_state; //output

	parameter INIT = 3'b000; //Declare parameter
	parameter NO_OP = 3'b001;
	parameter WRITE = 3'b010;
	parameter WR_ERROR = 3'b011;
	parameter READ = 3'b100;
	parameter RD_ERROR = 3'b101;

always@(wr_en,rd_en,state,data_count) //practice the option according to each parameter when change
begin //start option
	case(state) //case state
		INIT : //If the state is INIT
		begin //Declare next state
		if(wr_en==1'b1)
			begin
			if(rd_en==1'b0) next_state<=WRITE;
			else if(rd_en==1'b1) next_state<=NO_OP;
			end
		else if(wr_en==1'b0)
			begin
			if(rd_en==1'b0) next_state<=NO_OP;
			else if(rd_en==1'b1) next_state<=RD_ERROR;
			end
		end

		READ : //If the state is READ
		begin //Declare next state
		if(wr_en==1'b1)
			begin
			if(rd_en==1'b00) next_state<=WRITE;
			else if(rd_en==1'b1) next_state<=NO_OP;
			end
		else if(wr_en==1'b0)
			begin
			if(rd_en==1'b0) next_state<=NO_OP;
			else if(rd_en==1'b1&&data_count>4'b0000) next_state<=READ;
			else next_state=RD_ERROR;
			end
		end

		RD_ERROR : //If the state is RD_ERROR
		begin //Declare next state
		if(wr_en==1'b1)
			begin
			if(rd_en==1'b0) next_state<=WRITE;
			else if(rd_en==1'b1) next_state<=NO_OP;
			end
		else if(wr_en==1'b0)
			begin
			if(rd_en==1'b0) next_state<=NO_OP;
			else if(rd_en==1'b1) next_state<=RD_ERROR;
			end
		end

		NO_OP : //If the state is NO_OP
		begin //Declare next state
		if(wr_en==1'b1)
			begin
			if(rd_en==1'b0&&data_count<4'b1000) next_state<=WRITE;
			else if(rd_en==1'b1) next_state<=NO_OP;
			else next_state<=WR_ERROR;
			end
		else if(wr_en==1'b0) 
			begin
			if(rd_en==1'b0) next_state<=NO_OP;
			else if(rd_en==1'b1&&data_count>4'b0000) next_state<=READ;
			else next_state<=RD_ERROR;
			end
		end

		WRITE : //If the state is WRITE
		begin //Declare next state
		if(wr_en==1'b1)
			begin
			if(rd_en==0&&data_count<4'b1000) next_state<=WRITE;
			else if(rd_en==1'b1) next_state<=NO_OP;
			else next_state<=WR_ERROR;
			end
		else if(wr_en==1'b0) 
			begin
			if(rd_en==1'b0) next_state<=NO_OP;
			else if(rd_en==1'b1) next_state<=READ;
			end
		end

		WR_ERROR : //If the state is WR_ERROR
		begin //Declare next state
		if(wr_en==1'b1)
			begin
			if(rd_en==1'b0) next_state<=WR_ERROR;
			else if(rd_en==1'b1) next_state<=NO_OP;
			end
		else if(wr_en==1'b0)
			begin
			if(rd_en==1'b0) next_state<=NO_OP;
			else if(rd_en==1'b1) next_state<=READ;
			end
		end
		endcase
	end
endmodule

