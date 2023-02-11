[org 0x100]

	jmp start

lose:	dw 0
msg: db 'Your High Score:',0

;---------------------------------------
;Main body of the code for the program.
;---------------------------------------
start:	 
	mov al, 13h
	mov ah, 0
	int 10h 
	call Background
	mov ah, 0x2c
	int 21h
	push cx
	push dx
	push 176		;hurdle values
	push 100
	push 114		;movement values
	push 20
	call movement
	mov al, 3h
	mov ah, 0
	int 10h 
	mov ah, 0x2c
	int 21h
	push cx
	push dx
	pop eax
	pop ebx
	sub eax, ebx
	shr ax, 8
	push ax
	call printNum
end:mov ax, 0x4c00
	int 21h
;---------------------------------------
;Function for print number.
;---------------------------------------
printNum:push bp
	mov bp, sp
	push es
	pusha
	push 0xB800
	pop es
	mov ax, [bp + 4]
	mov di, 1826
	mov dh, 0x0a
	mov si, msg
msgDis:	mov dl, [si]
	cmp dl, 0
	je contine
	mov [es:di], dx
	add di, 2
	inc si
	jmp msgDis
contine:mov bx, 10
	xor cx, cx
nextDigit:xor dx, dx
	div bx
	add dl, 0x30
	push dx
	inc cx
	cmp ax, 0
	jnz nextDigit
	mov di, 2000
nextPos:pop dx
	mov dh, 0x0a
	mov [es:di], dx
	add di, 2
	loop nextPos
	popa
	pop es
	pop bp
	ret 2
;---------------------------------------
;Function for moving hurdles.
;---------------------------------------
MovH:	push bp
	mov bp, sp
	pusha
	mov word bx, [bp+8]
	dec bx
	cmp bx, 0
	jne reM
	mov bx, 320
reM:mov word [bp+8], bx
	popa
	pop bp
	ret
;---------------------------------------
;Function for slowing program execution.
;---------------------------------------
dslow:	push cx
	mov cx, 0x4fff	
ls:	dec cx
	jnz ls
	pop cx
	ret	
;---------------------------------------
;Function for slowing the motion of the
;dino figure.
;---------------------------------------
Mslow:	push cx
	mov cx, 0x2fff	
lsm:dec cx
	jnz lsm
	pop cx
	ret
;---------------------------------------
;Function for creating the background
;scenery of the game.
;---------------------------------------
Background:
	pusha
	mov dx, 0
;----Sky----
	mov al, 1111b
l1:	mov cx, 0
l2:	mov ah, 0ch
	int 10h 
	add cx, 1
	cmp cx, 320
	jne l2
	add dx, 1
	cmp dx, 200
	jne l1
;----Land----
	mov dx, 192
	mov al, 0000b
l3:	mov cx, 0
l4:	mov ah, 0ch
	int 10h 
	add cx, 1
	cmp cx, 320
	jne l4
	add dx, 1
	cmp dx, 193
	jne l3
	popa	
	ret
;---------------------------------------
;Function for creating the hurdles in
;the game.
;---------------------------------------
Hurdles:push bp
	mov bp, sp
	pusha
;----Hurdle#1----
	mov al, 1000b
	mov cx, [bp+8]		; column-wise pixel
	mov di, [bp+10]
	add di, 3
	mov bx, 2
H11:mov dx, di
H12:mov ah, 0ch
	int 10h 
	inc dx
	cmp dx, 191
	jb H12
	inc cx
	dec bx
	jnz H11
	mov cx, [bp+8]
	mov dx, di	
	mov bx, 5
	add dx, 10
	add cx, 1
b1:	sub dx, 1
	sub cx, 1
	mov ah, 0ch
	int 10h
	dec bx
	jnz b1
	mov cx, [bp+8]
	mov dx, di
	mov bx, 5
	add dx, 8
b2:	sub dx, 1
	add cx, 1
	mov ah, 0ch
	int 10h
	dec bx
	jnz b2
;----Hurdle#2----
	mov cx, [bp+8]
	add cx, 94
	mov si, cx
	mov bx, 2
	sub di, 9
H21:mov dx, di
H22:mov ah, 0ch
	int 10h 
	inc dx
	cmp dx, 191
	jb H22
	inc cx
	dec bx
	jnz H21
	mov cx, si
	mov dx, di	
	mov bx, 5
	add dx, 10
	add cx, 1
b3:	sub dx, 1
	sub cx, 1
	mov ah, 0ch
	int 10h
	dec bx
	jnz b3
	mov cx, si
	mov dx, di
	mov bx, 5
	add dx, 8
b4:	sub dx, 1
	add cx, 1
	mov ah, 0ch
	int 10h
	dec bx
	jnz b4
;----Hurdle#3----
	mov cx, [bp+8]
	add cx, 184
	mov si, cx
	mov bx, 2
	add di, 6
H31:mov dx, di
H32:mov ah, 0ch
	int 10h 
	inc dx
	cmp dx, 191
	jb H32
	inc cx
	dec bx
	jnz H31
	mov cx, si
	mov dx, di
	mov bx, 5
	add dx, 10
	add cx, 1
b5:	sub dx, 1
	sub cx, 1
	mov ah, 0ch
	int 10h
	dec bx
	jnz b5
	mov cx, si
	mov dx, di	
	mov bx, 5
	add dx, 8
b6:	sub dx, 1
	add cx, 1
	mov ah, 0ch
	int 10h
	dec bx
	jnz b6
	popa	
	pop bp
	ret
;---------------------------------------
;Function for clearing the Hurdles
;---------------------------------------
CHurdles:push bp
	mov bp, sp
	pusha
;----Hurdle#1----
	mov al, 1111b
	mov cx, [bp+8]		; column-wise pixel
	mov di, [bp+10]
	add di, 3
	mov bx, 2
C11:mov dx, di
C12:mov ah, 0ch
	int 10h 
	inc dx
	cmp dx, 191
	jb C12
	inc cx
	dec bx
	jnz C11
	mov cx, [bp+8]
	mov dx, di
	mov bx, 5
	add dx, 10
	add cx, 1
c1:	sub dx, 1
	sub cx, 1
	mov ah, 0ch
	int 10h
	dec bx
	jnz c1
	mov cx, [bp+8]
	mov dx, di
	mov bx, 5
	add dx, 8
c2:	sub dx, 1
	add cx, 1
	mov ah, 0ch
	int 10h
	dec bx
	jnz c2
;----Hurdle#2----
	mov cx, [bp+8]
	add cx, 94
	mov si, cx
	sub di, 9
	mov bx, 2
C21:mov dx, di
C22:mov ah, 0ch
	int 10h 
	inc dx
	cmp dx, 191
	jb C22
	inc cx
	dec bx
	jnz C21
	mov cx, si
	mov dx, di
	mov bx, 5
	add dx, 10
	add cx, 1
c3:	sub dx, 1
	sub cx, 1
	mov ah, 0ch
	int 10h
	dec bx
	jnz c3
	mov cx, si
	mov dx, di
	mov bx, 5
	add dx, 8
c4:	sub dx, 1
	add cx, 1
	mov ah, 0ch
	int 10h
	dec bx
	jnz c4
;----Hurdle#3----
	mov cx, [bp+8]
	add cx, 184
	mov si, cx
	add di, 6
	mov bx, 2
C31:mov dx, di
C32:mov ah, 0ch
	int 10h 
	inc dx
	cmp dx, 191
	jb C32
	inc cx
	dec bx
	jnz C31
	mov cx, si
	mov dx, di
	mov bx, 5
	add dx, 10
	add cx, 1
c5:	sub dx, 1
	sub cx, 1
	mov ah, 0ch
	int 10h
	dec bx
	jnz c5
	mov cx, si
	mov dx, di
	mov bx, 5
	add dx, 8
c6:	sub dx, 1
	add cx, 1
	mov ah, 0ch
	int 10h
	dec bx
	jnz c6
	popa	
	pop bp
	ret
;---------------------------------------
;Function for creating the
;Dino figure in the game.
;---------------------------------------
Char:push bp
	mov bp, sp
	pusha

	mov cx, [bp+4]	; column-wise pixel
	mov dx, [bp+6]	; row-wise pixel
;-----head--------
	mov di, dx
	add di, 5
	mov al, 0000b
	mov bx, 0
loop1:	mov ah, 0ch
	int 10h
loop2:	add dx, 1
	mov ah, 0ch
	int 10h
	cmp dx, di   ;height
	jne loop2
	add bx, 1        
	add cx, 1
	mov dx, [bp+6]
	cmp bx, 9	
	jne loop1
;-----body------
	mov cx, [bp+4]	; column-wise pixel
	mov dx, [bp+6]	; row-wise pixel
	mov bx, 0
	add cx, 1
	add dx, 4
	mov di, dx
	add di, 9
	mov si, cx	
loop3:	mov ah, 0ch
	int 10h
loop4:	add dx, 1
	mov ah, 0ch
	int 10h
	cmp dx, di
	jne loop4
	add bx, 1
	add cx, 1
	mov dx, [bp+6]
	add dx, 2
	cmp bx,	5
	jne loop3
;-----tail-----
	mov cx, [bp+4]	; column-wise pixel
	mov dx, [bp+6]	; row-wise pixel
	mov bx, 5
	add dx, 11
	add cx, 3
loop8:	sub dx, 1
	sub cx, 1
	mov ah, 0ch
	int 10h
	sub bx, 1
	cmp bx, 0
	jne loop8
	mov cx, [bp+4]	; column-wise pixel
	mov dx, [bp+6]	; row-wise pixel
	mov bx, 5
	add dx, 12
	add cx, 3
loop82:	sub dx, 1
	sub cx, 1
	mov ah, 0ch
	int 10h
	sub bx, 1
	cmp bx, 0
	jne loop82
	mov cx, [bp+4]	; column-wise pixel
	mov dx, [bp+6]	; row-wise pixel
	mov bx, 5
	add dx, 13
	add cx, 3
loop83:	sub dx, 1
	sub cx, 1
	mov ah, 0ch
	int 10h
	sub bx, 1
	cmp bx, 0
	jne loop83
;-----Leftleg-----
	mov cx, [bp+4]	; column-wise pixel
	mov dx, [bp+6]	; row-wise pixel
	mov bx, 4
	add dx, 12
	add cx, 2
loop10:	add dx, 1
	mov ah, 0ch
	int 10h
	sub bx, 1
	cmp bx, 0
	jne loop10
;-----Rightleg------
	mov cx, [bp+4]	; column-wise pixel
	mov dx, [bp+6]	; row-wise pixel
	mov bx, 4
	add dx, 12
	add cx, 5
loop11:	add dx, 1
	mov ah, 0ch
	int 10h
	sub bx, 1
	cmp bx, 0
	jne loop11
;-----left eye-----
	mov cx, [bp+4]	; column-wise pixel
	mov dx, [bp+6]	; row-wise pixel
	mov al, 1111b
	add cx, 3
	mov bx, 0
	add dx, 2
	mov ah, 0ch
	int 10h
;----mouth----
	mov cx, [bp+4]	; column-wise pixel
	mov dx, [bp+6]	; row-wise pixel
	add cx, 6
	add dx, 4
	mov ah, 0ch
	int 10h
	add cx, 1
	mov ah, 0ch
	int 10h
	add cx, 1
	mov ah, 0ch
	int 10h
Exs:	popa	
	pop bp
	ret 	
;---------------------------------------
;Function for clearing the
;Dino figure in the game.
;---------------------------------------
ClrDis:	push bp
	mov bp, sp
	pusha
	mov cx, [bp+4]	; column-wise pixel
	mov dx, [bp+6]	; row-wise pixel
;-----head--------
	mov di, dx
	add di, 5
	mov al, 1111b
	mov bx, 0
lop1:	mov ah, 0ch
	int 10h
lop2:	add dx, 1
	mov ah, 0ch
	int 10h
	cmp dx, di   ;height
	jne lop2
	add bx, 1        
	add cx, 1
	mov dx, [bp+6]
	cmp bx, 9	
	jne lop1
;-----body------
	mov cx, [bp+4]	; column-wise pixel
	mov dx, [bp+6]	; row-wise pixel
	mov bx, 0
	add cx, 1
	add dx, 4
	mov di, dx
	add di, 9
	mov si, cx	
lop3:	mov ah, 0ch
	int 10h
lop4:	add dx, 1
	mov ah, 0ch
	int 10h
	cmp dx, di
	jne lop4
	add bx, 1
	add cx, 1
	mov dx, [bp+6]
	add dx, 2
	cmp bx,	5
	jne lop3
;-----tail-----
	mov cx, [bp+4]	; column-wise pixel
	mov dx, [bp+6]	; row-wise pixel
	mov bx, 5
	add dx, 11
	add cx, 3
lop8:	sub dx, 1
	sub cx, 1
	mov ah, 0ch
	int 10h
	sub bx, 1
	cmp bx, 0
	jne lop8
	mov cx, [bp+4]	; column-wise pixel
	mov dx, [bp+6]	; row-wise pixel
	mov bx, 5
	add dx, 12
	add cx, 3
lop82:	sub dx, 1
	sub cx, 1
	mov ah, 0ch
	int 10h
	sub bx, 1
	cmp bx, 0
	jne lop82
	mov cx, [bp+4]	; column-wise pixel
	mov dx, [bp+6]	; row-wise pixel
	mov bx, 5
	add dx, 13
	add cx, 3
lop83:	sub dx, 1
	sub cx, 1
	mov ah, 0ch
	int 10h
	sub bx, 1
	cmp bx, 0
	jne lop83
;-----Leftleg-----
	mov cx, [bp+4]	; column-wise pixel
	mov dx, [bp+6]	; row-wise pixel
	mov bx, 4
	add dx, 12
	add cx, 2
lop10:	add dx, 1
	mov ah, 0ch
	int 10h
	sub bx, 1
	cmp bx, 0
	jne lop10
;-----Rightleg------
	mov cx, [bp+4]	; column-wise pixel
	mov dx, [bp+6]	; row-wise pixel
	mov bx, 4
	add dx, 12
	add cx, 5
lop11:	add dx, 1
	mov ah, 0ch
	int 10h
	sub bx, 1
	cmp bx, 0
	jne lop11
Exc:	popa	
	pop bp
	ret 
;---------------------------------------
;Function for movement of the
;Dino figure in the game.
;---------------------------------------
movement:push bp
	mov bp, sp
	pusha
	mov dx, [bp+10]	; row-wise pixel
	mov cx, [bp+8]	; column-wise pixel
	push dx
	push cx
	mov dx, [bp+6]	; row-wise pixel
	mov cx, [bp+4]	; column-wise pixel
	push dx
	push cx
AgainD:	call Char
	call Hurdles
	call LoseSet
	mov cx, [lose]
	cmp cx, 1
	je exitmov1
	call Mslow
	call Hurdles
	call dslow
	call CHurdles
	call MovH
Minput:	in al, 0x60
	cmp al, 1
	je exitmov1	
	cmp al, 57
	je Jumping
	call Hurdles
	call LoseSet
	mov cx, [lose]
	cmp cx, 1
	je exitmov1
	call dslow
	call CHurdles
	call MovH
	jmp Gravity
exitmov1:jmp exitmov
Jumping:mov bx, 20
j1:	call ClrDis
	pop cx
	pop dx
	sub dx, 3
	push dx
	push cx
	call Char
	call Hurdles
	call LoseSet
	mov cx, [lose]
	cmp cx, 1
	je exitmov1
	call dslow
	call CHurdles
	call MovH
	dec bx
	jnz j1
	jmp Gravity
Gravity:pop cx
	pop dx
	push dx
	push cx
	cmp dx, 133
	ja Minput
	mov bx, 30
j2:	call ClrDis
	pop cx
	pop dx
	add dx, 2
	push dx
	push cx
	call Char
	call Hurdles
	call LoseSet
	mov cx, [lose]
	cmp cx, 1
	je exitmov1
	call Hurdles
	call dslow
	call CHurdles
	call MovH
	dec bx
	jnz j2
	jmp AgainD
	
exitmov:call Hurdles
	pop ax
	pop ax
	pop ax
	pop ax
	popa	
	pop bp
	ret 8
;---------------------------------------
;Function for Checking if Dino has 
;hit any hurdle in the game.
;---------------------------------------
LoseSet:push bp
	mov bp, sp
	pusha
	mov dx, [bp+6]	; row-wise pixel
	mov cx, [bp+4]	; column-wise pixel
	mov bx, 8
	add dx, 8
L1:	inc cx
	mov ah, 0x0D
	int 0x10
	cmp al, 1000b
	je Lset
;	mov al, 1001b	;to make range visible
;	mov ah, 0ch
;	int 10h 
	dec bx
	jnz L1
	jmp loseexit
Lset:	mov cx, 1
	mov word [lose], cx	
loseexit:popa	
	pop bp
	ret		
;---------------------------------------