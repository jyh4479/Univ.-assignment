	AREA Floatingpoint, CODE, READONLY
	ENTRY


	LDR r12, =Matrix_data ;load data
	LDR r13, TEST_data ;load memory for saving data
	
	LDR r9,Savecount
	LDR r10,[r12],#4 ;n
	LDR r11,[r12],#4 ;k
	MOV r0,r10
	MOV r14,#1 ;for calculate counting
	STR r14,[r9,#20]
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;row;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
firstload4 ;first load
	LDR r1,[r12],#4 ;load data of dat
	LDR r2,[r12],#4
	STR r1,[r13],#4
	B cal4 ;call calulation

load4
	MOV r1,r2 ;change dat
	LDR r2,[r12],#4
cal4
	;CMP r1,r2 ;compare two float value
	;BEQ CMPNUM 
	;MOV r3,r1,LSL #1
	;MOV r4,r2,LSL #1
	;CMP r3,r4
	;BEQ Savevalue ;when the result is zero
CMPNUM4
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
	ADD r5,r5,#8388608 ;ADD 1 to mantisa
	ADD r6,r6,#8388608	
	CMP r7,r8 ;compare exponent
	SUBGT r9,r7,r8
	SUBLT r9,r8,r7 ;shift num	
	MOVGT r6,r6,LSR r9 ;if shift num is not 0
	MOVLT r5,r5,LSR r9	
	MOVLE r7,r8		
	CMP r3,r4
	BEQ EQADD4
NEADD4
	MOV r8,r1,lsl #1
	MOV r9,r2,lsl #1
	MOV r8,r8,lsr #1
	MOV r9,r9,lsr #1
	CMP r8,r9
	MOVEQ r7,#0 ;when the result is zero
	BEQ savefloat4
	SUBGT r5,r5,r6 
	SUBLT r5,r6,r5	
	;MOVGT r3,r3
	MOVLT r3,r4;Declare sign

loop4 ;for normalize
	CMP r5,#8388608
	MOVLT r5,r5,lsl #1
	SUBLT r7,r7,#1
	BLT loop4
	B Finish4


EQADD4	
	ADD r5,r5,r6 ;adding mantissa
	CMP r5,#16777216
	MOVGE r5,r5,LSR #1
	ADDGE r7,r7,#1	

Finish4
	SUB r5,r5,#8388608
	SUB r7,r7,#1 ;/2
	ADD r7,r5,r7,lsl #23
	ADD r7,r7,r3,lsl #31

savefloat4
	STR r7,[r13],#4 ;save data
	STR r2,[r13],#4
	
	ADD r14,r14,#1 ;calculation count
	CMP r14,r0 ;compare counting
	BNE load4
	
	
	LDR r9,Savecount ;load memry for saving count
	LDR r4,[r9,#20]
	CMP r11,r4
	BEQ padding6

nonpadding4
	MOV r14,#1 ;initialize calculation count


	LDR r5,[r9]
	ADD r5,r5,#1 ;increase count
	STR r5,[r9]
		
	CMP r5,r10 ;check calculation number of one row
	BNE firstload4 ;change row
	
	MOV r3,#0
	STR r3,[r9] ;initialize padding count
	MOV r0,r0,LSL #1
	SUB r0,r0,#1 ;next calculate count
	
	CMP r4,#1
	LDREQ r12,TEST_data
	LDREQ r13,TEST_data2
	
	LDRNE r12,TEST_data2
	LDRNE r13,TEST_data3
	
	ADD r4,r4,#1
	STR r4,[r9,#20]
	
	B firstload4

	
	
padding6
	MOV r14,#1 ;initialize cal count

	LDR r9,Savecount
	LDR r5,[r9]
	ADD r5,r5,#1
	STR r5,[r9]
	
	CMP r11,#2
	STR r2,[r13],#4 ;padding
	STREQ r2,[r13],#4
	STREQ r2,[r13],#4
	STRGT r2,[r13],#4
	STRGT r2,[r13],#4
	STRGT r2,[r13],#4
	STRGT r2,[r13],#4
	STRGT r2,[r13],#4
	STRGT r2,[r13],#4
	
	
	CMP r5,r10
	MOVEQ r0,#0
	STREQ r0,[r9] ;initialize padding count
	BEQ setting
	
	B firstload4




;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;column;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
setting
	STR r14,[r9,#20];initialize k count
	
	CMP r11,#2
	LDRLT r12,TEST_data
	LDRLT r13,Result_data
	
	LDREQ r12,TEST_data2
	LDREQ r13,TEST_data4
	
	LDRGT r12,TEST_data3
	LDRGT r13,TEST_data4
	
	MOV r0,r10,LSL #3 ;for making next pointer number n * 4
	MOVEQ r0,r0,LSL #1
	MOVGT r0,r0,LSL #2
	
	CMP r11,#2
	MOV r6,r10,LSL#1 ;column calculate
	MOVEQ r6,r6,LSL#1
	MOVGT r6,r6,LSL#2
	STR r6,[r9,#12]
	
column4
	STR r12,[r9,#4] ;for next column pointer
	STR r13,[r9,#8] ;for next column pointer
	
	;CMP r11,#2
	;MOV r6,r10,LSL#1 ;column calculate
	;MOVEQ r6,r6,LSL#1
	;MOVGT r6,r6,LSL#2
	;STR r6,[r9,#12]
	
	
Cfirstload4
	LDR r1,[r12],r0
	LDR r2,[r12],r0
	STR r1,[r13],r0
	B Ccal4

Cload4
	MOV r1,r2
	LDR r2,[r12],r0
	
Ccal4
	;CMP r1,r2 ;compare two float value
	;BEQ CMPNUM 
	;MOV r3,r1,LSL #1
	;MOV r4,r2,LSL #1
	;CMP r3,r4
	;BEQ Savevalue ;when the result is zero
CCMPNUM4
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
	ADD r5,r5,#8388608 ;ADD 1 to mantisa
	ADD r6,r6,#8388608	
	CMP r7,r8 ;compare exponent
	SUBGT r9,r7,r8
	SUBLT r9,r8,r7 ;shift num	
	MOVGT r6,r6,LSR r9 ;if shift num is not 0
	MOVLT r5,r5,LSR r9	
	MOVLE r7,r8		
	CMP r3,r4
	BEQ CEQADD4
CNEADD4
	MOV r8,r1,lsl #1
	MOV r9,r2,lsl #1
	MOV r8,r8,lsr #1
	MOV r9,r9,lsr #1
	CMP r8,r9
	MOVEQ r7,#0 ;when the result is zero
	BEQ Csavefloat4
	SUBGT r5,r5,r6 
	SUBLT r5,r6,r5	
	;MOVGT r3,r3
	MOVLT r3,r4;Declare sign

Cloop4 ;for normalize
	CMP r5,#8388608
	MOVLT r5,r5,lsl #1
	SUBLT r7,r7,#1
	BLT Cloop4
	B CFinish4


CEQADD4	
	ADD r5,r5,r6 ;adding mantissa
	CMP r5,#16777216
	MOVGE r5,r5,LSR #1
	ADDGE r7,r7,#1	

CFinish4
	SUB r5,r5,#8388608
	SUB r7,r7,#1 ;result of mid point
	ADD r7,r5,r7,lsl #23
	ADD r7,r7,r3,lsl #31
	
Csavefloat4
	STR r7,[r13],r0
	STR r2,[r13],r0
	
	ADD r14,r14,#1 ;cal count
	CMP r14,r10
	BNE Cload4
	
	LDR r9,Savecount ;load memry for saving count
	LDR r4,[r9,#20]
	CMP r11,r4
	BEQ Cpadding6

Cnonpadding4
	MOV r14,#1 ;initialize cal count

	LDR r5,[r9] ;load count
	ADD r5,r5,#1
	STR r5,[r9]
	
	LDR r12,[r9,#4];for calculating next column
	LDR r13,[r9,#8]
	ADD r12,r12,#4
	ADD r13,r13,#4
	STR r12,[r9,#4]
	STR r13,[r9,#8]
	
	LDR r6,[r9,#12]
	CMP r5,r6
	BNE Cfirstload4
	
	MOV r7,#0
	STR r7,[r9] ;initialize padding count
	

	LDR r12,TEST_data4
	CMP r11,#2 ;check value of k
	LDRNE r13,TEST_data5
	LDREQ r13,Result_data
	
	CMP r4,#2
	LDREQ r12,TEST_data5 ;when k 3
	LDREQ r13,Result_data
	
	MOV r10,r10,LSL#1 ;chnage data of N
	SUB r10,r10,#1
		
	ADD r4,r4,#1
	STR r4,[r9,#20]
	B column4
	
	
Cpadding6
	MOV r14,#1 ;initialize cal count

	LDR r9,Savecount ;load data of count
	LDR r5,[r9]
	ADD r5,r5,#1
	STR r5,[r9]
	
	CMP r11,#2
	STR r2,[r13],r0 ;padding
	STREQ r2,[r13],r0
	STREQ r2,[r13],r0
	STRGT r2,[r13],r0
	STRGT r2,[r13],r0
	STRGT r2,[r13],r0
	STRGT r2,[r13],r0
	STRGT r2,[r13],r0
	STRGT r2,[r13],r0
	
	LDR r12,[r9,#4];for calculating next column
	LDR r13,[r9,#8]
	ADD r12,r12,#4
	ADD r13,r13,#4
	STR r12,[r9,#4]
	STR r13,[r9,#8]
	
	
	MOV r5,r5,LSL #2 ;Because of unit
	CMP r5,r0
	
	BNE Cfirstload4
	MOV pc,#0 ;Program end
	
	
		
Result_data & 0x60000000
TEST_data4 & 0x80000
TEST_data5 & 0x90000

TEST_data3 & 0x60000
TEST_data2 & 0x50000
TEST_data & 0x40000
Savecount & 0x70000

	AREA data
Matrix_data ;The area of data
	;DCD 3
	;DCD 1
	;DCD 2_01000010110111000000000000000000
	;DCD 2_01000011011110000000000000000000
	;DCD 2_11000001100000000000000000000000
	;DCD 2_11000010101010000000000000000000
	;DCD 2_11000001010110000000000000000000
	;DCD 2_01000000011111000000000000000000
	;DCD 2_10111110101101000000000000000000
	;DCD 2_01000010011100000000000000000000
	;DCD 2_11000100010000000000000000000000
	
	;DCD 3
	;DCD 2
	;DCD 2_01000010011010000000000000000000
	;DCD 2_10111111111101000000000000000000
	;DCD 2_11000000110000000000000000000000
	;DCD 2_11000010111000000000000000000000
	;DCD 2_01000011000000000000000000000000
	;DCD 2_01000010001011000000000000000000
	;DCD 2_01000011110001000000000000000000
	;DCD 2_01000011011100000000000000000000
	;DCD 2_01000001101000000000000000000000

	
	;DCD 2
	;DCD 3
	;DCD 2_01000000000000100000000000000000
	;DCD 2_11000000111000000000000000000000
	;DCD 2_01000011100000100000000000000000
	;DCD 2_01000001100010000000000000000000	
	END