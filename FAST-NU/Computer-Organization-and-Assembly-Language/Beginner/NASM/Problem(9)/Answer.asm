[org 0x100]

	jmp start

P1Msg: db 'You Won the Game..!!$'
P2Msg: db 'You Lost :($'
Win:	dw 0
Dead: dw 0
Left:   dw 0
Right:	dw 0
Down:	dw 0
BallLosY: dw 80
BallLosX: dw 135
Gindcator: dw 0
BGindcator: dw 0
BossLocation: dw 160
BossVAlue: dw 104
ElVAlue: dw 0
Eneny1: dw 90
Eneny2:	dw 153
msg: db 'Press Space to Start',0

;---------------------------------------
Frame:
	push bp
	mov bp, sp
	push ax
	push bx 
	push cx
	push di
	push es

	mov ah,00	
	mov al,03h	; interrupt to clear screen
	int 10h		
	
	mov ah, 0xAB
	mov al, 177
	
	mov bx, 0xb800
	mov es, bx
	mov di, [bp+4]
	mov cx, di
	add cx, 124	

l1c:	mov [es:di], ax
	add di, 2
	cmp di, cx
	jne l1c
	mov [es:di], ax
	add cx, 2880
l2c:	add di, 160
	mov [es:di], ax
	cmp di, cx
	jne l2c
	mov [es:di], ax
	sub cx, 124
l3c:	sub di, 2
	mov [es:di], ax
	cmp di, cx
	jne l3c
	mov [es:di], ax
	sub cx, 2880
l4c:	sub di, 160
	mov [es:di], ax
	cmp di, cx
	jne l4c

	pop es
	pop di
	pop cx
	pop bx
	pop ax
	pop bp
	ret
;---------------------------------------
GameTitle:
	push bp
	mov bp, sp
	push ax
	push bx 
	push cx
	push di
	push es
	
	mov ah, 0x03
	mov al, 'O'
	
	mov bx, 0xb800
	mov es, bx
	mov di, [bp+4]
	add di, 170
	mov cx, 14	
	push di
	
;----SUPER----
;----S----
l11:	mov [es:di], ax
	add di, 2
	sub cx, 2
	cmp cx, 0
	jne l11
	add di, 158
	mov [es:di], ax
	pop di
	push di
	mov cx, 6
l12:	add di, 160
	mov [es:di], ax
	sub cx, 2
	cmp cx, 0
	jne l12
	mov cx, 14	
l13:	mov [es:di], ax
	add di, 2
	sub cx, 2
	cmp cx, 0
	jne l13
	sub di, 2
	mov cx, 6
l14:	add di, 160
	mov [es:di], ax
	sub cx, 2
	cmp cx, 0
	jne l14
	mov cx, 14	
l15:	mov [es:di], ax
	sub di, 2
	sub cx, 2
	cmp cx, 0
	jne l15
	sub di, 158
	mov [es:di], ax

	pop di
	add di, 20	
	mov cx, 12	
	mov ah, 0x0E
;----U----
	push di	
	push di	
	mov [es:di], ax
l21:	add di, 160
	mov [es:di], ax
	sub cx, 2
	cmp cx, 0
	jne l21
	mov cx, 12	
l22:	mov [es:di], ax
	add di, 2
	sub cx, 2
	cmp cx, 0
	jne l22
	mov cx, 12	
	mov [es:di], ax
l23:	sub di, 160
	mov [es:di], ax
	sub cx, 2
	cmp cx, 0
	jne l23

	pop di
	add di, 20	
	mov cx, 12	
	mov ah, 0x04
;----P----
	push di	
	mov [es:di], ax
l31:	add di, 160
	mov [es:di], ax
	sub cx, 2
	cmp cx, 0
	jne l31
	pop di
	push di
	mov cx, 14	
l32:	mov [es:di], ax
	add di, 2
	sub cx, 2
	cmp cx, 0
	jne l32
	sub di, 2
	mov cx, 6
l33:	add di, 160
	mov [es:di], ax
	sub cx, 2
	cmp cx, 0
	jne l33
	mov cx, 14	
l34:	mov [es:di], ax
	sub di, 2
	sub cx, 2
	cmp cx, 0
	jne l34

	pop di
	add di, 20	
	mov cx, 14	
	mov bx, 0	
	mov ah, 0x02
;----E----
	push di
l41:	mov [es:di+bx], ax
	add bx, 2
	sub cx, 2
	cmp cx, 0
	jne l41
	mov cx, 6
l42:	add di, 160
	mov [es:di], ax
	sub cx, 2
	cmp cx, 0
	jne l42
	mov cx, 14	
	mov bx, 0	
l43:	mov [es:di+bx], ax
	add bx, 2
	sub cx, 2
	cmp cx, 0
	jne l43
	mov cx, 6
l44:	add di, 160
	mov [es:di], ax
	sub cx, 2
	cmp cx, 0
	jne l44
	mov cx, 14	
	mov bx, 0	
l45:	mov [es:di+bx], ax
	add bx, 2
	sub cx, 2
	cmp cx, 0
	jne l45
	pop di
	add di, 20	
	mov cx, 6	
	mov bx, 0
	mov ah, 0x0E
;----R----
	push di	
l51:	add bx, 160
	mov [es:di+bx], ax
	sub cx, 2
	cmp cx, 0
	jne l51
	mov cx, 14	
l52:	mov [es:di], ax
	add di, 2
	sub cx, 2
	cmp cx, 0
	jne l52
	sub di, 2
	mov cx, 6
l53:	add di, 160
	mov [es:di], ax
	sub cx, 2
	cmp cx, 0
	jne l53
	mov cx, 14	
l54:	mov [es:di], ax
	sub di, 2
	sub cx, 2
	cmp cx, 0
	jne l54
	mov cx, 6
	mov bx, 4
	add di, 2
l55:	add di, 160
	add bx, 2
	mov [es:di], ax
	mov [es:di+bx], ax
	sub cx, 2
	cmp cx, 0
	jne l55

;----MARIO----
;----M----
	pop di	
	add di, 1220
	push di
	mov bx, 0
	mov ah, 0x03
	mov cx, 12	
	mov [es:di+bx], ax
l71:	add bx, 160
	mov [es:di+bx], ax
	sub cx, 2
	cmp cx, 0
	jne l71
	mov cx, 12	
	mov bx, 0
l72:	mov [es:di+bx], ax
	add bx, 2
	sub cx, 2
	cmp cx, 0
	jne l72
	mov bx, 12
	mov cx, 12	
	mov [es:di+bx], ax
l73:	add di, 160
	mov [es:di+bx], ax
	sub cx, 2
	cmp cx, 0
	jne l73
	pop di	
	push di
	mov bx,	6
	mov cx, 6	
	mov [es:di+bx], ax
l74:	add di, 160
	mov [es:di+bx], ax
	sub cx, 2
	cmp cx, 0
	jne l74

;----A----
	pop di	
	add di, 20
	push di
	mov ah, 0x02
	mov bx, 0
	mov cx, 12	
	mov [es:di+bx], ax
l81:	add bx, 160
	mov [es:di+bx], ax
	sub cx, 2
	cmp cx, 0
	jne l81
	mov cx, 12	
	mov bx, 0
l82:	mov [es:di+bx], ax
	add bx, 2
	sub cx, 2
	cmp cx, 0
	jne l82
	mov bx, 12
	mov cx, 12	
	mov [es:di+bx], ax
l83:	add di, 160
	mov [es:di+bx], ax
	sub cx, 2
	cmp cx, 0
	jne l83
	pop di	
	push di
	mov cx, 12	
	mov bx, 480
l84:	mov [es:di+bx], ax
	add bx, 2
	sub cx, 2
	cmp cx, 0
	jne l84

;----R----
	pop di	
	add di, 20
	push di
	mov ah, 0x0E
	mov cx, 6	
	mov bx, 0
l61:	add bx, 160
	mov [es:di+bx], ax
	sub cx, 2
	cmp cx, 0
	jne l61
	mov cx, 14	
l62:	mov [es:di], ax
	add di, 2
	sub cx, 2
	cmp cx, 0
	jne l62
	sub di, 2
	mov cx, 6
l63:	add di, 160
	mov [es:di], ax
	sub cx, 2
	cmp cx, 0
	jne l63
	mov cx, 14	
l64:	mov [es:di], ax
	sub di, 2
	sub cx, 2
	cmp cx, 0
	jne l64
	mov cx, 6
	mov bx, 4
	add di, 2
l65:	add di, 160
	add bx, 2
	mov [es:di], ax
	mov [es:di+bx], ax
	sub cx, 2
	cmp cx, 0
	jne l65

;----I----
	pop di	
	add di, 18
	push di
	mov ah, 0x04
	mov bx, 0
	mov cx, 12	
	mov [es:di+bx], ax
l91:	add bx, 160
	mov [es:di+bx], ax
	sub cx, 2
	cmp cx, 0
	jne l91
	mov cx, 12	
	mov bx, 0

;----O----
	mov ah, 0x05
	pop di
	add di, 6
	push di	
	mov cx, 12	
	mov [es:di], ax
l01:	add di, 160
	mov [es:di], ax
	sub cx, 2
	cmp cx, 0
	jne l01
	mov cx, 12	
l02:	mov [es:di], ax
	add di, 2
	sub cx, 2
	cmp cx, 0
	jne l02
	mov cx, 12	
	mov [es:di], ax
l03:	sub di, 160
	mov [es:di], ax
	sub cx, 2
	cmp cx, 0
	jne l03
	pop di
	mov cx, 14	
l06:	mov [es:di], ax
	add di, 2
	sub cx, 2
	cmp cx, 0
	jne l06

	pop di
	pop es
	pop di
	pop cx
	pop bx
	pop ax
	pop bp
	ret	
;---------------------------------------
MsgDis:
	push bp
	mov bp, sp
	push ax
	push bx 
	push di
	push si
	push es
	
	mov ah, 0x05
	mov si, msg
	mov al, [si]
	
	mov bx, 0xb800
	mov es, bx
	mov di, [bp+4]
	add di, 3080	

lm1:	cmp al, 0
	je exitfun
	mov [es:di], ax
	add di, 2
	add si, 1
	mov al, [si]
	jmp lm1

exitfun:pop es
	pop si
	pop di
	pop bx
	pop ax
	pop bp
	ret
;---------------------------------------
;Main body of the code for the program.
;---------------------------------------
start:	
	push 338	
	call Frame
	pop ax
	add ax, 162
	push ax

	call GameTitle
	call MsgDis
		
input:	mov ah, 0
	int 0x16 
	cmp al, ' '
	jne input
	mov al, 13h
	mov ah, 0
	int 10h
	call Background
	push 70
	call Hurdles
	push 225
	call castle
	push 124
	push 20
	call movement
	mov al, 03h
	mov ah, 0
	int 10h 
	mov ax, [Win]
	cmp ax, 1
	jne V1
	mov  ax, 0xb800
	mov  es, ax             ; point es to video memory
	mov cx,2000
	mov di,0
	mov ah, 0xAB
	mov al, 177
	rep stosw
	call WP1
	jmp end
V1:	cmp ax, 2
	jne V3
	call WP2
V3:	mov ax, [Dead]
	cmp ax, 1
	jne end
	call WP2

end:mov ax, 0x4c00
	int 21h
;--------------------------	
WP1: 	pusha
		push es
		push 0xb800
		pop es
		mov di, 1980
		mov si, P1Msg
		mov ah, 0x20
q1:		mov al, [si]
		cmp al, '$'
		je P1E
		mov [es:di],ax
		add di, 2
		inc si
		jmp q1
P1E:	pop es
		popa
		ret
;--------------------------
WP2: 	pusha
		push es
		push 0xb800
		pop es
		mov di, 1990
		mov si, P2Msg
		mov ah, 0x04
q2:		mov al, [si]
		cmp al, '$'
		je P2E
		mov [es:di],ax
		add di, 2
		inc si
		jmp q2
P2E:	pop es
		popa
		ret	
;--------------------------
clearBoss:
push bp
mov bp, sp
pusha

mov cx, [BossLocation]
sub cx, 6 
mov di, cx
add di, 46

mov dx, 30
mov si, dx
add si, 47
mov al, 1011b

bloop1:
mov ah, 0ch
int 10h

bloop2:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne bloop2

add cx, 1
mov dx, 30
cmp cx, di
jne bloop1

popa
pop bp
ret
;--------------------------
sBoss:
	pusha

    mov cx, [BGindcator]
	cmp cx, 0
	je BEright

BEleft:
	call clearBoss
    mov cx, [BossVAlue]
	cmp cx, 1
	jb BElfmv
	mov ax, [BossLocation]
	dec ax
	mov [BossLocation], ax
	call monster
	dec cx
	mov [BossVAlue], cx
	jmp BEout

BElfmx:
	mov cx, 1
	mov [BGindcator], cx
	jmp BEleft

BElfmv:
	mov cx, 0
	mov [BGindcator], cx

BEright	
	call clearBoss
    mov cx, [BossVAlue]
	cmp cx, 104
	ja BElfmx
	mov ax, [BossLocation]
	inc ax
	mov [BossLocation], ax
	call monster
	inc cx
	mov [BossVAlue], cx

BEout: 
	popa	
	ret
;---------------------
;fireball
;---------------------
sFire:
	pusha
	mov cx, [BallLosX]
	mov dx, [BallLosY]
	add dx, 10
	mov bx, 12
FL1:mov ah, 0x0D
	int 0x10
	cmp al, 0110b
	jne FL12
	call cFire
	mov ax, 72
	mov [BallLosY], ax
	mov ax, [BossLocation]
	mov [BallLosX], ax
	jmp FC1
FL12:cmp al, 0010b
	jne FL2
	call sEnemies
	call cFire
	mov ax, 72
	mov [BallLosY], ax
	mov ax, [BossLocation]
	mov [BallLosX], ax	
	jmp FC1
FL2:cmp al, 0111b
	jne FL13
	mov ax, 1
	mov [Dead], ax	
	jmp FC1
FL13:inc cx 
	dec bx
	jnz FL1
FC1:call fdelay	
	mov dx, [BallLosX]
	cmp dx, 185
	jb FC
	call cFire
	mov ax, 110
	mov [BallLosY], ax
FC:	call fdelay	
	call cFire
	mov dx, [BallLosY]
	inc dx
	mov [BallLosY], dx
	call Fire
	call sEnemies
	popa
	ret
;------------------------
fdelay:push	ax
mov ax, 0x0f0f
fd:	dec ax
	jnz fd
	pop ax
	ret
;------------------------
Fire:
	pusha
	mov dx, [BallLosY]     ;starting row pixel
	cmp dx, 185
	je BallE1
	mov si, dx     ;ending row pixel
	add si, 2

	mov cx, [BallLosX]    ;column pixel
	mov di, cx
	add di, 5     ;ending column pixel

	mov bx, 0
	mov al, 1100b

floop1:
	mov ah, 0ch
	int 10h
floop2:
	add dx, 1
	mov ah, 0ch
	int 10h
	cmp dx, si
	jne floop2	
	add cx, 1
	add bx, 1
	mov dx, [BallLosY]     ;starting row pixel
	mov si, dx     ;ending row pixel
	add si, 2
	sub dx, bx
	add si, bx
	cmp cx, di
	jne floop1
	jmp Hac
BallE1: jmp BallE
;----------------
Hac:mov cx, [BallLosX]    ;column pixel
	add cx, 10
	mov di, [BallLosX]
	add di, 4

	mov dx, [BallLosY]     ;starting row pixel
	mov si, dx     ;ending row pixel
	add si, 2
	mov bx, 0
	mov al, 1100b

floop3:
	mov ah, 0ch
	int 10h

floop4:
	add dx, 1
	mov ah, 0ch
	int 10h
	cmp dx, si
	jne floop4
	sub cx, 1
	add bx, 1
	mov dx, [BallLosY]     ;starting row pixel
	mov si, dx     ;ending row pixel
	add si, 2
	sub dx, bx
	add si, bx
	cmp cx, di
	jne floop3

BallE:	popa
		ret
;-------------------------------------------------
cFire:
	pusha
	mov dx, [BallLosY]     ;starting row pixel
	cmp dx, 185
	je cBallE1
	mov si, dx     ;ending row pixel
	add si, 2

	mov cx, [BallLosX]    ;column pixel
	mov di, cx
	add di, 5     ;ending column pixel

	mov bx, 0
	mov al, 1011b

cfloop1:
	mov ah, 0ch
	int 10h

cfloop2:
	add dx, 1
	mov ah, 0ch
	int 10h
	cmp dx, si
	jne cfloop2	
	add cx, 1
	add bx, 1
	mov dx, [BallLosY]     ;starting row pixel
	mov si, dx     ;ending row pixel
	add si, 2
	sub dx, bx
	add si, bx
	cmp cx, di
	jne cfloop1
	jmp cHac
cBallE1: jmp cBallE
;----------------
cHac:mov cx, [BallLosX]    ;column pixel
	add cx, 10
	mov di, [BallLosX]
	add di, 4

	mov dx, [BallLosY]     ;starting row pixel
	mov si, dx     ;ending row pixel
	add si, 2
	mov bx, 0
	mov al, 1011b

cfloop3:
	mov ah, 0ch
	int 10h

cfloop4:
	add dx, 1
	mov ah, 0ch
	int 10h
	cmp dx, si
	jne cfloop4
	sub cx, 1
	add bx, 1
	mov dx, [BallLosY]     ;starting row pixel
	mov si, dx     ;ending row pixel
	add si, 2
	sub dx, bx
	add si, bx
	cmp cx, di
	jne cfloop3

cBallE:	popa
		ret
;--------------------------
;Monster
;--------------------------
monster:
push bp
mov bp, sp
pusha

;----rectangle-----
mov cx, [BossLocation]    ;column pixel
mov di, cx
add di, 35

mov dx, 55        ;row pixel
mov si, dx
add si, 9
mov al, 1110b

mloop1:
mov ah, 0ch
int 10h

mloop2:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne mloop2

add cx, 1
mov dx, 55
cmp cx, di
jne mloop1

;--------------------
mov cx, [BossLocation]    ;column pixel
add cx, 5
mov di, cx
add di, 10

mov dx, 64
mov si, dx
add si, 9
mov al, 1110b

mloop3:
mov ah, 0ch
int 10h

mloop4:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne mloop4

add cx, 1
mov dx, 64
cmp cx, di
jne mloop3

;-----------------
mov cx, [BossLocation]    ;column pixel
add cx, 15
mov di, cx
add di, 5

mov dx, 64
mov si, dx
add si, 7
mov al, 1110b

mloop5:
mov ah, 0ch
int 10h

mloop6:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne mloop6

add cx, 1
mov dx, 64
cmp cx, di
jne mloop5

;----------------
mov cx, [BossLocation]    ;column pixel
add cx, 20
mov di, cx
add di, 10

mov dx, 64
mov si, dx
add si, 9
mov al, 1110b

mloop7:
mov ah, 0ch
int 10h

mloop8:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne mloop8

add cx, 1
mov dx, 64
cmp cx, di
jne mloop7

;-----face-------
mov cx, [BossLocation]    ;column pixel
add cx, 8
mov di, cx
add di, 19

mov dx, 43
mov si, dx
add si, 11
mov al, 0010b

mloop9:
mov ah, 0ch
int 10h

mloop10:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne mloop10

add cx, 1
mov dx, 43
cmp cx, di
jne mloop9

;------mouth------
mov cx, [BossLocation]    ;column pixel
add cx, 8
mov di, cx
add di, 19

mov dx, 65
mov si, dx
add si, 3
mov al, 0100b

mloop11:
mov ah, 0ch
int 10h

mloop12:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne mloop12

add cx, 1
mov dx, 65
cmp cx, di
jne mloop11

;-------------------
mov cx, [BossLocation]    ;column pixel
add cx, 15
mov di, cx
add di, 5

mov dx, 63
mov si, dx
add si, 2

mloop13:
mov ah, 0ch
int 10h

mloop14:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne mloop14

add cx, 1
mov dx, 63
cmp cx, di
jne mloop13

;-----eyes--------
;-----left eye-----
mov cx, [BossLocation]    ;column pixel
add cx, 10
mov di, cx
add di, 5

mov dx, 51
mov si, dx
add si, 6
mov al, 1111b

mloop15:
mov ah, 0ch
int 10h

mloop16:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne mloop16

add cx, 1
mov dx, 51
cmp cx, di
jne mloop15

;------Right eye-----
mov cx, [BossLocation]    ;column pixel
add cx, 20
mov di, cx
add di, 5

mov dx, 51
mov si, dx
add si, 6
mov al, 1111b

mloop17:
mov ah, 0ch
int 10h

mloop18:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne mloop18

add cx, 1
mov dx, 51
cmp cx, di
jne mloop17

;------eyeball-----
mov cx, [BossLocation]    ;column pixel
add cx, 13
mov di, cx
add di, 2

mov dx, 55
mov si, dx
add si, 2
mov al, 0000b

mloop19:
mov ah, 0ch
int 10h

mloop20:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne mloop20

add cx, 1
mov dx, 55
cmp cx, di
jne mloop19

;------right-------
mov cx, [BossLocation]    ;column pixel
add cx, 23
mov di, cx
add di, 2

mov dx, 55
mov si, dx
add si, 2
mov al, 0000b

mloop21:
mov ah, 0ch
int 10h

mloop22:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne mloop22

add cx, 1
mov dx, 55
cmp cx, di
jne mloop21

;-----hair-------
mov cx, [BossLocation]    ;column pixel
add cx, 1
mov di, cx
add di, 7

mov dx, 37
mov si, dx
add si, 17
mov al, 0110b

mloop23:
mov ah, 0ch
int 10h

mloop24:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne mloop24

add cx, 1
mov dx, 37
cmp cx, di
jne mloop23

;---------------
mov cx, [BossLocation]    ;column pixel
add cx, 8
mov di, [BossLocation]    ;column pixel
add di, 27

mov dx, 37
mov si, dx
add si, 6
mov al, 0110b

mloop25:
mov ah, 0ch
int 10h

mloop26:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne mloop26

add cx, 1
mov dx, 37
cmp cx, di
jne mloop25

;------------------
mov cx, [BossLocation]    ;column pixel
add cx, 27
mov di, [BossLocation]    ;column pixel
add di, 35

mov dx, 37
mov si, dx
add si, 17
mov al, 0110b

mloop27:
mov ah, 0ch
int 10h

mloop28:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne mloop28

add cx, 1
mov dx, 37
cmp cx, di
jne mloop27

;----horns----
mov cx, [BossLocation]    ;column pixel
add cx, 27
mov di, [BossLocation]    ;column pixel
add di, 40
mov dx, 44
mov si, dx
add si, 3
mov al, 1110b

mloop31:
mov ah, 0ch
int 10h

mloop32:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne mloop32

add cx, 1
mov dx, 44
cmp cx, di
jne mloop31

mov cx, [BossLocation]    ;column pixel
add cx, 39
mov di, [BossLocation]    ;column pixel
add di, 37
mov dx, 44
mov si,42
mloop33:
mov ah, 0ch
int 10h

mloop34:
sub dx,1
mov ah, 0ch
int 10h
cmp dx, si
jne mloop34

sub cx, 1
mov dx,44
cmp cx, di
jne mloop33

;------left horn------
mov cx, [BossLocation]    ;column pixel
add cx, 8
mov di, [BossLocation]    ;column pixel
sub di, 5
mov dx, 44
mov si, dx
add si, 3
mov al, 1110b

mloop35:
mov ah, 0ch
int 10h

mloop36:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne mloop36

sub cx, 1
mov dx, 44
cmp cx, di
jne mloop35

mov cx, [BossLocation]    ;column pixel
sub cx, 4
mov di, [BossLocation]    ;column pixel
sub di, 2
mov dx, 44
mov si,42

mloop38:
mov ah, 0ch
int 10h

mloop37:
sub dx,1
mov ah, 0ch
int 10h
cmp dx, si
jne mloop37

add cx, 1
mov dx,44
cmp cx, di
jne mloop38

popa
pop bp
ret	
;---------------------------------------
ClsEnemies:
push bp
mov bp, sp
pusha

;----Enemy1---
mov cx, [Eneny1]        ;column pixel
mov di, cx
add di, 9         ;ending column pixel

mov dx, 175       ;starting row pixel
mov bx, 0
mov si, dx
add si, 9         ;ending row pixel
mov al, 1011b

eeloop1:
mov ah, 0ch
int 10h

eeloop2:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne eeloop2

add bx, 1
add cx, 1      ;next column
mov dx, 175
add dx, bx
cmp cx, di
jne eeloop1

mov cx, [Eneny1]        ;column pixel
mov di, cx
sub di, 9

mov dx, 175
mov bx, 0
mov si, dx
add si, 9
mov al, 1011b

eeloop3:
mov ah, 0ch
int 10h

eeloop4:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne eeloop4

add bx, 1
sub cx, 1
mov dx, 175
add dx, bx
cmp cx, di
jne eeloop3

;----Body----
mov cx, [Eneny1]      ;staring column pixel
sub cx, 3
mov di, cx
add di, 7      ;ending column pixel

mov dx, 185
mov si, dx
add si, 4
mov al, 1011b

eeloop5:
mov ah, 0ch
int 10h

eeloop6:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne eeloop6

add cx, 1
mov dx, 185
cmp cx, di
jne eeloop5

;----eyes-----
mov cx, [Eneny1]
sub cx, 2
mov di, cx
add di, 2

mov dx, 179
mov si, dx
add si, 2
mov al, 1011b

eeloop7:
mov ah, 0ch
int 10h

eeloop8:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne eeloop8

add cx, 1
mov dx, 179
cmp cx, di
jne eeloop7

mov cx, [Eneny1]
sub cx, 2
mov di, cx
add di, 2

mov dx, 179
mov si, dx
add si, 2
mov al, 1011b

eeloop9:
mov ah, 0ch
int 10h

eeloop10:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne eeloop10

add cx, 1
mov dx, 179
cmp cx, di
jne eeloop9

mov cx, [Eneny1]
sub cx, 2
mov di, cx
add di, 1

mov dx, 179
mov si, dx
add si, 2
mov al, 1011b

eeloop11:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne eeloop11

mov cx, [Eneny1]
add cx, 2
mov di, cx
add di, 1

mov dx, 179
mov si, dx
add si, 2
mov al, 1011b

eeloop12:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne eeloop12

;-----legs-----
;-----left leg----
mov cx, [Eneny1]
sub cx, 3	; column-wise pixel
mov di, [Eneny1]
sub di, 8
mov dx, 188	; row-wise pixel
mov si, dx
add si, 5
mov al, 1011b
mov bx, 0

eeloop14:
mov ah, 0ch
int 10h

eeloop13:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne eeloop13

add bx, 1
mov dx, 188
add dx, bx
sub cx, 1
cmp cx, di
jne eeloop14

;----Right leg----
mov cx, [Eneny1]
add cx, 3   ;column pixel
mov di, [Eneny1]
add di, 8
mov dx, 188   ;row pixel
mov si, dx
add si, 5
mov al, 1011b
mov bx, 0

eeloop15:
mov ah, 0ch
int 10h

eeloop16:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne eeloop16

add bx, 1
mov dx, 188
add dx, bx
add cx, 1
cmp cx, di
jne eeloop15

;-----Enemy 2------
mov cx, [Eneny2]        ;column pixel
mov di, cx
add di, 9         ;ending column pixel

mov dx, 175       ;starting row pixel
mov bx, 0
mov si, dx
add si, 9         ;ending row pixel
mov al, 1011b

ee2loop1:
mov ah, 0ch
int 10h

ee2loop2:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne ee2loop2

add bx, 1
add cx, 1      ;next column
mov dx, 175
add dx, bx
cmp cx, di
jne ee2loop1

mov cx, [Eneny2]        ;column pixel
mov di, cx
sub di, 9

mov dx, 175
mov bx, 0
mov si, dx
add si, 9
mov al, 1011b

ee2loop3:
mov ah, 0ch
int 10h

ee2loop4:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne ee2loop4

add bx, 1
sub cx, 1
mov dx, 175
add dx, bx
cmp cx, di
jne ee2loop3

;----Body----
mov cx, [Eneny2]      ;staring column pixel
sub cx, 3
mov di, cx
add di, 7      ;ending column pixel

mov dx, 185
mov si, dx
add si, 4
mov al, 1011b

ee2loop5:
mov ah, 0ch
int 10h

ee2loop6:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne ee2loop6

add cx, 1
mov dx, 185
cmp cx, di
jne ee2loop5

;----eyes-----
mov cx, [Eneny2]
sub cx, 2
mov di, cx
add di, 2

mov dx, 179
mov si, dx
add si, 2
mov al, 1011b

ee2loop7:
mov ah, 0ch
int 10h

ee2loop8:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne ee2loop8

add cx, 1
mov dx, 179
cmp cx, di
jne ee2loop7

mov cx, [Eneny2]
sub cx, 2
mov di, cx
add di, 2

mov dx, 179
mov si, dx
add si, 2
mov al, 1011b

ee2loop9:
mov ah, 0ch
int 10h

ee2loop10:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne ee2loop10

add cx, 1
mov dx, 179
cmp cx, di
jne ee2loop9

mov cx, [Eneny2]
sub cx, 2
mov di, cx
add di, 1

mov dx, 179
mov si, dx
add si, 2
mov al, 1011b

ee2loop11:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne ee2loop11

mov cx, [Eneny2]
add cx, 2
mov di, cx
add di, 1

mov dx, 179
mov si, dx
add si, 2
mov al, 1011b

ee2loop12:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne ee2loop12

;-----legs-----
;-----left leg----
mov cx, [Eneny2]
sub cx, 3	; column-wise pixel
mov di, [Eneny2]
sub di, 8
mov dx, 188	; row-wise pixel
mov si, dx
add si, 5
mov al, 1011b
mov bx, 0

ee2loop14:
mov ah, 0ch
int 10h

ee2loop13:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne ee2loop13

add bx, 1
mov dx, 188
add dx, bx
sub cx, 1
cmp cx, di
jne ee2loop14

;----Right leg----
mov cx, [Eneny2]
add cx, 3   ;column pixel
mov di, [Eneny2]
add di, 8
mov dx, 188   ;row pixel
mov si, dx
add si, 5
mov al, 1011b
mov bx, 0

ee2loop15:
mov ah, 0ch
int 10h

ee2loop16:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne ee2loop16

add bx, 1
mov dx, 188
add dx, bx
add cx, 1
cmp cx, di
jne ee2loop15
popa
pop bp
ret
;---------------------------------------
sEnemies:
	pusha
    
    mov cx, [Gindcator]
	cmp cx, 0
	je Eright

Eleft:
	call ClsEnemies
    mov cx, [ElVAlue]
	cmp cx, 1
	jb Elfmv
	mov ax, [Eneny1]
	dec ax
	mov [Eneny1], ax
	mov ax, [Eneny2]
	dec ax
	mov [Eneny2], ax
	call Enemies
	dec cx
	mov [ElVAlue], cx
	jmp sEout

Elfmx:
	mov cx, 1
	mov [Gindcator], cx
	jmp Eleft

Elfmv:
	mov cx, 0
	mov [Gindcator], cx

Eright	
	call ClsEnemies
    mov cx, [ElVAlue]
	cmp cx, 30
	ja Elfmx
	mov ax, [Eneny1]
	inc ax
	mov [Eneny1], ax
	mov ax, [Eneny2]
	inc ax
	mov [Eneny2], ax
	call Enemies
	inc cx
	mov [ElVAlue], cx

sEout: 
	popa	
	ret
;---------------------------------------
;Function for creating the background
;scenery of the game.
;---------------------------------------
Background:
	pusha
	mov dx, 0
;----Sky----
	mov al, 1011b
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
dslow:	pusha
	mov cx, 0x0010	
lsU:mov dx, 0xffff
ls:	dec dx
	jnz ls
	dec cx
	jnz lsU
	popa
	ret
;---------------------------------------
;Function for slowing the motion of the
;Mario figure.
;---------------------------------------
Mslow:	push cx
	mov cx, 0xCCCC	
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
	add cx, 63
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

	popa	
	pop bp
	ret 2
;---------------------------------------
;Function for creating enemies
;--------------------------------------
Enemies:
push bp
mov bp, sp
pusha

;----Enemy1---
mov cx, [Eneny1]        ;column pixel
mov di, cx
add di, 9         ;ending column pixel

mov dx, 175       ;starting row pixel
mov bx, 0
mov si, dx
add si, 9         ;ending row pixel
mov al, 1100b

eloop1:
mov ah, 0ch
int 10h

eloop2:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne eloop2

add bx, 1
add cx, 1      ;next column
mov dx, 175
add dx, bx
cmp cx, di
jne eloop1

mov cx, [Eneny1]        ;column pixel
mov di, cx
sub di, 9

mov dx, 175
mov bx, 0
mov si, dx
add si, 9
mov al, 1100b

eloop3:
mov ah, 0ch
int 10h

eloop4:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne eloop4

add bx, 1
sub cx, 1
mov dx, 175
add dx, bx
cmp cx, di
jne eloop3

;----Body----
mov cx, [Eneny1]      ;staring column pixel
sub cx, 3
mov di, cx
add di, 7      ;ending column pixel

mov dx, 185
mov si, dx
add si, 4
mov al, 1101b

eloop5:
mov ah, 0ch
int 10h

eloop6:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne eloop6

add cx, 1
mov dx, 185
cmp cx, di
jne eloop5

;----eyes-----
mov cx, [Eneny1]
sub cx, 2
mov di, cx
add di, 2

mov dx, 179
mov si, dx
add si, 2
mov al, 0000b

eloop7:
mov ah, 0ch
int 10h

eloop8:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne eloop8

add cx, 1
mov dx, 179
cmp cx, di
jne eloop7

mov cx, [Eneny1]
sub cx, 2
mov di, cx
add di, 2

mov dx, 179
mov si, dx
add si, 2
mov al, 1111b

eloop9:
mov ah, 0ch
int 10h

eloop10:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne eloop10

add cx, 1
mov dx, 179
cmp cx, di
jne eloop9

mov cx, [Eneny1]
sub cx, 2
mov di, cx
add di, 1

mov dx, 179
mov si, dx
add si, 2
mov al, 0000b

eloop11:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne eloop11

mov cx, [Eneny1]
add cx, 2
mov di, cx
add di, 1

mov dx, 179
mov si, dx
add si, 2
mov al, 0000b

eloop12:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne eloop12

;-----legs-----
;-----left leg----
mov cx, [Eneny1]
sub cx, 3	; column-wise pixel
mov di, [Eneny1]
sub di, 8
mov dx, 188	; row-wise pixel
mov si, dx
add si, 5
mov al, 0000b
mov bx, 0

eloop14:
mov ah, 0ch
int 10h

eloop13:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne eloop13

add bx, 1
mov dx, 188
add dx, bx
sub cx, 1
cmp cx, di
jne eloop14

;----Right leg----
mov cx, [Eneny1]
add cx, 3   ;column pixel
mov di, [Eneny1]
add di, 8
mov dx, 188   ;row pixel
mov si, dx
add si, 5
mov al, 0000b
mov bx, 0

eloop15:
mov ah, 0ch
int 10h

eloop16:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne eloop16

add bx, 1
mov dx, 188
add dx, bx
add cx, 1
cmp cx, di
jne eloop15

;-----Enemy 2------
mov cx, [Eneny2]        ;column pixel
mov di, cx
add di, 9         ;ending column pixel

mov dx, 175       ;starting row pixel
mov bx, 0
mov si, dx
add si, 9         ;ending row pixel
mov al, 1100b

e2loop1:
mov ah, 0ch
int 10h

e2loop2:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne e2loop2

add bx, 1
add cx, 1      ;next column
mov dx, 175
add dx, bx
cmp cx, di
jne e2loop1

mov cx, [Eneny2]        ;column pixel
mov di, cx
sub di, 9

mov dx, 175
mov bx, 0
mov si, dx
add si, 9
mov al, 1100b

e2loop3:
mov ah, 0ch
int 10h

e2loop4:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne e2loop4

add bx, 1
sub cx, 1
mov dx, 175
add dx, bx
cmp cx, di
jne e2loop3

;----Body----
mov cx, [Eneny2]      ;staring column pixel
sub cx, 3
mov di, cx
add di, 7      ;ending column pixel

mov dx, 185
mov si, dx
add si, 4
mov al, 1101b

e2loop5:
mov ah, 0ch
int 10h

e2loop6:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne e2loop6

add cx, 1
mov dx, 185
cmp cx, di
jne e2loop5

;----eyes-----
mov cx, [Eneny2]
sub cx, 2
mov di, cx
add di, 2

mov dx, 179
mov si, dx
add si, 2
mov al, 1111b

e2loop7:
mov ah, 0ch
int 10h

e2loop8:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne e2loop8

add cx, 1
mov dx, 179
cmp cx, di
jne e2loop7

mov cx, [Eneny2]
sub cx, 2
mov di, cx
add di, 2

mov dx, 179
mov si, dx
add si, 2
mov al, 1111b

e2loop9:
mov ah, 0ch
int 10h

e2loop10:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne e2loop10

add cx, 1
mov dx, 179
cmp cx, di
jne e2loop9

mov cx, [Eneny2]
sub cx, 2
mov di, cx
add di, 1

mov dx, 179
mov si, dx
add si, 2
mov al, 0000b

e2loop11:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne e2loop11

mov cx, [Eneny2]
add cx, 2
mov di, cx
add di, 1

mov dx, 179
mov si, dx
add si, 2
mov al, 0000b

e2loop12:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne e2loop12

;-----legs-----
;-----left leg----
mov cx, [Eneny2]
sub cx, 3	; column-wise pixel
mov di, [Eneny2]
sub di, 8
mov dx, 188	; row-wise pixel
mov si, dx
add si, 5
mov al, 0000b
mov bx, 0

e2loop14:
mov ah, 0ch
int 10h

e2loop13:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne e2loop13

add bx, 1
mov dx, 188
add dx, bx
sub cx, 1
cmp cx, di
jne e2loop14

;----Right leg----
mov cx, [Eneny2]
add cx, 3   ;column pixel
mov di, [Eneny2]
add di, 8
mov dx, 188   ;row pixel
mov si, dx
add si, 5
mov al, 0000b
mov bx, 0

e2loop15:
mov ah, 0ch
int 10h

e2loop16:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne e2loop16

add bx, 1
mov dx, 188
add dx, bx
add cx, 1
cmp cx, di
jne e2loop15

exit:
popa
pop bp
ret
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
mov al, 1011b
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
add cx, 2
mov bx, 0
add dx, 2
mov ah, 0ch
int 10h
;----righteye-----
mov cx, [bp+4]	; column-wise pixel
mov dx, [bp+6]	; row-wise pixel
add cx, 7
mov bx, 0
add dx, 2
mov ah, 0ch
int 10h
;----nose----
mov cx, [bp+4]	; column-wise pixel
mov dx, [bp+6]	; row-wise pixel
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
	mov dx, [bp+6]	; row-wise pixel
	mov cx, [bp+4]	; column-wise pixel
	mov bx, 14
DA:	mov ah, 0x0D
	int 0x10
	cmp al, 1100b
	jne DC
	mov ax, 2
	mov [Win], ax	
	jmp exitmov1
DC:	add cx, 1
	dec bx
	jnz	DA
	call Char	
	call WinSet
	mov cx, [Win]
	cmp cx, 1
	je exitmov1
	call VEMotion 
Minput:
	mov cx, [Dead]
	cmp cx, 1
	je exitmov1	
	call dslow
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
	jb AgainD
	sub cx, 5
	mov bx, 3
L1:	mov ah, 0x0D
	int 0x10
	cmp al, 0110b
	je AgainD
	cmp al, 1100b
	jne LC
	mov ax, 2
	mov [Win], ax	
	jmp exitmov1
LC:	add dx, 3
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
	mov bx, 20
R1:	mov ah, 0x0D
	int 0x10
	cmp al, 0110b
	je AgainD
	cmp al, 1100b
	jne RC
	mov ax, 2
	mov [Win], ax	
	jmp exitmov
RC:	add dx, 1
	dec bx
	jnz	R1
	call ClrDis
	pop ax
	add ax, 3
	push ax
	jmp AgainD

Jumping:
	mov bx, 20
	cmp dx, 100
	jb AgainD
	sub dx, 20
	cmp dx, 100
	jb AgainD
	add dx, 20
j1:	call ClrDis
	pop cx
	pop dx
	sub dx, 1
	push dx
	push cx
	call Char
	cmp dx, 50
	jb Minput
	call VEMotion 
	mov si, [Dead]
	cmp si, 1
	je exitmov1	
	call Mslow
	call Mslow
	dec bx
	jnz j1
	jmp Minput

Back:jmp AgainD

Gravity:
	pop cx
	pop dx
	push dx
	push cx
	cmp dx, 175
	ja Back
	sub cx, 3
	add dx, 18
	mov bx, 14
G1:	mov ah, 0x0D
	int 0x10
	cmp al, 0110b
	je Back
	cmp al, 1100b
	jne GC
	mov ax, 2
	mov [Win], ax	
	jmp exitmov
GC:	add cx, 1
	dec bx
	jnz	G1
	call ClrDis
	pop cx
	pop dx 
	add dx, 1
	push dx
	push cx
	jmp AgainD
	
exitmov:pop ax
	pop ax
	popa	
	pop bp
	ret 4
;---------------------------------------
VEMotion:
	call sBoss
	call sFire
	ret
;---------------------------------------
;Function for Checking if Mario has 
;reached the flag and won the game.
;---------------------------------------
WinSet:	push bp
	mov bp, sp
	pusha
	mov cx, [bp+4]	; column-wise pixel
	cmp cx, 210
	jb Winexit
	mov cx, 1
	mov word [Win], cx	
	
Winexit:popa	
	pop bp
	ret		
;--------------------------
;Castle
;--------------------------
castle:
push bp
mov bp, sp
pusha

;--------building-----------
mov cx, [bp+4]  ;column pixel
mov di, cx
add di, 7       ;ending column pixel

mov dx, 152     ;starting row pixel
mov si,  200    ;ending row pixel
mov al, 0111b

cloop1:
mov ah, 0ch
int 10h

cloop2:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne cloop2

add cx, 1
mov dx, 152
cmp cx, di
jne cloop1

;--------------------
mov cx, 232
mov di, cx
add di, 7

mov dx, 159
mov si, 200
mov al, 0111b

cloop3:
mov ah, 0ch
int 10h

cloop4:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne cloop4

add cx, 1
mov dx, 159
cmp cx, di
jne cloop3

;--------------------
mov cx, 239
mov di, cx
add di, 7

mov dx, 152
mov si, 200
mov al, 0111b

cloop5:
mov ah, 0ch
int 10h

cloop6:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne cloop6

add cx, 1
mov dx, 152
cmp cx, di
jne cloop5

;----------------------
mov cx, 246
mov di, cx
add di, 7

mov dx, 159
mov si, 200
mov al, 0111b

cloop7:
mov ah, 0ch
int 10h

cloop8:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne cloop8

add cx, 1
mov dx, 159
cmp cx, di
jne cloop7

;---------------------
mov cx, 253
mov di, cx
add di, 7

mov dx, 152
mov si, 200
mov al, 0111b

cloop9:
mov ah, 0ch
int 10h

cloop10:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne cloop10

add cx, 1
mov dx, 152
cmp cx, di
jne cloop9

;--------------------
mov cx, 260
mov di, cx
add di, 7

mov dx, 159
mov si, 200
mov al, 0111b

cloop11:
mov ah, 0ch
int 10h

cloop12:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne cloop12

add cx, 1
mov dx, 159
cmp cx, di
jne cloop11

;-----------------------
mov cx, 267
mov di, cx
add di, 7

mov dx, 152
mov si, 200
mov al, 0111b

cloop13:
mov ah, 0ch
int 10h

cloop14:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne cloop13

add cx, 1
mov dx, 152
cmp cx, di
jne cloop14

;-----------------------
mov cx, 274
mov di, cx
add di, 7

mov dx, 159
mov si, 200
mov al, 0111b

cloop15:
mov ah, 0ch
int 10h

cloop16:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne cloop16

add cx, 1
mov dx, 159
cmp cx, di
jne cloop15

;----------------------
mov cx, 281
mov di, cx
add di, 7

mov dx, 152
mov si, 200
mov al, 0111b

cloop17:
mov ah, 0ch
int 10h

cloop18:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne cloop18

add cx, 1
mov dx, 152
cmp cx, di
jne cloop17

;-------------------------
mov cx, 288
mov di, cx
add di, 7

mov dx, 159
mov si, 200
mov al, 0111b

cloop19:
mov ah, 0ch
int 10h

cloop20:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne cloop20

add cx, 1
mov dx, 159
cmp cx, di
jne cloop19

;----------------------
mov cx, 295
mov di, cx
add di, 7

mov dx, 152
mov si, 200
mov al, 0111b

cloop21:
mov ah, 0ch
int 10h

cloop22:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne cloop22

add cx, 1
mov dx, 152
cmp cx, di
jne cloop21

;-------top-----------
mov cx, 235
mov di, cx
add di, 4        ;14

mov dx, 125
mov si, dx
add si, 33
mov al, 1000b

cloop23:
mov ah, 0ch
int 10h

cloop24:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne cloop24

add cx, 1
mov dx, 125
cmp cx, di
jne cloop23

;---------------
mov cx, 239
mov di, cx
add di, 7

mov dx, 125
mov si, dx
add si, 26

cloop25:
mov ah, 0ch
int 10h

cloop26:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne cloop26

add cx, 1
mov dx, 125
cmp cx, di
jne cloop25

;-----------------
mov cx, 246
mov di, cx
add di, 4

mov dx, 125
mov si, dx
add si, 33

cloop27:
mov ah, 0ch
int 10h

cloop28:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne cloop28

add cx, 1
mov dx, 125
cmp cx, di
jne cloop27

;-----------------

mov cx, 288
mov di, 295

mov dx, 125
mov si, dx
add si, 33

cloop29:
mov ah, 0ch
int 10h

cloop30:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne cloop30

add cx, 1
mov dx, 125
cmp cx, di
jne cloop29

;------------
mov cx, 281
mov di, 288

mov dx, 125
mov si, dx
add si, 26

cloop31:
mov ah, 0ch
int 10h

cloop32:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne cloop32

add cx, 1
mov dx, 125
cmp cx, di
jne cloop31

;-----------------
mov cx, 259
mov di, 266

mov dx, 125
mov si, dx
add si, 33

cloop33:
mov ah, 0ch
int 10h

cloop34:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne cloop34

add cx, 1
mov dx, 125
cmp cx, di
jne cloop33

;---------------
mov cx, 266
mov di, 273

mov dx, 125
mov si, dx
add si, 27

cloop35:
mov ah, 0ch
int 10h

cloop36:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne cloop36

add cx, 1
mov dx, 125
cmp cx, di
jne cloop35

;------Door----------

mov cx, 259
mov di, cx
add di, 7

mov dx, 185
mov si, dx
add si, 15
mov bx, 0
mov al, 0110b

dloop1:
mov ah, 0ch
int 10h

dloop2:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne dloop2

add cx, 1
add bx, 1
mov dx, 185
sub dx, bx
cmp cx, di
jne dloop1

;-----------------
mov cx, 272
mov di, cx
sub di, 7

mov dx, 185
mov si, dx
add si, 15
mov bx, 0

dloop3:
mov ah, 0ch
int 10h

dloop4:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne dloop4

sub cx, 1
add bx, 1
mov dx, 185
sub dx, bx
cmp cx, di
jne dloop3

;-----roof------
mov cx, 243
mov di, 252

mov dx, 115
mov si, dx
add si, 9
mov bx, 0
mov al, 0100b

dloop5:
mov ah, 0ch
int 10h

dloop6:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne dloop6

mov dx, 115
add cx, 1
add bx, 1
add dx, bx
cmp cx, di
jne dloop5

;---------------
mov cx, 242
mov di, 233

mov dx, 115
mov si, dx
add si, 9
mov bx, 0

dloop7:
mov ah, 0ch
int 10h

dloop8:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne dloop8

mov dx, 115
sub cx, 1
add bx, 1
add dx, bx
cmp cx, di
jne dloop7

;------------------
mov cx, 267
mov di, 276

mov dx, 115
mov si, dx
add si, 9
mov bx, 0
mov al, 0100b

dloop9:
mov ah, 0ch
int 10h

dloop10:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne dloop10

mov dx, 115
add cx, 1
add bx, 1
add dx, bx
cmp cx, di
jne dloop9

;-----------------
mov cx, 266
mov di, 257

mov dx, 115
mov si, dx
add si, 9
mov bx, 0

dloop11:
mov ah, 0ch
int 10h

dloop12:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne dloop12

mov dx, 115
sub cx, 1
add bx, 1
add dx, bx
cmp cx, di
jne dloop11

;---------------
mov cx, 288
mov di, 297

mov dx, 115
mov si, dx
add si, 9
mov bx, 0
mov al, 0100b

dloop13:
mov ah, 0ch
int 10h

dloop14:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne dloop14

mov dx, 115
add cx, 1
add bx, 1
add dx, bx
cmp cx, di
jne dloop13

;-----------------
mov cx, 287
mov di, 278

mov dx, 115
mov si, dx
add si, 9
mov bx, 0

dloop15:
mov ah, 0ch
int 10h

dloop16:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne dloop16

mov dx, 115
sub cx, 1
add bx, 1
add dx, bx
cmp cx, di
jne dloop15

;------flags--------
mov cx, 242
mov di, 243

mov dx, 103
mov si, 115

lloop1:
mov ah, 0ch
int 10h

lloop2:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne lloop2

add cx, 1
cmp cx, di
jne lloop1

;----------------

mov cx, 242
mov di, 245

mov dx, 104
mov si, 109
mov bx, 0

lloop3:
mov ah, 0ch
int 10h

lloop4:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne lloop4

mov dx, 104
mov si, 109
add cx, 1
add bx, 1
add dx, bx
sub si, bx
cmp cx, di
jne lloop3

;--------flag on roof2---------
mov cx, 266
mov di, 267

mov dx, 103
mov si, 115

lloop5:
mov ah, 0ch
int 10h

lloop6:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne lloop6

add cx, 1
cmp cx, di
jne lloop5

;----------------

mov cx, 266
mov di, 269

mov dx, 104
mov si, 109
mov bx, 0

lloop7:
mov ah, 0ch
int 10h

lloop8:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne lloop8

mov dx, 104
mov si, 109
add cx, 1
add bx, 1
add dx, bx
sub si, bx
cmp cx, di
jne lloop7

;----flag on roof3------
mov cx, 288
mov di, 289

mov dx, 103
mov si, 115

lloop9:
mov ah, 0ch
int 10h

lloop10:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne lloop10

add cx, 1
cmp cx, di
jne lloop9

;----------------

mov cx, 288
mov di, 291

mov dx, 104
mov si, 109
mov bx, 0

lloop11:
mov ah, 0ch
int 10h

lloop12:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne lloop12

mov dx, 104
mov si, 109
add cx, 1
add bx, 1
add dx, bx
sub si, bx
cmp cx, di
jne lloop11

;-----window-----
mov cx, 238
mov di, cx
add di, 4

mov dx, 135
mov si, dx
add si, 9
mov bx, 0
mov al, 1110b

wloop4:
mov ah, 0ch
int 10h

wloop5:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne wloop5

add cx, 1
add bx, 1
mov dx, 135
sub dx, bx
cmp cx, di
jne wloop4

;-----------------
mov cx, 246
mov di, 241

mov dx, 135
mov si, dx
add si, 9
mov bx, 0

wloop1:
mov ah, 0ch
int 10h

wloop2:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne wloop2

sub cx, 1
add bx, 1
mov dx, 135
sub dx, bx
cmp cx, di
jne wloop1

;-----window 2-----
mov cx, 262
mov di, cx
add di, 4

mov dx, 135
mov si, dx
add si, 9
mov bx, 0
mov al, 1110b

wloop7:
mov ah, 0ch
int 10h

wloop8:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne wloop8

add cx, 1
add bx, 1
mov dx, 135
sub dx, bx
cmp cx, di
jne wloop7

;-----------------
mov cx, 270
mov di, 265

mov dx, 135
mov si, dx
add si, 9
mov bx, 0

wloop9:
mov ah, 0ch
int 10h

wloop10:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne wloop10

sub cx, 1
add bx, 1
mov dx, 135
sub dx, bx
cmp cx, di
jne wloop9

;-------window 3--------
mov cx, 284
mov di, cx
add di, 4

mov dx, 135
mov si, dx
add si, 9
mov bx, 0
mov al, 1110b

wloop11:
mov ah, 0ch
int 10h

wloop12:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne wloop12

add cx, 1
add bx, 1
mov dx, 135
sub dx, bx
cmp cx, di
jne wloop11

;-----------------
mov cx, 292
mov di, 287

mov dx, 135
mov si, dx
add si, 9
mov bx, 0

wloop13:
mov ah, 0ch
int 10h

wloop14:
add dx, 1
mov ah, 0ch
int 10h
cmp dx, si
jne wloop14

sub cx, 1
add bx, 1
mov dx, 135
sub dx, bx
cmp cx, di
jne wloop13

;Casexit:
popa 
pop bp
ret
;---------------------------------------
;	Thank You (^_^)
;---------------------------------------