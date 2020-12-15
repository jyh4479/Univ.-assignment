	AREA Task2, CODE, READONLY
	ENTRY
main
	LDR sp, Address2 ;Load address
	LDR r10, Address1
	MOV r0,#10 ;save value to each register
	MOV r1,#11
	MOV r2,#12
	MOV r3,#13
	MOV r4,#14
	MOV r5,#15
	MOV r6,#16
	MOV r7,#17
	STMEA sp!,{r0-r7} ;storing data

doRegister ;function
	ADD r0,r0,#0 ;option of function
	ADD r1,r1,#1
	ADD r2,r2,#2
	ADD r3,r3,#3
	ADD r4,r4,#4
	ADD r5,r5,#5
	ADD r6,r6,#6
	ADD r7,r7,#7
 
doGCD ;function
	ADD r8,r8,r0 ;add all value of register
	ADD r8,r8,r1
	ADD r8,r8,r2
	ADD r8,r8,r3
	ADD r8,r8,r4
	ADD r8,r8,r5
	ADD r8,r8,r6
	ADD r8,r8,r7 ;for gcd
	MOV r9,#160
gcd ;loop for searching greatest common divisor
	CMP r8,r9
	SUBGT r8,r8,r9
	SUBLT r9,r9,r8
	BNE gcd

Finish ;for finishing program
	STR r8,[r10] ;Save gcd
	
	LDMEA sp!,{r8}
	ADD r7,r7,r8
	LDMEA sp!,{r8}
	ADD r6,r6,r8
	LDMEA sp!,{r8}
	ADD r5,r5,r8
	LDMEA sp!,{r8}
	ADD r4,r4,r8
	LDMEA sp!,{r8}
	ADD r3,r3,r8
	LDMEA sp!,{r8}
	ADD r2,r2,r8
	LDMEA sp!,{r8}
	ADD r1,r1,r8
	LDMEA sp!,{r8}
	ADD r0,r0,r8
	
	STMFA r10!,{r0-r7} ;Saveing value to memory
	
Address1 & 0x40000
Address2 & 0x41000
	
	END ;end program