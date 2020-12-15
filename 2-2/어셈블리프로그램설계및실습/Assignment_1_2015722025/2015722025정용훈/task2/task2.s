	AREA ARMex, CODE, READONLY
	ENTRY
		
start
	MOV r0,#1 ;Save each value
	MOV r1,#2
	MOV r2,#3
	MOV r3,#4
	
	LDR r4, TEMPADDR1 ;Save the address of memory
	
	STRB r0,[r4] ;Save each value to memory
	STRB r1,[r4,#1]
	STRB r2,[r4,#2]
	STRB r3,[r4,#3]
	
	LDR r5,[r4] ;Load value from r4 to r5
	
	STRB r0,[r4,#3] ;Save each value to memory
	STRB r1,[r4,#2]
	STRB r2,[r4,#1]
	STRB r3,[r4]
	
	LDR r6,[r4] ;Load value from r4 to r6
	
	MOV pc, lr
TEMPADDR1 & &00001000
	END