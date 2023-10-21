[org 0x100]

	jmp start

Win:	dw 0
Left:   dw 0
Right:	dw 0
Down:	dw 0

;---------------------------------------
;Main body of the code for the program.
;---------------------------------------
start:	 
	mov al, 13h
	mov ah, 0
	int 10h 
	call Background
	push 70
	call Hurdles
	push 280
	call FlagPole
	push 124
	push 20
	call movement
;	mov al, 03h
;	mov ah, 0
;	int 10h 

	pop ax
	pop ax
	
end:mov ax, 0x4c00
	int 21h
;---------------------------------------
;Function for creating the background
;scenery of the game.
;---------------------------------------
Background:
	pusha
	mov dx, 0
;----Sky----
	mov al, 1001b
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
	mov dx, 195
	mov al, 0010b
l3:	mov cx, 0
l4:	mov ah, 0ch
	int 10h 
	add cx, 1
	cmp cx, 320
	jne l4
	add dx, 1
	cmp dx, 200
	jne l3

	popa	
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
;Mario figure.
;---------------------------------------
Mslow:	push cx
	mov cx, 0x6fff	
lsm:dec cx
	jnz lsm
	pop cx
	ret
;---------------------------------------
;Function for creating the hurdles in
;the game.
;---------------------------------------
Hurdles:push bp
	mov bp, sp
	pusha

;----Hurdle#1----
	mov cx, [bp+4]	; column-wise pixel
	mov bx, cx
	add bx, 10
	mov si, cx
	mov di, bx
	add si, 1
	sub di, 2
	mov al, 0110b

U1h1:	mov dx, 165	; row-wise pixel
U1h2:	cmp dx, 170
	je ski11
	cmp dx, 170
	ja l1h1

	mov ah, 0ch
	int 10h 
ski11:	add dx, 1
	cmp dx, 195
	jne U1h2
	jmp ski12
	
l1h1:	cmp cx, si
	jb ski12	
	cmp cx, di
	ja ski12	
	mov ah, 0ch
	int 10h
	add dx, 1
	cmp dx, 195
	jne U1h2

ski12:	add cx, 1
	cmp cx, bx
	jne U1h1

;----Hurdle#2----
	mov cx, [bp+4]
	add cx, 54
	mov bx, cx
	add bx, 10
	mov si, cx
	mov di, bx
	add si, 1
	sub di, 2
U2h1:	mov dx, 135	; row-wise pixel
U2h2:	cmp dx, 140
	je ski21
	cmp dx, 140
	ja l2h1

	mov ah, 0ch
	int 10h 
ski21:	add dx, 1
	cmp dx, 195
	jne U2h2
	jmp ski22
	
l2h1:	cmp cx, si
	jb ski22	
	cmp cx, di
	ja ski22	
	mov ah, 0ch
	int 10h
	add dx, 1
	cmp dx, 195
	jne U2h2

ski22:	add cx, 1
	cmp cx, bx
	jne U2h1

;----Hurdle#3----
	mov cx, [bp+4]
	add cx, 124
	mov bx, cx
	add bx, 10
	mov si, cx
	mov di, bx
	add si, 1
	sub di, 2
U3h1:	mov dx, 174	; row-wise pixel
U3h2:	cmp dx, 179
	je ski31
	cmp dx, 179
	ja l3h1

	mov ah, 0ch
	int 10h 
ski31:	add dx, 1
	cmp dx, 195
	jne U3h2
	jmp ski32
	
l3h1:	cmp cx, si
	jb ski32	
	cmp cx, di
	ja ski32	
	mov ah, 0ch
	int 10h
	add dx, 1
	cmp dx, 195
	jne U3h2

ski32:	add cx, 1
	cmp cx, bx
	jne U3h1

;----Hurdle#4----
	mov cx, [bp+4]
	add cx, 181
	mov bx, cx
	add bx, 10
	mov si, cx
	mov di, bx
	add si, 1
	sub di, 2
U4h1:	mov dx, 152	; row-wise pixel
U4h2:	cmp dx, 157
	je ski41
	cmp dx, 157
	ja l4h1
	mov ah, 0ch
	int 10h 
ski41:	add dx, 1
	cmp dx, 195
	jne U4h2
	jmp ski42
	
l4h1:	cmp cx, si
	jb ski42	
	cmp cx, di
	ja ski42	
	mov ah, 0ch
	int 10h
	add dx, 1
	cmp dx, 195
	jne U4h2

ski42:	add cx, 1
	cmp cx, bx
	jne U4h1
	
	popa	
	pop bp
	ret 2
;---------------------------------------
;Function for creating the flag in
;the game.
;---------------------------------------
FlagPole:push bp
	mov bp, sp
	pusha

;----Flag----
	mov cx, [bp+4]	; column-wise pixel
	mov bx, cx
	add bx, 22
	mov si, cx
	mov di, bx
	add si, 1
	sub di, 2
	mov al, 1010b

F1h1:	mov dx, 84	; row-wise pixel
F1h2:	cmp dx, 104
	je Fki11
	cmp dx, 104
	ja F2h1
	mov ah, 0ch
	int 10h 
Fki11:	add dx, 1
	cmp dx, 195
	jne F1h2
	
F2h1:	add cx, 1
	cmp cx, bx
	jne F1h1
;----Moon------
mov al, 1111b
mov cx, 289   ;column  320 ;x
mov dx, 87   ;row  200  ;y coordinate
mov di, dx

loop21:
mov ah, 0ch
int 10h

add dx,1
sub cx, 1
cmp cx, 284
jne loop21

start2:
mov al, 1111b
mov cx, 285   ;column  320 ;x
mov dx, 92   ;row  200  ;y coordinate

loop22:
mov ah, 0ch
int 10h

add dx, 1
cmp dx, 98
jne loop22

start3:
mov al, 1111b
mov cx, 285   ;column  320 ;x
mov dx, 98   ;row  200  ;y coordinate
mov di, dx

loop23:
mov ah, 0ch
int 10h

add dx,1
add cx, 1
cmp cx, 290
jne loop23

start20:
mov al, 1111b
mov cx, 286
mov dx, 91

loop20:
mov ah, 0ch
int 10h

add dx, 1
cmp dx, 99
jne loop20

start200:
mov al, 1111b
mov cx, 287
mov dx, 90

mov ah, 0ch
int 10h

;----Star-----
mov al, 1111b
mov cx, 292   ;column  320 ;x
mov dx, 93   ;row  200  ;y coordinate

loop24:
mov ah, 0ch
int 10h

add dx, 1
add cx, 1
cmp cx, 299
jne loop24

start4:
mov al, 1111b
mov cx, 298   ;column  320 ;x
mov dx, 93   ;row  200  ;y coordinate

loop25:
mov ah, 0ch
int 10h

add dx, 1
sub cx, 1
cmp dx, 100
jne loop25

start5:
mov al, 1111b
mov cx, 291   ;column  320 ;x
mov dx, 96   ;row

loop26:
mov ah, 0ch
int 10h

add cx, 1
cmp cx, 300
jne loop26

start6:
mov al, 1111b
mov cx, 295   ;column  320 ;x
mov dx, 92   ;row  200  ;y coordinate

loop27:
mov ah, 0ch
int 10h

add dx, 1
cmp dx, 101
jne loop27

;----WhiteFlag----
	mov cx, [bp+4]	; column-wise pixel
	add cx, 22
	mov bx, cx
	add bx, 8
	mov si, cx
	mov di, bx
	add si, 1
	sub di, 2
	mov al, 1111b

vF1h1:	mov dx, 84	; row-wise pixel
vF1h2:	cmp dx, 104
	je vFki11
	cmp dx, 104
	ja vF2h1

	mov ah, 0ch
	int 10h 
vFki11:	add dx, 1
	cmp dx, 195
	jne vF1h2
	
vF2h1:	add cx, 1
	cmp cx, bx
	jne vF1h1

;----Pole----
	mov al, 0000b
	mov cx, [bp+4]
	add cx, 30
	mov bx, cx
	add bx, 5
	mov si, cx
	mov di, bx
	add si, 1
	sub di, 2
p2h1:	mov dx, 80	; row-wise pixel
p2h2:	cmp dx, 82
	je pki21
	cmp dx, 82
	ja p1h1

	mov ah, 0ch
	int 10h 
pki21:	add dx, 1
	cmp dx, 195
	jne p2h2
	jmp pki22

p1h1:	cmp cx, si
	jb pki22	
	cmp cx, di
	ja pki22	
	mov ah, 0ch
	int 10h
	add dx, 1
	cmp dx, 195
	jne p2h2

pki22:	add cx, 1
	cmp cx, bx
	jne p2h1

	popa	
	pop bp
	ret 2
;---------------------------------------
;Function for creating the charactor 
;"Mario" figure in the game.
;---------------------------------------
Char:push bp
	mov bp, sp
	pusha

	mov cx, [bp+4]	; column-wise pixel
	mov dx, [bp+6]	; row-wise pixel
;-----head--------
mov di, dx
add di, 5
add cx, 1
mov al, 0111b
mov bx, 0

loop1:
mov ah, 0ch
int 10h
loop2:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, di   ;height
jne loop2
add bx, 1        
add cx, 1
mov dx, [bp+6]
cmp bx, 8
jne loop1
;-----body------
mov cx, [bp+4]	; column-wise pixel
mov dx, [bp+6]	; row-wise pixel
mov al, 0110b
mov bx, 0
add cx, 3
add dx, 6
mov di, dx
add di, 5
mov si, cx	

loop3:
mov ah, 0ch
int 10h

loop4:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, di
jne loop4

add bx, 1
add cx, 1
mov dx, [bp+6]
add dx, 6
cmp bx,	4
jne loop3
;-----Lefthand-----
mov cx, [bp+4]	; column-wise pixel
mov dx, [bp+6]	; row-wise pixel
mov al, 0000b
mov bx, 5
add dx, 6
add cx, 3

loop8:
add dx, 1
sub cx, 1
mov ah, 0ch
int 10h
sub bx, 1
cmp bx, 0
jne loop8
;-----Righthand------
mov cx, [bp+4]	; column-wise pixel
mov dx, [bp+6]	; row-wise pixel
mov al, 0000b
mov bx, 5
add dx, 6
add cx, 6

loop9:
add dx, 1
add cx, 1
mov ah, 0ch
int 10h
sub bx, 1
cmp bx, 0
jne loop9
;-----Leftleg-----
mov cx, [bp+4]	; column-wise pixel
mov dx, [bp+6]	; row-wise pixel
mov al, 0000b
mov bx, 5
add dx, 11
add cx, 3

loop10:
add dx, 1
;sub cx, 1
mov ah, 0ch
int 10h
sub bx, 1
cmp bx, 0
jne loop10
;-----Rightleg------
mov cx, [bp+4]	; column-wise pixel
mov dx, [bp+6]	; row-wise pixel
mov al, 0000b
mov bx, 5
add dx, 11
add cx, 6

loop11:
add dx, 1
;add cx, 1
mov ah, 0ch
int 10h
sub bx, 1
cmp bx, 0
jne loop11
;-----left eye-----
mov cx, [bp+4]	; column-wise pixel
mov dx, [bp+6]	; row-wise pixel
mov al, 1100b
add cx, 2
mov bx, 0
add dx, 2
mov ah, 0ch
int 10h
;----righteye-----
mov cx, [bp+4]	; column-wise pixel
mov dx, [bp+6]	; row-wise pixel
mov al, 1100b
add cx, 7
mov bx, 0
add dx, 2
mov ah, 0ch
int 10h
;----nose----
mov cx, [bp+4]	; column-wise pixel
mov dx, [bp+6]	; row-wise pixel
mov al, 0000b
add cx, 4
mov bx, 0
add dx, 4

mov ah, 0ch
int 10h
add cx, 1
mov ah, 0ch
int 10h

Exs:popa	
	pop bp
	ret 	
;---------------------------------------
;Function for clearing the charactor 
;"Mario" figure in the game.
;---------------------------------------
ClrDis:	push bp
	mov bp, sp
	pusha

	mov cx, [bp+4]	; column-wise pixel
	mov dx, [bp+6]	; row-wise pixel
;-----head--------
mov di, dx
add di, 5
add cx, 1
mov al, 1001b
mov bx, 0

lop1:
mov ah, 0ch
int 10h
lop2:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, di   ;height
jne lop2
add bx, 1        
add cx, 1
mov dx, [bp+6]
cmp bx, 8
jne lop1
;-----body------
mov cx, [bp+4]	; column-wise pixel
mov dx, [bp+6]	; row-wise pixel
mov al, 1001b
mov bx, 0
add cx, 3
add dx, 6
mov di, dx
add di, 5
mov si, cx	

lop3:
mov ah, 0ch
int 10h

lop4:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, di
jne lop4

add bx, 1
add cx, 1
mov dx, [bp+6]
add dx, 6
cmp bx,	4
jne lop3
;-----Lefthand-----
mov cx, [bp+4]	; column-wise pixel
mov dx, [bp+6]	; row-wise pixel
mov al, 1001b
mov bx, 5
add dx, 6
add cx, 3

lop8:
add dx, 1
sub cx, 1
mov ah, 0ch
int 10h
sub bx, 1
cmp bx, 0
jne lop8
;-----Righthand------
mov cx, [bp+4]	; column-wise pixel
mov dx, [bp+6]	; row-wise pixel
mov al, 1001b
mov bx, 5
add dx, 6
add cx, 6

lop9:
add dx, 1
add cx, 1
mov ah, 0ch
int 10h
sub bx, 1
cmp bx, 0
jne lop9
;-----Leftleg-----
mov cx, [bp+4]	; column-wise pixel
mov dx, [bp+6]	; row-wise pixel
mov al, 1001b
mov bx, 5
add dx, 11
add cx, 3

lop10:
add dx, 1
;sub cx, 1
mov ah, 0ch
int 10h
sub bx, 1
cmp bx, 0
jne lop10
;-----Rightleg------
mov cx, [bp+4]	; column-wise pixel
mov dx, [bp+6]	; row-wise pixel
mov al, 1001b
mov bx, 5
add dx, 11
add cx, 6

lop11:
add dx, 1
;add cx, 1
mov ah, 0ch
int 10h
sub bx, 1
cmp bx, 0
jne lop11
;-----left eye-----
mov cx, [bp+4]	; column-wise pixel
mov dx, [bp+6]	; row-wise pixel
mov al, 1001b
add cx, 2
mov bx, 0
add dx, 2
mov ah, 0ch
int 10h
;----righteye-----
mov cx, [bp+4]	; column-wise pixel
mov dx, [bp+6]	; row-wise pixel
mov al, 1001b
add cx, 7
mov bx, 0
add dx, 2
mov ah, 0ch
int 10h
;----nose----
mov cx, [bp+4]	; column-wise pixel
mov dx, [bp+6]	; row-wise pixel
mov al, 1001b
add cx, 4
mov bx, 0
add dx, 4

mov ah, 0ch
int 10h
add cx, 1
mov ah, 0ch
int 10h

Exc:popa	
	pop bp
	ret 
;---------------------------------------
;Function for movement of the charactor 
;"Mario" figure in the game.
;---------------------------------------
movement:push bp
	mov bp, sp
	pusha

	mov dx, [bp+6]	; row-wise pixel
	mov cx, [bp+4]	; column-wise pixel
	push dx
	push cx

AgainD:	
	call Char
	call Mslow
	call WinSet
	mov cx, [Win]
	cmp cx, 1
	je exitmov1

Minput:	
	in al, 0x60
	cmp al, 30
	je GoLeft
	cmp al, 32
	je GoRight
	cmp al, 1
	je exitmov1	
	cmp al, 57
	je Jumping
	jmp Gravity

GoLeft:pop cx
	pop dx
	push dx
	push cx
	cmp cx, 4
	jb Minput
	sub cx, 5
	mov bx, 3
L1:	mov ah, 0x0D
	int 0x10
	cmp al, 0110b
	je Minput
	add dx, 3
	dec bx
	jnz	L1
	call ClrDis
	pop ax
	sub ax, 3
	push ax
	jmp AgainD

exitmov1:jmp exitmov

GoRight:pop cx
	pop dx
	push dx
	push cx
	add cx, 16
	mov bx, 3
R1:	mov ah, 0x0D
	int 0x10
	cmp al, 0110b
	je Minput
	add dx, 3
	dec bx
	jnz	R1
	call ClrDis
	pop ax
	add ax, 3
	push ax
	jmp AgainD

Jumping:
	mov bx, 50
	cmp dx, 50
	jb Minput
j1:	call ClrDis
	pop cx
	pop dx
	sub dx, 1
	in al, 0x60
	cmp al, 30
	jne chr1
	sub cx, 2
chr1:cmp al, 32
	jne coU
	add cx, 2
coU:push dx
	push cx
	call Char
	cmp dx, 50
	jb Minput
	call dslow
	dec bx
	jnz j1
	jmp Minput

Gravity:
	pop cx
	pop dx
	push dx
	push cx
	cmp dx, 175
	ja Minput
	sub cx, 3
	add dx, 18
	mov bx, 14
G1:	mov ah, 0x0D
	int 0x10
	cmp al, 0110b
	je Minput
	add cx, 1
	dec bx
	jnz	G1
	call ClrDis
	pop cx
	pop dx
	add dx, 1
	in al, 0x60
	cmp al, 30
	jne chr2
	sub cx, 2
chr2:cmp al, 32
	jne cod
	add cx, 2
cod:push dx
	push cx
	jmp AgainD
	
exitmov:pop ax
	pop ax
	popa	
	pop bp
	ret 4
;---------------------------------------
;Function for Checking if Mario has 
;reached the flag and won the game.
;---------------------------------------
WinSet:	push bp
	mov bp, sp
	pusha
	mov cx, [bp+4]	; column-wise pixel
	cmp cx, 298
	jb Winexit
	mov cx, 1
	mov word [Win], cx	
	
Winexit:popa	
	pop bp
	ret		
;---------------------------------------
;	Thank You (^_^)
;---------------------------------------