[org 0x100]

    jmp start

video:  times 2000 dw 0
prevptr: dd 0
;--------------------------------------------------------
Display:pusha
        in al, 0x60
        cmp al, 0x1D
        jne nextcmp
        call storeScreen
        call ClsScreen
nextcmp:cmp al, 0x9D
        jne nomatch
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
        push 0xb800
        pop es
        mov cx, 2000
        mov di, 0
        mov bx, video
        
ls:     mov ax, word [es:di]
        mov word [cs:bx+di], ax
        add di, 2
        loop ls
        pop es
        popa
        ret 
;--------------------------------------------------------
Restore:pusha
        push es
        push 0xb800
        pop es
        mov di, 0
        mov si, 0
        mov bx, video
        mov cx, 2000
ld:     mov ax, word [cs:bx+si]
        mov word [es:di], ax
        add di, 2
        add si, 2
        loop ld
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
        rep stosw
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