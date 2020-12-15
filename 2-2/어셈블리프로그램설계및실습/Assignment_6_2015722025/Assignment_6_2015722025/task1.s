	AREA strcpy, CODE, READONLY
	ENTRY

main ;main
	LDR r0,Address ;load address
	LDR r1,=string1 ;load data of string
	
copy
	LDRB r2,[r1],#1 ;load string
	STRB r2,[r0],#1 ;save string
	CMP r2, #0 ;compare end of string
	BNE copy ;loop
	
	mov pc,lr

string1 DCB "Hello",0
Address & 0x40000 ;Declare address
	END