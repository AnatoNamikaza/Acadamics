[org 0x0100]
jmp start
; extra space in the front of each string is because
; as we are taking input value from int 0x16 so the
; string is printed one charactor short in the start 
; of the string...

msg1: db ' hello world'
msg2: db ' hello world again'
msg3: db ' hello world again and again'

;------------------------------------------------
clrline:	; to clear a single line
push bp
push es
push ax
push di
mov ax, 0xb800
mov es, ax ; point es to video base
mov di, 3840
mov ax, 0x0720 ; space char in normal attribute
lp1:
mov [es:di], ax
add di, 2
cmp di, 4000
jne lp1
pop di
pop ax
pop es
pop bp
ret 
;------------------------------------------------------


start:
mov ah, 0 ; service 0 – get keystroke
int 0x16 ; call BIOS keyboard service

call clrline	; subroutine to clear the line

cmp al, 27	; Esc to exit program
je end
cmp al, 31h	; Press "1" to enter 1st msg
je cond1
cmp al, 32h	; Press "2" to enter 2nd msg
je cond2
cmp al, 33h	; Press "3" to enter 3rd msg
je cond3
jne start	; anyother key will not be accepted

cond1:
push cs
pop  es
mov bp, msg1 
mov cx, 12
jmp begin

cond2:
push cs
pop  es
mov bp, msg2
mov cx, 18
jmp begin

cond3:
push cs
pop  es
mov bp, msg3
mov cx,28
jmp begin

begin:
mov ah, 0x13
mov al, 1
mov bh, 0
mov bl, 0x07
mov dh, 0x19
mov dl, 0
int 0x10
jmp start

end:
mov ax, 0x4c00 ; terminate program
int 0x21