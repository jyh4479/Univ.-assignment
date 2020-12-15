	AREA ARMex, CODE, READONLY
	ENTRY
	
start
	LDR r0, Address1 ;Load address
	MOV r1, #1 ;Save 1 to r1
	MOV r2, r1, lsl #1 ;r2=1*2
	add r3, r2,r2, lsl #1 ;r3=r2*3
	MOV r4, r3, lsl #2 ;r4=r3*4
	add r5, r4,r4, lsl #2 ;r5=r4*5
	
	rsb r6, r5,r5,lsl#2 ;r6=r5*6
	MOV r6, r6,lsl#1
	
	rsb r7, r6,r6,lsl#3 ;r7=r6*7
	MOV r8, r7 ,lsl#3 ;r8=r7*8
	add r9,r8,r8,lsl#3;r9=r8*9
	
	add r10, r9,r9,lsl#3;r10=r9*10
	add r10, r10,r9
	
	STR r10,[r0] ;Save information
	
	MOV pc, lr
Address1 & 0x40000 ;Declare address
	END
		
		
		