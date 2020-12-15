	AREA blockData, CODE, READONLY
	ENTRY

start
	LDR sp, Address1 ;Load address

	MOV r0, #0 ;Save each value at register
	MOV r1, #1
	MOV r2, #2
	MOV r3, #3
	MOV r4, #4
	MOV r5, #5
	MOV r6, #6
	MOV r7, #7
	
	STMEA sp!,{r0-r7} ;Store value in memory
	
	LDMEA sp!, {r5} ;Load data from memory
	LDMEA sp!, {r4}
	LDMEA sp!, {r3}
	LDMEA sp!, {r7}
	LDMEA sp!, {r2}
	LDMEA sp!, {r0}
	LDMEA sp!, {r6}
	LDMEA sp!, {r1}
	
Address1 & 0x40000 ;Declare address
	END