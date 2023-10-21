[org 0x100]

    jmp start

Str1: db 'He has food and drinks',0
Str2: db 'has',0
Str3: db 'and',0
prevptr: dd 0
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
StrLen: push bp
        mov bp, sp
        pusha
        mov di, [bp+4]
        mov bx, di
l1:     cmp byte [cs:di], 0
        je eLen
        inc di
        jmp l1
eLen:   sub di, bx
        mov word [bp+6], di
        popa
        pop bp
        ret 2
;--------------------------------------------------------
DetectionIndex:
        push bp
        mov bp, sp
        pusha
        mov bx, 0
resec:  mov di, [bp+8]
        mov si, [bp+6]
chk:    mov al, byte [cs:si]
        cmp al, byte [cs:di+bx]
        jne ser
        inc di
        inc si
        cmp byte [cs:si], 0
        je FInx
        cmp byte [cs:di+bx], 0
        je NEInx
        jmp chk
ser:    inc bx
        jmp resec
NEInx:  mov word [bp+4], -1     
EInx:   popa
        pop bp
        ret 
FInx:   mov word [bp+4], bx
        jmp EInx        
;--------------------------------------------------------
strD:   push bp
        mov bp, sp
        pusha
        push es
        push 0xb800
        pop es
        push 0
        push word [bp+4]
        call StrLen
        pop dx
        mov dh, al
        mov bx, 0
        mov di, 2000
        mov si, [bp+6]
        mov ah, 0x07
pr:     mov al, [cs:si+bx]
        cmp al, 0
        je Dexit
        cmp bl, dh
        je ndPrint
        mov [es:di], ax
        add di, 2
        inc bx
        jmp pr
ndPrint:mov cl, dl
        add bl, dl
ndI:    dec bx
        mov al, [cs:si+bx]
        mov [es:di], ax
        add di, 2
        dec cx
        jnz ndI
        add bl, dl
        jmp pr
Dexit:  pop es
        popa
        pop bp
        ret 4
;--------------------------------------------------------
Display:pusha
        push 0xb800
        pop es
        in al, 0x60
        cmp al, 0x2a
        jne nextcmp
        push Str1
        push Str3
        push 0
        call DetectionIndex
        pop ax
        cmp ax, -1
        je Fexit
        call strD
nextcmp:cmp al, 0xaa
        jne nextcmp1
        call ClsScreen
nextcmp1:cmp al, 0x36
        jne nextcmp2
        push Str1
        push Str2
        push 0
        call DetectionIndex
        pop ax
        cmp ax, -1
        je Fexit
        call strD
nextcmp2:cmp al, 0xb6
        jne nomatch
        call ClsScreen
nomatch:popa
        jmp far [cs:prevptr]
Fexit:  mov al, 0x20
        out 0x20, al
        popa
        iret
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