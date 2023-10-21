[org 0x100]

    jmp start

;---------------------------------------
TimeFrmt:
	pusha
	push es

    push 0xB800
    pop es

    mov di, 158
    mov bx, 16

    xor ax, ax    
    mov al, 4
    out 0x70, al        ; Load hours in "al" register
    jmp h1
h1: in al, 0x71
    push ax
    xor ax, ax    
    mov al, 2    
    out 0x70, al        ; Load minutes in "al" register
    jmp m1    
m1: in al, 0x71
    push ax
    xor ax, ax    
    mov al, 0    
    out 0x70, al        ; Load seconds in "al" register
    jmp s1    
s1: in al, 0x71
    div bl
    
    mov cx, 3

dis:
    mov dl, ah
    add dl, 0x30
    mov dh, 0x0c    
    mov [es:di], dx
    sub di, 2
    add al, 0x30
    mov dl, al
    mov [es:di], dx
    sub di, 2
    sub cx, 1
    cmp cx, 0
    je levfun
    mov dl, ":"
    mov [es:di], dx
    sub di, 2
    mov dx, 0
    pop ax
    div bl
    jmp dis    

levfun:    
    pop es
    popa
    ret
;---------------------------------------
start:	push 0x0000
		pop es
		cli
		mov word [es:8 * 4], int0
		mov [es:8 * 4 + 2], cs
		sti

		mov dx, start
		add dx, 15
		mov cl, 4
		shr dx, cl
		mov ah, 0x31
		int 0x21
;---------------------------------------
int0:   pusha
	    push es
	    call clrscr
	    call TimeFrmt
	    mov al, 0x20
 		out 0x20, al
		pop es
        popa
        iret
;---------------------------------------
clrscr:	pusha
		mov ah,00	
		mov al,03h						; interrupt to clear screen
		int 10h	

		popa	
		ret
;---------------------------------------
