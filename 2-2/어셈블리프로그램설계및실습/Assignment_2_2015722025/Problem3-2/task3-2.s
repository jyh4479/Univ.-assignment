	AREA ARMex, CODE, READONLY
		ENTRY

Main
	LDR r0, Address1
	MOV r1, #1 ;For making number of 10
	MOV r2, #10 ;The number of element
	
	ADD r1,r1,#1
	lsl r1,r1,#1
	ADD r1,r1,#1
	lsl r1,r1,#1 ;make number of 10
	
	B Calculation ;go to Calculation

Calculation
	ADD r3,r2,r1 ;r3=r2+r1
	MUL r4,r3,r2 ;r4=r3*r2
	STR r4,[r0] ;store the r4 to r0
	
	MOV pc, lr

Address1 & 0x0004000
	END