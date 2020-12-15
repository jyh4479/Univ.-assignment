	AREA ARMex, CODE, READONLY
	ENTRY
	
start
	MOV r0, #10 ;Save 10 to r0
	MOV r1, #15 ;Save 15 to r1
	MOV r2, #8 ;Save 8 to r1
	
	MOV r4, #0 ;Declare resister for compare other value

	LDR r3, TEMPADDR1 ;Save the address of memory
	
	STRB r0,[r3] ;Save the value to memory
	STRB r1,[r3,#1]
	STRB r2,[r3,#2]
	
	LDRB r4,[r3] ;Load value from r3 to r4
	CMP r4, #10 ;Compare the value
	MOVGT r5,#1 ; > ;each condition
	MOVLT r5,#2 ; <
	MOVEQ r5,#3 ; =
	
	LDRB r4,[r3,#1] ;Load other value from r3 to r4
	CMP r4, #10 ;Compare the value
	MOVGT r5,#1 ;each condition
	MOVLT r5,#2
	MOVEQ r5,#3
	
	LDRB r4,[r3,#2] ;Load other value from r3 to r4
	CMP r4, #10 ;Compare the value
	MOVGT r5,#1 ;each condition
	MOVLT r5,#2
	MOVEQ r5,#3
	
	MOV pc, lr
TEMPADDR1 & &00001000 ;Decalre memory
	END