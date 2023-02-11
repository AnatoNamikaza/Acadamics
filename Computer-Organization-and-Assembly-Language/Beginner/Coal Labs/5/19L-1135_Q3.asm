[org 0x100]



	jmp start

Correction:
	pop ax
	add ax, 2
	push ax
	mov ax, 0
	mov dx, 0
	iret

start:	xor ax, ax
	mov es, ax

	mov word [es:0*4], Correction
	mov [es:0*4+2], cs 
	mov ax, 8
	mov bx, 0
	div bx

end:	mov ax, 0x4c00
	int 0x21
