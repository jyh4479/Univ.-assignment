	AREA Floatingpoint, CODE, READONLY
	ENTRY

start
	LDR r0,Address1
	LDR r1,float1 ;value
	LDR r2,float2
	LDR r10,mantissa ;for adding 1 to mantissa and comparing
	
	CMP r1,r2 ;compare two float value
	BEQ CMPNUM 
	MOV r3,r1,LSL #1
	MOV r4,r2,LSL #1
	CMP r3,r4
	BEQ Savevalue ;when the result is zero
	
CMPNUM
	MOV r3,r1,LSR #31;Declare S1
	MOV r4,r2,LSR #31;Declare S2
	
	MOV r5,r1,LSL #9;Declare Mantissa F1
	MOV r5,r5,LSR #9
	MOV r6,r2,LSL #9;F2
	MOV r6,r6,LSR #9
	
	MOV r7,r1,LSL #1
	MOV r7,r7,LSR #24 ;E1
	MOV r8,r2,LSL #1
	MOV r8,r8,LSR #24 ;E2
	
	ADD r5,r5,r10 ;ADD 1 to mantisa
	ADD r6,r6,r10
	
	CMP r7,r8 ;compare exponent
	SUBGT r9,r7,r8
	SUBLT r9,r8,r7 ;shift num
	
	CMP r7,r8
	MOVGT r6,r6,LSR r9 ;if shift num is not 0
	MOVLT r5,r5,LSR r9
	
	CMP r7,r8 ;compare exponent
	MOVGT r13,r7
	MOVLE r13,r8
	
	CMP r3,r4
	BEQ EQADD
	B NEADD
	
EQADD	
	ADD r5,r5,r6 ;adding mantissa
	ADD r10,r10,r10
	CMP r5,r10
	MOVGT r5,r5,LSR #1
	ADDGT r13,r13,#1
	
	B Finish
NEADD	
	CMP r5,r6 ;mantisa
	SUBGT r5,r5,r6
	SUBLT r5,r6,r5
	
	MOV r1,r1,lsl #1
	MOV r2,r2,lsl #1
	
	CMP r1,r2 ;Declare sign
	MOVGT r3,r3
	MOVLT r3,r4
	
	MOV r9,#0
loop ;for normalize
	CMP r10,r5
	MOVGT r5,r5,lsl #1
	ADDGT r9,r9,#1
	BGT loop
	
	SUBNE r13,r13,r9 ;exponent
	
Finish
	LDR r10, mantissa
	
	SUB r5,r5,r10
	
	MOV r3,r3,lsl #31
	MOV r13,r13,lsl #23
	
	ADD r11,r13,r3
	ADD r11,r11,r5 ;result
	
Savevalue
	STR r11,[r0] ;save the value to memory
	MOV pc,lr
	

float1 & 0x3FC00000 ;1.5
float2 & 0x40500000 ;3.25
;float1 & 0xC2680000 ;-58
;float2 & 0x426C0000 ;59
;float2 & 0x42680000 ;58
;float2 & 0x41C00000;24
;float1 & 0x426C0000;59
;float2 & 0x3FC00000
;float1 & 0x40500000
mantissa & 0x00800000
Address1 & 0x40000 ;Declare address
	END