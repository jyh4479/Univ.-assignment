	AREA ARmex, CODE, ReADONLY
		ENTRY

Main
	LDR r0, Address1 ;Load the memory
	LDR r1, =Arry ;Load the arry
	
	LDR r2,[r1],#36 ;Declaration of storage from the back
	B Loop ;go Loop
Loop
	LDR r2,[r1],#-4 ;Load information from the back sequentially
	STRB r2,[r0],#1 ;Save to memory
	CMP r2, #10 ;Compare the value for ending of program
	BEQ Finish ;If equal go Finish
	BNE Loop ;If not equal go Loop
	
Finish
	MOV pc, lr
	
Arry DCD 10,9,8,7,6,5,4,3,2,1
Address1 & 0x0004000
	END