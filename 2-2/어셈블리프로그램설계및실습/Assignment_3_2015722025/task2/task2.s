	AREA ARMex, CODE, READONLY
		ENTRY

start
	LDR r0,Address1 ;Load address
	MOV r1,#1; ;Save 1 to r1
	MOV r11,#2; ;Save 2 to r11
	
	mul r2,r1,r11 ;r2=1*2
	add r11,r11,#1 ;r11=3
	mul r3,r2,r11 ;r3=r2*3
	add r11,r11,#1 ;r11=4
	mul r4,r3,r11 ;r4=r3*4
	add r11,r11,#1 ;r11=5
	mul r5,r4,r11 ;r5=r4*5
	add r11,r11,#1 ;r11=6
	mul r6,r5,r11 ;r6=r5*6
	add r11,r11,#1 ;r11=7
	mul r7,r6,r11 ;r7=r6*7
	add r11,r11,#1 ;r11=8
	mul r8,r7,r11 ;r8=r7*8
	add r11,r11,#1 ;r11=9
	mul r9,r8,r11 ;r9=r8*9
	add r11,r11,#1 ;r11=10
	mul r10,r9,r11 ;r10=r9*10
	
	STR r10,[r0] ;Save information
	
	MOV pc,lr

Address1 & 0x40000 ;Declare address
	end