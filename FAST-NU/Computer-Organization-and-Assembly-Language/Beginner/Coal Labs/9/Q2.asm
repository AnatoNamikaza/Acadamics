[org 0x100]
        jmp start
msg: db 'print$'
video:  times 2000 dw 0
prevptr: dd 0
;--------------------------------------------------------
sleep:  pusha
        mov cx, 0x0016
loop1:  mov dx, 0xFFFF
loop2:  dec dx
        jnz loop2
        loop loop1
        popa
        ret
;--------------------------------------------------------
Display:pusha
        mov dx, msg
        mov ah, 9
        int 21h
        popa
        ret
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
printa: call storeScreen
        call ClsScreen
        call Display
        call sleep
        call Restore
        ret
;--------------------------------------------------------
start:  call printa
        mov ax, 0x4c00
        int 0x21
;--------------------------------------------------------