[org 0x100]

    jmp start

;---------------------------------------
TimeFrmt:
    push 0xB800
    pop es

    push bp
    mov bp, sp

    mov di, [bp+2]
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
    pop bp
    mov al, 0x20
	out 0x20, al    	
    jmp lt
;---------------------------------------
start:  xor ax, ax
		mov es, ax
	    cli
	    push word [es:0x0*4]    ; Saving interrupt's offset
	    push word [es:0x0*4+2]
	    mov word [es:0x0*4], int0    ; Overwriting interrupt's offset
	    mov [es:0x0*4+2], cs
	    sti
	    int 0x0        ; calling interrupt

lev:  	pop word [es:0x0*4+2]    ; Restoring interrupt's offset
		pop word [es:0x0*4]

end:    mov ax, 0x4c00        ; termination of program
    	int 21h
;---------------------------------------
int0:   pusha
	    push es

	    push 158        
	    call clrscr
    
lt:     in al, 0x60
    	cmp al, 1
    	je exit0
    	cmp al, 1
    	jne TimeFrmt
    	jmp lt    
    
exit0:  pop ax
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
