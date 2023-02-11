[org 0x0100]
jmp start
message: db 0xB3 ; string to be printed
message1: db 'X'
message2: db 'O'
length: dw 1


P1Msg: db 'Player 1 wins!!$'
P2Msg: db 'Player 2 wins!!$'
NMag: db 'Game has reached a Draw.$'
BoxCs: dw 842,876,910,1642,1676,1710,2442,2476,2510

val: db 0,0,0,0,0,0,0,0,0
Turn: db 1
; subroutine to clear the screen
clrscr:	push ax
		mov ah,00	
		mov al,03h	; interrupt to clear screen
		int 10h		
		pop ax
		ret
;---------------------------------------------------------------------------
WP1: 	pusha
		push es
		push 0xb800
		pop es
		mov di, 3426
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
;---------------------------------------------------------------------------
WP2: 	pusha
		push es
		push 0xb800
		pop es
		mov di, 3426
		mov si, P2Msg
		mov ah, 0x20
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
;---------------------------------------------------------------------------
WP3: 	pusha
		push es
		push 0xb800
		pop es
		mov di, 3416
		mov si, NMag
		mov ah, 0x20
q3:		mov al, [si]
		cmp al, '$'
		je P3E
		mov [es:di],ax
		add di, 2
		inc si
		jmp q3
P3E:	pop es
		popa
		ret
;---------------------------------------------------------------------------
FullW:	push bp
		mov bp, sp
		pusha
		mov ax, 0
		mov bx, 8
FW:		mov al, [val+bx]
		cmp al, 0
		je exitF
		dec bx
		cmp bx, -1
		je sFull
		jmp FW
sFull:	mov ax, 1
		mov [bp+4], ax
exitF:	popa
		pop bp
		ret
;---------------------------------------------------------------------------
Switch:	pusha
		mov al, [Turn]
		cmp al, 1
		jne p1v
		mov al, 2
		mov [Turn], al
		jmp exitS
p1v:	mov al, 1
		mov [Turn], al
exitS:	popa
		ret
;---------------------------------------------------------------------------
Win:	push bp
		mov bp, sp
		pusha
		mov ax, 0
		mov bx, 0
		mov al, [val]		; 0,1,2
		mov bl, [val+1]
		cmp al, bl
		jne Ck2
		mov bl, [val+2]
		cmp al, bl
		jne Ck2
		mov [bp+4], ax
		jmp winE

Ck2:	mov bl, [val+3]		;0,3,6
		cmp al, bl
		jne Ck3
		mov bl, [val+6]
		cmp al, bl
		jne Ck3
		mov [bp+4], ax
		jmp winE

Ck3:	mov bl, [val+4]		;0,4,8
		cmp al, bl
		jne Ck4
		mov bl, [val+8]
		cmp al, bl
		jne Ck4
		mov [bp+4], ax
		jmp winE

Ck4:	mov al, [val+2]		;2,4,6
		mov bl, [val+4]
		cmp al, bl
		jne Ck5
		mov bl, [val+6]
		cmp al, bl
		jne Ck5
		mov [bp+4], ax
		jmp winE

Ck5:	mov al, [val+3]		;3,4,5
		mov bl, [val+4]
		cmp al, bl
		jne Ck6
		mov bl, [val+5]
		cmp al, bl
		jne Ck6
		mov [bp+4], ax
		jmp winE

Ck6:	mov al, [val+6]		;6,7,8
		mov bl, [val+7]
		cmp al, bl
		jne Ck7
		mov bl, [val+8]
		cmp al, bl
		jne Ck7
		mov [bp+4], ax
		jmp winE

Ck7:	mov al, [val+1]		;1,4,7
		mov bl, [val+4]
		cmp al, bl
		jne Ck8
		mov bl, [val+7]
		cmp al, bl
		jne Ck8
		mov [bp+4], ax
		jmp winE

Ck8:	mov al, [val+2]		;2,5,8
		mov bl, [val+5]
		cmp al, bl
		jne winE
		mov bl, [val+8]
		cmp al, bl
		jne winE
		mov [bp+4], ax

winE:	popa
		pop bp
		ret
;---------------------------------------------------------------------------
Zero:	push bp
		mov bp, sp
		pusha
		push es
		mov ah, 0x20
		mov al, 178
		mov bx, 0xb800
		mov es, bx
		mov di, [bp+4]
		mov bx, 2
		mov [es:di+bx], ax
		add bx, 2
		mov [es:di+bx], ax
		add bx, 162
		mov [es:di+bx], ax
		add bx, 158
		mov [es:di+bx], ax
		sub bx, 2
		mov [es:di+bx], ax
		sub bx, 162
		mov [es:di+bx], ax
		pop es
		popa
		pop bp
		ret 2
;---------------------------------------------------------------------------
Cross:	push bp
		mov bp, sp
		pusha
		push es
		mov ah, 0x20
		mov al, 178
		mov bx, 0xb800
		mov es, bx
		mov di, [bp+4]
		mov bx, 0
		mov [es:di+bx], ax
		add bx, 162
		mov [es:di+bx], ax
		add bx, 164
		mov [es:di+bx], ax
		sub bx, 320
		mov [es:di+bx], ax
		add bx, 158
		mov [es:di+bx], ax
		add bx, 156
		mov [es:di+bx], ax
		pop es
		popa
		pop bp
		ret 2
;---------------------------------------------------------------------------
DisC:	push bp
		mov bp, sp
		pusha
		push es
		push 0xB800
		pop es
		mov bx, 10
		mov word ax, [bp+4]
		mov di, 3998
		mov ch, 0x06
		mov cl, 0x30
		cmp ax, 10
		ja n1
		mov [es:di-2], cx
n1:		cmp ax, 100
		ja ALX
		mov [es:di-4], cx
ALX:	mov dx, 0
		div bx
		mov cl, dl
		add cl, 0x30
		mov [es:di], cx
		sub di, 2
		cmp ax, 0
		jne ALX
		mov word ax, [bp+6]
		mov ch, 0x0A
		mov di, 3838
		mov cl, 0x30
		cmp ax, 10
		ja n2
		mov [es:di-2], cx
n2:		cmp ax, 100
		ja ALY
		mov [es:di-4], cx
ALY:	mov dx, 0
		div bx
		mov cl, dl
		add cl, 0x30
		mov [es:di], cx
		sub di, 2
		cmp ax, 0
		jne ALY
exitC:	pop es
		popa
		pop bp
		ret 4
;---------------------------------------------------------------------------
;subroutine to set the background colour
clr:
push es
push ax
push di
mov ax, 0xb800
mov es, ax ; point es to video base
mov di, 0 ; point di to top left column
next:
mov ax,0420h
mov [es:di],ax
add di, 1 ; move to next screen location
cmp di, 4000 ; has the whole screen cleared
jne next ; if no clear next position
pop di
pop ax
pop es
ret
;---------------------------------------------------------------------------
printRectangle: push bp
mov bp, sp
push es
push ax
push cx
push si
push di
mov ax, 0xb800
mov es, ax ; point es to video base
mov al, 80 ; load al with columns per row
mul byte [bp+12] ; multiply with row number
add ax, [bp+10] ; add col
shl ax, 1 ; turn into byte offset
mov di, ax ; point di to required location

mov ah, [bp+4] ; load attribute in ah
mov cx, [bp+6]
sub cx, [bp+10]

topLine: mov al, 0x5f ; ASCII of <->;

mov [es:di], ax ; show this char on screen
add di, 2 ; move to next screen location
call sleep;
loop topLine ; repeat the operation cx times
mov cx, [bp+8]
sub cx, [bp+12]
add di, 160

rightLine: 
mov al, 0xB3 ; ASCII of <|>;
mov [es:di], ax ; show this char on screen
add di, 160 ; move to next screen location
call sleep;
loop rightLine ; repeat the operation cx times
mov cx, [bp+6]
sub cx, [bp+10]
sub di, 2

bottomLine: mov al, 0x5f ; ASCII of <->;

mov [es:di], ax ; show this char on screen
sub di, 2 ; move to next screen location
call sleep;
loop bottomLine ; repeat the operation cx times
mov cx, [bp+8]
sub cx, [bp+12]
sub di, 160

leftLine: mov al, 0xB3 ; ASCII of <|>;

mov [es:di], ax ; show this char on screen
sub di, 160 ; move to next screen location
call sleep;
loop leftLine ; repeat the operation cx times
pop di
pop si
pop cx
pop ax
pop es
pop bp
ret 10

;---------------------------------------------------------------------------
sleep: ;push cx
;mov cx, 0xFFFF
;delay: loop delay
;pop cx
ret
;---------------------------------------------------------------------------
printstr: push bp
mov bp, sp
push es
push ax
push cx
push si
push di
mov ax, 0xb800
mov es, ax ; point es to video base
mov al, 80 ; load al with columns per row
mul byte [bp+10] ; multiply with y position
add ax, [bp+12] ; add x position
shl ax, 1 ; turn into byte offset
mov di,ax ; point di to required location
mov si, [bp+6] ; point si to string
mov cx, [bp+4] ; load length of string in cx
mov ah, [bp+8] ; load attribute in ah
nextchar: mov al, [si] ; load next char of string
mov [es:di], ax ; show this char on screen
add di, 2 ; move to next screen location
add si, 1 ; move to next char in string
loop nextchar ; repeat the operation cx times
pop di
pop si
pop cx
pop ax
pop es
pop bp
ret 10
;---------------------------------------------------------------------------
line1:

;---------------------------------------------------------------------------
start: ;jmp testS
call clrscr ; call the clrscr subroutine
call clr
mov ax, 1
push ax ; push top
mov ax, 1
push ax ; push left
mov ax, 23
push ax ; push bottom
mov ax, 79
push ax ; push right number
mov ax, 24h ; Red FG
push ax ; push attribute
call printRectangle ; call the printstr subroutine

mov ax, 2
push ax ; push top
mov ax, 3
push ax ; push left
mov ax, 22
push ax ; push bottom
mov ax, 77
push ax ; push right number
mov ax, 24h; Red FG
push ax ; push attribute
call printRectangle ; call the printstr subroutine

mov ax, 3
push ax ; push top
mov ax, 15
push ax ; push left
mov ax, 17
push ax ; push bottom
mov ax, 65
push ax ; push right number
mov ax, 0x25 ; Red FG
push ax ; push attribute
call printRectangle

mov ax, 3
push ax ; push top
mov ax, 31
push ax ; push left
mov ax, 17
push ax ; push bottom
mov ax, 49
push ax ; push right number
mov ax, 0x25 ; Red FG
push ax ; push attribute
call printRectangle

mov ax, 8
push ax ; push top
mov ax, 15
push ax ; push left
mov ax, 12
push ax ; push bottom
mov ax, 65
push ax ; push right number
mov ax, 0x25 ; Red FG
push ax ; push attribute
call printRectangle

mov ax, 19
push ax ; push top
mov ax, 20
push ax ; push left
mov ax, 21
push ax ; push bottom
mov ax, 60
push ax ; push right number
mov ax, 0x28; Red FG
push ax ; push attribute
call printRectangle ; call the printstr subroutine


mov ax, 30
push ax ; push x position
mov ax, 8
push ax ; push y position
mov ax, 0x25 ; blue on green attribute
push ax ; push attribute
mov ax, message
push ax ; push address of message
push word [length] ; push message length
call printstr ; call the printstr subroutine

mov ax, 49
push ax ; push x position
mov ax, 8
push ax ; push y position
mov ax, 0x25 ; blue on green attribute
push ax ; push attribute
mov ax, message
push ax ; push address of message
push word [length] ; push message length
call printstr ; call the printstr subroutine

mov ax, 49
push ax ; push x position
mov ax, 13
push ax ; push y position
mov ax, 0x25 ; blue on green attribute
push ax ; push attribute
mov ax, message
push ax ; push address of message
push word [length] ; push message length
call printstr ; call the printstr subroutine

mov ax, 30
push ax ; push x position
mov ax, 13
push ax ; push y position
mov ax, 0x25 ; blue on green attribute
push ax ; push attribute
mov ax, message
push ax ; push address of message
push word [length] ; push message length
call printstr ; call the printstr subroutine

mov ax, 65
push ax ; push x position
mov ax, 18
push ax ; push y position
mov ax, 0x25 ; blue on green attribute
push ax ; push attribute
mov ax, message
push ax ; push address of message
push word [length] ; push message length
call printstr ; call the printstr subroutine

mov ax, 14
push ax ; push x position
mov ax, 18
push ax ; push y position
mov ax, 0x25 ; blue on green attribute
push ax ; push attribute
mov ax, message
push ax ; push address of message
push word [length] ; push message length
call printstr ; call the printstr subroutine

mov ax, 49
push ax ; push x position
mov ax, 18
push ax ; push y position
mov ax, 0x25 ; blue on green attribute
push ax ; push attribute
mov ax, message
push ax ; push address of message
push word [length] ; push message length
call printstr ; call the printstr subroutine

mov ax, 30
push ax ; push x position
mov ax, 18
push ax ; push y position
mov ax, 0x25 ; blue on green attribute
push ax ; push attribute
mov ax, message
push ax ; push address of message
push word [length] ; push message length
call printstr ; call the printstr subroutine


mov ax, 60
push ax ; push x position
mov ax, 22
push ax ; push y position
mov ax, 0x28 ; blue on green attribute
push ax ; push attribute
mov ax, message
push ax ; push address of message
push word [length] ; push message length
call printstr ; call the printstr subroutine

mov ax, 19
push ax ; push x position
mov ax, 22
push ax ; push y position
mov ax, 0x28 ; blue on green attribute
push ax ; push attribute
mov ax, message
push ax ; push address of message
push word [length] ; push message length
call printstr ; call the printstr subroutine

mov ax, 0
push ax ; push x position
mov ax, 24
push ax ; push y position
mov ax, 0x24 ; blue on green attribute
push ax ; push attribute
mov ax, message
push ax ; push address of message
push word [length] ; push message length
call printstr ; call the printstr subroutine

mov ax, 2
push ax ; push x position
mov ax, 23
push ax ; push y position
mov ax, 0x24 ; blue on green attribute
push ax ; push attribute
mov ax, message
push ax ; push address of message
push word [length] ; push message length
call printstr ; call the printstr subroutine

mov ax, 79
push ax ; push x position
mov ax, 24
push ax ; push y position
mov ax, 0x24 ; blue on green attribute
push ax ; push attribute
mov ax, message
push ax ; push address of message
push word [length] ; push message length
call printstr ; call the printstr subroutine

mov ax, 77
push ax ; push x position
mov ax, 23
push ax ; push y position
mov ax, 0x24 ; blue on green attribute
push ax ; push attribute
mov ax, message
push ax ; push address of message
push word [length] ; push message length
call printstr ; call the printstr subroutine

mov ax, 17
push ax ; push x position
mov ax, 5
push ax ; push y position
mov ax, 0x24 ; blue on green attribute
push ax ; push attribute
mov ax, message1
push ax ; push address of message
push word [length] ; push message length
;call printstr ; call the printstr subroutine

mov ax, 21
push ax ; push x position
mov ax, 6
push ax ; push y position
mov ax, 0x24 ; blue on green attribute
push ax ; push attribute
mov ax, message1
push ax ; push address of message
push word [length] ; push message length
;call printstr ; call the printstr subroutine

mov ax, 19
push ax ; push x position
mov ax, 7
push ax ; push y position
mov ax, 0x24 ; blue on green attribute
push ax ; push attribute
mov ax, message1
push ax ; push address of message
push word [length] ; push message length
;call printstr ; call the printstr subroutine
;---------------------------------------------------------------------------
;
;
;
;
;
; do your main here
;
;
;
;
;---------------------------------------------------------------------------
			mov ax, 1
			int 33h
			mov bx, 0
SGame:		call Game
			push 0
			call FullW
			pop bx
			cmp bx, 1
			je V2			
			push 0
			call Win
			pop ax
			cmp ax, 1
			jne V1
			call WP1
			jmp terminate
V1:			cmp ax, 2
			jne SGame
			call WP2
			jmp terminate
V2:			call WP3
terminate:	mov ax, 0x4c00 ; terminate program
			int 0x21
;---------------------------------------------------------------------------
Game:		pusha
M1:			mov ax, 3
			int 33h
			push cx
			push dx
			call DisC
			cmp cx, 112
			jb M1
			cmp cx, 524
			ja M1
			cmp dx, 32
			jb M1
			cmp dx, 150
			ja M1
			cmp bx, 1
			jne M1

			cmp dx, 72
			ja ROW2
			cmp cx, 240
			ja RC2
			call BOX1
			popa
			ret
RC2:		cmp cx, 394
			ja RC3
			call BOX2
			popa
			ret
RC3:		call BOX3
			popa
			ret
ROW2:		cmp dx, 112
			ja ROW3
			cmp cx, 240
			ja R2C2
			call BOX4
			popa
			ret
R2C2:		cmp cx, 394
			ja R2C3
			call BOX5
			popa
			ret
R2C3:		call BOX6
			popa
			ret
ROW3:		cmp cx, 240
			ja R3C2
			call BOX7
			popa
			ret
R3C2:		cmp cx, 394
			ja R3C3
			call BOX8
			popa
			ret
R3C3:		call BOX9
			popa
			ret
;---------------------------------------------------------------------------
BOX1:		push ax
			mov al, [val]
			cmp al, 0
			jne BX1
			push word [BoxCs]
			mov al, [Turn]
			cmp al, 1
			jne x1
			call Zero
			jmp s1
x1:			call Cross
s1:			mov [val], al
			call Switch
BX1:		pop ax
			ret			


BOX2:		push ax
			mov al, [val+1]
			cmp al, 0
			jne BX2
			push word [BoxCs+2]
			mov al, [Turn]
			cmp al, 1
			jne x2
			call Zero
			jmp s2
x2:			call Cross
s2:			mov [val+1], al
			call Switch
BX2:		pop ax
			ret

BOX3:		push ax
			mov al, [val+2]
			cmp al, 0
			jne BX3
			push word [BoxCs+4]
			mov al, [Turn]
			cmp al, 1
			jne x3
			call Zero
			jmp s3
x3:			call Cross
s3:			mov [val+2], al
			call Switch
BX3:		pop ax
			ret

BOX4:		push ax
			mov al, [val+3]
			cmp al, 0
			jne BX4
			push word [BoxCs+6]
			mov al, [Turn]
			cmp al, 1
			jne x4
			call Zero
			jmp s4
x4:			call Cross
s4:			mov [val+3], al
			call Switch
BX4:		pop ax
			ret

BOX5:		push ax
			mov al, [val+4]
			cmp al, 0
			jne BX5
			push word [BoxCs+8]
			mov al, [Turn]
			cmp al, 1
			jne x5
			call Zero
			jmp s5
x5:			call Cross
s5:			mov [val+4], al
			call Switch
BX5:		pop ax
			ret

BOX6:		push ax
			mov al, [val+5]
			cmp al, 0
			jne BX6
			push word [BoxCs+10]
			mov al, [Turn]
			cmp al, 1
			jne x6
			call Zero
			jmp s6
x6:			call Cross
s6:			mov [val+5], al
			call Switch
BX6:		pop ax
			ret

BOX7:		push ax
			mov al, [val+6]
			cmp al, 0
			jne BX7
			push word [BoxCs+12]
			mov al, [Turn]
			cmp al, 1
			jne x7
			call Zero
			jmp s7
x7:			call Cross
s7:			mov [val+6], al
			call Switch
BX7:		pop ax
			ret

BOX8:		push ax
			mov al, [val+7]
			cmp al, 0
			jne BX8
			push word [BoxCs+14]
			mov al, [Turn]
			cmp al, 1
			jne x8
			call Zero
			jmp s8
x8:			call Cross
s8:			mov [val+7], al
			call Switch
BX8:		pop ax
			ret

BOX9:		push ax
			mov al, [val+8]
			cmp al, 0
			jne BX9
			push word [BoxCs+16]
			mov al, [Turn]
			cmp al, 1
			jne x9
			call Zero
			jmp s9
x9:			call Cross
s9:			mov [val+8], al
			call Switch
BX9:		pop ax
			ret