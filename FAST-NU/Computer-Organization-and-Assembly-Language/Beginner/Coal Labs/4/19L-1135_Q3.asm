[org 0x0100]
jmp start

;------------------------------------------------
infiniteDisplay: 
push bp
push es
push ax
push di
mov ax, 0xb800
mov es, ax

l1: 
mov di, 0
add dl, 1
mov dh, 7
lp1:
mov [es:di], dx
add di, 2
cmp di, 4000
jne lp1
mov cx, 0xffff
l2:
sub cx, 1
cmp cx, 0
jne l2
mov cx, 0xffff
l3:
sub cx, 1
cmp cx, 0
jne l3
mov cx, 0xffff
l4:
sub cx, 1
cmp cx, 0
jne l4

jmp l1

pop di
pop ax
pop es
pop bp
ret 
;------------------------------------------------------
interrupt: 
mov ax, 0xffff 
mov bl, 2 
div bl 

ret
;------------------------------------------------------
start: 
xor ax, ax
mov es, ax 
mov word [es:0*4], infiniteDisplay 
mov [es:0*4+2], cs 
call interrupt 

mov ax, 0x4c00 ; terminate program
int 0x21 