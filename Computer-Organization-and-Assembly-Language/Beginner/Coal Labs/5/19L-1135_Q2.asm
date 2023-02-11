[org 0x100]



	jmp start

GreatestCommonDivisor:
	div bx
	cmp dx, 0
	je exiting
l1:	mov ax, bx
	mov bx, dx
	mov dx, 0
	div bx
	cmp dx, 0
	je exiting
	jmp l1
	
exiting:mov ax, bx
	mov bx, 0
	iret

start:	xor ax, ax
	mov es, ax

	mov word [es:128*4], GreatestCommonDivisor 
	mov [es:128*4+2], cs 
	mov ax, 91
	mov bx, 14
	int 0x80

end:	mov ax, 0x4c00
	int 0x21
