[org 0x0100]
jmp start
;------------------------------------------------
printKey: push ax
pop bx ; bx=ax
push es
push ax
push cx
push di
mov ax, 0xb800
mov es, ax ; point es to video base
xor di, di ; point di to top left column
mov al, bl
mov ah, 0x07 ; normal attribute
mov cx, 2000 ; number of screen locations
cld ; auto increment mode
rep stosw ; clear the whole screen
pop di
pop cx
pop ax
pop es
ret
;------------------------------------------------
start: mov ah, 0 ; service 0 – get keystroke
int 0x16 ; call BIOS keyboard service
cmp al, 27
je end
call printKey ; clear the screen
jmp start

end:
mov ax, 0x4c00 ; terminate program
int 0x21