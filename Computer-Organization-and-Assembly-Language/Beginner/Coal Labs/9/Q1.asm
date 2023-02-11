[org 0x100]
        jmp start
video:  times 2000 dw 0
prevptr: dd 0
;--------------------------------------------------------
sleep:	pusha
		mov cx, 0x0004
loop1:  mov dx, 0xFFFF
loop2:	dec dx
		jnz loop2
		loop loop1
		popa
		ret
;--------------------------------------------------------
Display:pusha
        in al, 0x60
        cmp al, 0x1E
        jne nextcmp
        call storeScreen
        call ClsScreen
l3:		in al, 0x60
        cmp al, 0x1E        
        je l3
nextcmp:cmp al, 0x9E
        jne nomatch
        call sleep
        call Restore
nomatch:popa
        jmp far [cs:prevptr]
exit:   mov al, 0x20
        out 0x20, al
        popa
        iret
;--------------------------------------------------------
storeScreen:
        pusha
        push es
        mov di, video
        push cs
        pop es
        push ds
        push 0xb800
        pop ds
        mov si, 0
        mov cx, 2000
		cld
		repnz movsw
		pop ds
        pop es
        popa
        ret 
;--------------------------------------------------------
Restore:pusha
        push es
        mov si, video
        push ds
        push cs
        pop ds
        push 0xb800
        pop es
        mov di, 0
        mov cx, 2000
		cld
		repnz movsw
		pop ds
        pop es
        popa
        ret
;--------------------------------------------------------
ClsScreen:
        pusha
        push 0xb800
        pop es
        mov di, 0
        mov ax, 0x0720
        mov cx, 2000
        cld
		repnz stosw
        popa
        ret
;--------------------------------------------------------
start:  xor ax, ax
        mov es, ax
        mov ax, [es:9*4]
        mov [prevptr], ax
        mov ax, [es:9*4+2]
        mov [prevptr+2], ax
        cli
        mov word [es:9*4], Display
        mov [es:9*4+2], cs
        sti
        mov dx, start
        add dx, 15
        mov cl, 4
        shr dx, cl
        mov ax, 0x3100
        int 0x21
;--------------------------------------------------------