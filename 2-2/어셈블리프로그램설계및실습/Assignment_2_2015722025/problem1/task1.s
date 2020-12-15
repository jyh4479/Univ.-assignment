	AREA ARMex, CODE, READONLY
		ENTRY

Main
	LDR r0, =Char1 ;Load the String for comparing
	LDR r1, =Char2
	LDR r2, Address1 ;Load the memory for saving
	MOV r3, #10 ;The number is going to used for checking
	MOV r4, #11

Strcmp
	LDRB r8, [r0],#1 ;Load the character
	LDRB r9, [r1],#1
	CMP r8, r9 ;compare the character
	BNE Different ;if the character is different, go to Different
	BEQ Check ;if the character is same, go to Check

Check
	CMP r8, #0 ;For checking end of string
	BEQ Equal ;If end, go Equal
	BNE Strcmp ;If not end, go Strcmp

Equal
	STR r3, [r2] ;Save the r3 to r2
	B Finish ;go Finish
	
Different
	STR r4, [r2] ;Save the r4 to r2
	B Finish ;go Finish

Finish
	MOV pc, lr

Char1 DCB "aca",0
Char2 DCB "aaa",0
	
Address1 & 0x00004000
	END