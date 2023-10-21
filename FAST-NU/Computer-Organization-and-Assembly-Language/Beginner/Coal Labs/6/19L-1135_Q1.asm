[org 0x100]

	jmp start

Char:	dw 0x072A

;---------------------------------------
start:	xor ax, ax
	push es
	mov es, ax
	mov ax, [es:0*4]	; Saving interrupt's offset
	push ax
	mov ax, [es:0*4+2]
	push ax
	mov word [es:0*4], int0	; Overwriting interrupt's offset
	mov [es:0*4+2], cs

Type:	mov ah,00	
	mov al,03h	
	int 10h		
	mov ah, 0
	int 0x16
	cmp al, 27		; Press Lshift + e to exit
	je lev
	int 0x0			; calling interrupt
	jmp Type

lev:	pop word [es:0*4+2]	; Restoring interrupt's offset
	pop word [es:0*4]
	pop es

end:	mov ax, 0x4c00		; termination of program
	int 21h
;---------------------------------------
int0:	push 158;64		; column where char is printed vertically 
input:	in al, 0x60
	cmp al, 28		; Press "Enter" key to start interval
	je Go
	cmp al, 68		; Press "F-10" key to exit interrupt
	je exit0
	cmp al, 1		; Press "Esc" key to exit interrupt
	je exit0
	jmp input

Dis:	call DisChar
Go:	in al, 0x60
	cmp al, 68		; Press "F-10" key to end interval and
	je exit0		; exit interrupt
	cmp al, 1		; Press "Esc" key to end interval and
	je exit0		; exit interrupt
	mov ah, 0
	int 0x16
	cmp al, 26
	jne Dis
	jmp Go	

exit0:	out 0x20, al
	pop ax
	iret
;---------------------------------------
DisChar:
	push bp
	mov bp, sp
	pusha
	push es

	mov ax, [Char]
	
	mov bx, 0xb800
	mov es, bx
	mov di, [bp+4]
	mov [es:di], ax
	add di, 160
	mov [bp+4], di

	pop es
	popa
	pop bp
	ret
;---------------------------------------