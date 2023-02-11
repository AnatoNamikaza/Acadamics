[org 0x100]



	jmp start

msg1: db ' Hi, You pressed a.'
msg2: db ' Hi, You pressed b.'
msg3: db ' Hi, You entered wrong credentials.'

start:	mov ah, 0

	int 16h
	mov ah, 00
	mov al, 03h

	int 10h
	mov ah, 0

	int 16h
	cmp al, 'a'
	je cond1
	cmp al, 'b'
	je cond2
	jmp cond3

cond1:	push cs
	pop  es
	mov bp, msg1 
	mov cx, 19
	jmp begin

cond2:	push cs
	pop  es
	mov bp, msg2
	mov cx, 19
	jmp begin

cond3:	push cs
	pop  es
	mov bp, msg3
	mov cx, 35
	jmp begin

begin:	mov ah, 0x13
	mov al, 1
	mov bh, 0
	mov bl, 0x07
	mov dh, 0x19
	mov dl, 0
	int 0x10

end:	mov ax, 0x4c00
	int 0x21
