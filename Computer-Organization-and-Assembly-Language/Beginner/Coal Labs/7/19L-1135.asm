[org 0x0100]

;---------Data for Program--------------------------------

            jmp main
    
;---------Code Implementation of Program------------------
;---------------------------------------------------------
slow:       pusha               ;slowing movement
            mov cx, 0x2fff    
l2:         loopnz l2
            popa
            ret
;---------------------------------------------------------
Print:  pusha
        push es
        push ds

        mov ax, 0xB800
        mov es, ax
        mov ds, ax
        mov bx, 3198
        mov dx, 3358
        
        std
restart:mov cx, 2000        
        add bx, 160
        add dx, 160
        cmp bx, 4000
        ja reset3
        cmp dx, 4000
        ja reset4
l3:     mov si, bx
        mov di, dx
        mov word ax, [ds:si]
        mov word [es:di], ax
l1:     sub si, 2
        sub di, 2
        mov word ax, [ds:si]
        mov word [es:di], ax
G1:     mov ah,1
        int 0x16
        cmp al, 27
        je exitfun

        cmp si, 0
        je reset1
        cmp di, 0
        je reset2
        loopnz l1
        call slow


        jmp restart

reset1: mov si, 4000
        jmp l1
reset2: mov di, 4000
        jmp l1

reset3: sub bx, 4000
        jmp l3
reset4: sub dx, 4000
        jmp l3

exitfun:pop ds
        pop es
        popa

        ret 
        
;-----------------Main code-------------------------------
main:   call Print

end:    mov ax, 0x4c00
        int 0x21


