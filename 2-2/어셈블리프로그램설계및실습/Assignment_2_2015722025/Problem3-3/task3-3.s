	AREA ARMex, CODE, READONLY
		ENTRY

Main
	LDR r0, Address1 ;Load the memory
	LDR r1, =Arry ;Load the arry
	B Calculation ;go to Calculation

Calculation ;This calculation adds values sequentially
	LDR r3,[r1],#4 ;Load the data to r3 from r1
	ADD r2,r2,r3 ;r2=r2+r3
	LDR r3,[r1],#4
	ADD r2,r2,r3
	LDR r3,[r1],#4
	ADD r2,r2,r3
	LDR r3,[r1],#4
	ADD r2,r2,r3
	LDR r3,[r1],#4
	ADD r2,r2,r3
	LDR r3,[r1],#4
	ADD r2,r2,r3
	LDR r3,[r1],#4
	ADD r2,r2,r3
	LDR r3,[r1],#4
	ADD r2,r2,r3
	LDR r3,[r1],#4
	ADD r2,r2,r3
	LDR r3,[r1],#4
	ADD r2,r2,r3
	
	STR r2,[r0] ;Store the r2 to r0
	
	B Finish ;go to Finish
	
Finish
	MOV pc, lr

Arry DCD 11,13,15,17,19,21,23,25,27,29
Address1 & 0x0004000
	END