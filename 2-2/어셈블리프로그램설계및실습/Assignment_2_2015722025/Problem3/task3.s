	AREA ARMex, CODE, READONLY
		ENTRY
		
Main
	LDR r0, Address1 ;Load the memory
	MOV r1,#1 ;r1=1
	
	lsl r3,r1,#1
	lsl r3,r3,#1
	ADD r3,r3,#1
	lsl r3,r3,#1
	ADD r3,r3,#1 ;make number of 11 to r3
	
	ADD r4,r3,#1
	ADD r4,r4,#1
	ADD r4,r4,#1
	lsl r4,r4,#1
	ADD r4,r4,#1 ;make number of 29 to r4
	
	B Loop ;go to Loop
	
Loop
	ADD r5,r5,r3 ;r5=r5+r3
	CMP r3,r4 ;compare the r3 and r4
	BEQ Finish ;if equal, go to Finish
	ADD r3,r3,#1 ;r3=r3+2
	ADD r3,r3,#1
	BNE Loop ;if not equal, go to Loop
Finish
	STR r5,[r0] ;store the information
	MOV pc, lr
	
Address1 & 0x00004000
	END