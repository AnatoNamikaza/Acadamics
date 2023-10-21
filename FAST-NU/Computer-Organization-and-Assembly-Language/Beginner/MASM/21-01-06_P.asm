INCLUDE Irvine32.inc

;=========================================
.data
;=========================================
	background db 3600 dup(' '), 0
	controls byte 244," Press W for UP | Press S for DOWN | Press A for LEFT | Press D for RIGHT | Press E to exit | Press R to restart Game ",245, 0
	Goal byte " Target:- Make a tile of 2048 to win the Game", 0
	ms byte "Exiting the Game......", 0
	sDis byte "Scores: ", 0
	GameTitle db "{> GAME  2048 <}",0
	B1 db 120 dup(177), 0
	B2 db 52 dup('~'), 0
	B3 db 46 dup('_'), 0
	B4 db 6 dup(196), 0
	SC db "        ", 0
	GameBoard dw 16 dup(0), 0 
;	GameBoard dw 16 dup(2048);
;=========================================
.code
;=========================================
main PROC
	call WhiteScr
	mov esi, offset GameBoard

WinCheck:
	mov ebx, 0
	mov cx, 16
	mov ax, 2048
l1:	cmp ax, [GameBoard+ebx]
	jb terminate
	add bx, 2
	dec cx
	jnz l1
	call RanNum

Gameloop:
	call Frame
	call Board
	call readchar
	cmp al, 'e'
	je terminate
	cmp al, 'w'
	je _w
	cmp al, 's'
	je _s
	cmp al, 'a'
	je _a
	cmp al, 'd'
	je _d
	cmp al, 'r'
	je _r
	jmp WinCheck

;=========================================
;-------- Control Key Procedures ---------
;=========================================

_w:	call mvU
	jmp WinCheck
	
_s:	call mvD
	jmp WinCheck

_a:	call mvL
	jmp WinCheck

_d:	call mvR
	jmp WinCheck

_r: mov ebx, 0
	mov cx, 16
l2:	mov [GameBoard+ebx], 0
	add bx, 2
	dec cx
	jnz l2
	jmp WinCheck

;=========================================
;----------- Move Up Procedure -----------
;=========================================

mvU:pusha

;---- Board Coulum 1 ----
;-- Block 1 --

	mov edi, 4

C1B1:mov dx, [GameBoard]
	mov cx, 3
	mov ebx, 8
U1:	mov ax, [GameBoard+ebx]
	cmp ax, 0
	jne U2
	add bx, 8
	dec cx
	jnz U1

U2:	cmp dx, 0
	jne U3
	mov [GameBoard], ax
	mov [GameBoard+ebx], dx
	jmp C1B2

U3:	cmp dx, ax
	jne C1B2
	add ax, dx
	mov dx, 0
	mov [GameBoard], ax
	mov [GameBoard+ebx], dx

;-- Block 2 --

C1B2:dec di
	cmp di, 2
	ja C1B1
	mov dx, [GameBoard+8]
	mov cx, 2
	mov ebx, 16
U4:	mov ax, [GameBoard+ebx]
	cmp ax, 0
	jne U5
	add bx, 8
	dec cx
	jnz U4

U5:	cmp dx, 0
	jne U6
	mov [GameBoard+8], ax
	mov [GameBoard+ebx], dx
	jmp C1B3

U6:	cmp dx, ax
	jne C1B3
	add ax, dx
	mov dx, 0
	mov [GameBoard+8], ax
	mov [GameBoard+ebx], dx

;-- Block 3 --

C1B3:cmp di, 0
	jne C1B2
	mov dx, [GameBoard+16]
	mov ebx, 24
	mov ax, [GameBoard+ebx]
	
	cmp dx, 0
	jne U8
	mov [GameBoard+16], ax
	mov [GameBoard+ebx], dx
	jmp C2B1v

U8:	cmp dx, ax
	jne C2B1v
	add ax, dx
	mov dx, 0
	mov [GameBoard+16], ax
	mov [GameBoard+ebx], dx

;---- Board Coulum 2 ----
;-- Block 1 --

C2B1v:	mov edi, 4

C2B1:mov dx, [GameBoard+2]
	mov cx, 3
	mov ebx, 10
U9:	mov ax, [GameBoard+ebx]
	cmp ax, 0
	jne U10
	add bx, 8
	dec cx
	jnz U9

U10:cmp dx, 0
	jne U11
	mov [GameBoard+2], ax
	mov [GameBoard+ebx], dx
	jmp C2B2

U11:cmp dx, ax
	jne C2B2
	add ax, dx
	mov dx, 0
	mov [GameBoard+2], ax
	mov [GameBoard+ebx], dx

;-- Block 2 --

C2B2:dec di
	cmp di, 2
	ja C2B1
	mov dx, [GameBoard+10]
	mov cx, 2
	mov ebx, 18
U12:mov ax, [GameBoard+ebx]
	cmp ax, 0
	jne U13
	add bx, 8
	dec cx
	jnz U12

U13:cmp dx, 0
	jne U14
	mov [GameBoard+10], ax
	mov [GameBoard+ebx], dx
	jmp C2B3

U14:cmp dx, ax
	jne C2B3
	add ax, dx
	mov dx, 0
	mov [GameBoard+10], ax
	mov [GameBoard+ebx], dx

;-- Block 3 --

C2B3:cmp di, 0
	jne C2B2
	mov dx, [GameBoard+18]
	mov ebx, 26
	mov ax, [GameBoard+ebx]
	cmp dx, 0
	jne U15
	mov [GameBoard+18], ax
	mov [GameBoard+ebx], dx
	jmp C3B1v

U15:cmp dx, ax
	jne C3B1v
	add ax, dx
	mov dx, 0
	mov [GameBoard+18], ax
	mov [GameBoard+ebx], dx

;---- Board Coulum 3 ----
;-- Block 1 --

C3B1v:	mov edi, 4

C3B1:mov dx, [GameBoard+4]
	mov cx, 3
	mov ebx, 12
U16:mov ax, [GameBoard+ebx]
	cmp ax, 0
	jne U17
	add bx, 8
	dec cx
	jnz U16

U17:cmp dx, 0
	jne U18
	mov [GameBoard+4], ax
	mov [GameBoard+ebx], dx
	jmp C3B2

U18:cmp dx, ax
	jne C3B2
	add ax, dx
	mov dx, 0
	mov [GameBoard+4], ax
	mov [GameBoard+ebx], dx

;-- Block 2 --

C3B2:dec di
	cmp di, 2
	ja C3B1
	mov dx, [GameBoard+12]
	mov cx, 2
	mov ebx, 20
U19:mov ax, [GameBoard+ebx]
	cmp ax, 0
	jne U20
	add bx, 8
	dec cx
	jnz U19

U20:cmp dx, 0
	jne U21
	mov [GameBoard+12], ax
	mov [GameBoard+ebx], dx
	jmp C3B3

U21:cmp dx, ax
	jne C3B3
	add ax, dx
	mov dx, 0
	mov [GameBoard+12], ax
	mov [GameBoard+ebx], dx

;-- Block 3 --

C3B3:cmp di, 0
	jne C3B2
	mov dx, [GameBoard+20]
	mov ebx, 28
	mov ax, [GameBoard+ebx]
	cmp dx, 0
	jne U22
	mov [GameBoard+20], ax
	mov [GameBoard+ebx], dx
	jmp C4B1v

U22:cmp dx, ax
	jne C4B1v
	add ax, dx
	mov dx, 0
	mov [GameBoard+20], ax
	mov [GameBoard+ebx], dx

;---- Board Coulum 4 ----
;-- Block 1 --

C4B1v:	mov edi, 4

C4B1:mov dx, [GameBoard+6]
	mov cx, 3
	mov ebx, 14
U23:mov ax, [GameBoard+ebx]
	cmp ax, 0
	jne U24
	add bx, 8
	dec cx
	jnz U23

U24:cmp dx, 0
	jne U25
	mov [GameBoard+6], ax
	mov [GameBoard+ebx], dx
	jmp C4B2

U25:cmp dx, ax
	jne C4B2
	add ax, dx
	mov dx, 0
	mov [GameBoard+6], ax
	mov [GameBoard+ebx], dx

;-- Block 2 --

C4B2:dec di
	cmp di, 2
	ja C4B1
	mov dx, [GameBoard+14]
	mov cx, 2
	mov ebx, 22
U26:mov ax, [GameBoard+ebx]
	cmp ax, 0
	jne U27
	add bx, 8
	dec cx
	jnz U26

U27:cmp dx, 0
	jne U28
	mov [GameBoard+14], ax
	mov [GameBoard+ebx], dx
	jmp C4B3

U28:cmp dx, ax
	jne C4B3
	add ax, dx
	mov dx, 0
	mov [GameBoard+14], ax
	mov [GameBoard+ebx], dx

;-- Block 3 --

C4B3:cmp di, 0
	jne C4B2
	mov dx, [GameBoard+22]
	mov ebx, 30
	mov ax, [GameBoard+ebx]
	cmp dx, 0
	jne U29
	mov [GameBoard+22], ax
	mov [GameBoard+ebx], dx
	jmp Ue

U29:cmp dx, ax
	jne Ue
	add ax, dx
	mov dx, 0
	mov [GameBoard+22], ax
	mov [GameBoard+ebx], dx

Ue:	popa
	ret

;=========================================
;---------- Move Down Procedure ----------
;=========================================

mvD:pusha

;---- Board Coulum 1 ----
;-- Block 1 --

	mov edi, 4

DC1B1:mov dx, [GameBoard+24]
	mov cx, 3
	mov ebx, 24
D1:	sub bx, 8
	mov ax, [GameBoard+ebx]
	cmp ax, 0
	jne D2
	dec cx
	jnz D1

D2:	cmp dx, 0
	jne D3
	mov [GameBoard+24], ax
	mov [GameBoard+ebx], dx
	jmp DC1B2

D3:	cmp dx, ax
	jne DC1B2
	add ax, dx
	mov dx, 0
	mov [GameBoard+24], ax
	mov [GameBoard+ebx], dx

;-- Block 2 --

DC1B2:dec di
	cmp di, 2 
	ja DC1B1
	mov dx, [GameBoard+16]
	mov cx, 2
	mov ebx, 16
D4:	sub bx, 8
	mov ax, [GameBoard+ebx]
	cmp ax, 0
	jne D5
	dec cx
	jnz D4

D5:	cmp dx, 0
	jne D6
	mov [GameBoard+16], ax
	mov [GameBoard+ebx], dx
	jmp DC1B3

D6:	cmp dx, ax
	jne DC1B3
	add ax, dx
	mov dx, 0
	mov [GameBoard+16], ax
	mov [GameBoard+ebx], dx

;-- Block 3 --

DC1B3:cmp di, 0
	jne DC1B2
	mov dx, [GameBoard+8]
	mov ax, [GameBoard]
	cmp dx, 0
	jne D8
	mov [GameBoard+8], ax
	mov [GameBoard], dx
	jmp DC2B1v

D8:	cmp dx, ax
	jne DC2B1v
	add ax, dx
	mov dx, 0
	mov [GameBoard+8], ax
	mov [GameBoard], dx

;---- Board Coulum 2 ----
;-- Block 1 --

DC2B1v: mov edi, 4

DC2B1:mov dx, [GameBoard+26]
	mov cx, 3
	mov ebx, 26
D9:	sub bx, 8
	mov ax, [GameBoard+ebx]
	cmp ax, 0
	jne D10
	dec cx
	jnz D9

D10:cmp dx, 0
	jne D11
	mov [GameBoard+26], ax
	mov [GameBoard+ebx], dx
	jmp DC2B2

D11:cmp dx, ax
	jne DC2B2
	add ax, dx
	mov dx, 0
	mov [GameBoard+26], ax
	mov [GameBoard+ebx], dx

;-- Block 2 --

DC2B2:dec di
	cmp di, 2
	ja DC2B1
	mov dx, [GameBoard+18]
	mov cx, 2
	mov ebx, 18
D12:sub bx, 8
	mov ax, [GameBoard+ebx]
	cmp ax, 0
	jne D13
	dec cx
	jnz D12

D13:cmp dx, 0
	jne D14
	mov [GameBoard+18], ax
	mov [GameBoard+ebx], dx
	jmp DC2B3

D14:cmp dx, ax
	jne DC2B3
	add ax, dx
	mov dx, 0
	mov [GameBoard+18], ax
	mov [GameBoard+ebx], dx

;-- Block 3 --

DC2B3:cmp di, 0
	jne DC2B2
	mov dx, [GameBoard+10]
	mov ax, [GameBoard+2]
	cmp dx, 0
	jne D15
	mov [GameBoard+10], ax
	mov [GameBoard+2], dx
	jmp DC3B1v

D15:cmp dx, ax
	jne DC3B1v
	add ax, dx
	mov dx, 0
	mov [GameBoard+10], ax
	mov [GameBoard+2], dx

;---- Board Coulum 3 ----
;-- Block 1 --

DC3B1v: mov edi, 4

DC3B1:mov dx, [GameBoard+28]
	mov cx, 3
	mov ebx, 28
D16:sub bx, 8
	mov ax, [GameBoard+ebx]
	cmp ax, 0
	jne D17
	dec cx
	jnz D16

D17:cmp dx, 0
	jne D18
	mov [GameBoard+28], ax
	mov [GameBoard+ebx], dx
	jmp DC3B2

D18:cmp dx, ax
	jne DC3B2
	add ax, dx
	mov dx, 0
	mov [GameBoard+28], ax
	mov [GameBoard+ebx], dx

;-- Block 2 --

DC3B2:dec di
	cmp di, 2
	ja DC3B1
	mov dx, [GameBoard+20]
	mov cx, 2
	mov ebx, 20
D19:sub bx, 8
	mov ax, [GameBoard+ebx]
	cmp ax, 0
	jne D20
	dec cx
	jnz D19

D20:cmp dx, 0
	jne D21
	mov [GameBoard+20], ax
	mov [GameBoard+ebx], dx
	jmp DC3B3

D21:cmp dx, ax
	jne DC3B3
	add ax, dx
	mov dx, 0
	mov [GameBoard+20], ax
	mov [GameBoard+ebx], dx

;-- Block 3 --

DC3B3:cmp di, 0
	jne DC3B2
	mov dx, [GameBoard+12]
	mov ax, [GameBoard+4]
	cmp dx, 0
	jne D22
	mov [GameBoard+12], ax
	mov [GameBoard+4], dx
	jmp DC4B1v

D22:cmp dx, ax
	jne DC4B1v
	add ax, dx
	mov dx, 0
	mov [GameBoard+12], ax
	mov [GameBoard+4], dx

;---- Board Coulum 4 ----
;-- Block 1 --

DC4B1v: mov edi, 4

DC4B1:mov dx, [GameBoard+30]
	mov cx, 3
	mov ebx, 30
D23:sub bx, 8
	mov ax, [GameBoard+ebx]
	cmp ax, 0
	jne D24
	dec cx
	jnz D23

D24:cmp dx, 0
	jne D25
	mov [GameBoard+30], ax
	mov [GameBoard+ebx], dx
	jmp DC4B2

D25:cmp dx, ax
	jne DC4B2
	add ax, dx
	mov dx, 0
	mov [GameBoard+30], ax
	mov [GameBoard+ebx], dx

;-- Block 2 --

DC4B2:dec di
	cmp di, 2
	ja DC4B1
	mov dx, [GameBoard+22]
	mov cx, 2
	mov ebx, 22
D26:sub bx, 8
	mov ax, [GameBoard+ebx]
	cmp ax, 0
	jne D27
	dec cx
	jnz D26

D27:cmp dx, 0
	jne D28
	mov [GameBoard+22], ax
	mov [GameBoard+ebx], dx
	jmp DC4B3

D28:cmp dx, ax
	jne DC4B3
	add ax, dx
	mov dx, 0
	mov [GameBoard+22], ax
	mov [GameBoard+ebx], dx

;-- Block 3 --

DC4B3:cmp di, 0
	jne DC4B2
	mov dx, [GameBoard+14]
	mov ax, [GameBoard+6]
	cmp dx, 0
	jne D29
	mov [GameBoard+14], ax
	mov [GameBoard+6], dx
	jmp De

D29:cmp dx, ax
	jne De
	add ax, dx
	mov dx, 0
	mov [GameBoard+14], ax
	mov [GameBoard+6], dx

De:popa
	ret

;=========================================
;--------- Move Right Procedure ----------
;=========================================

mvR:pusha

;---- Board Row 1 ----
;-- Block 1 --
	
	mov edi, 4

L1B1:mov dx, [GameBoard+6]
	mov cx, 3
	mov ebx, 6
Lv1:sub bx, 2
	mov ax, [GameBoard+ebx]
	cmp ax, 0
	jne Lv2
	dec cx
	jnz Lv1

Lv2:cmp dx, 0
	jne L3
	mov [GameBoard+6], ax
	mov [GameBoard+ebx], dx
	jmp L1B2

L3:	cmp dx, ax
	jne L1B2
	add ax, dx
	mov dx, 0
	mov [GameBoard+6], ax
	mov [GameBoard+ebx], dx

;-- Block 2 --

L1B2:dec di
	cmp di, 2
	ja L1B1
	mov dx, [GameBoard+4]
	mov cx, 2
	mov ebx, 4
L4:	sub bx, 2
	mov ax, [GameBoard+ebx]
	cmp ax, 0
	jne L5
	dec cx
	jnz L4

L5:	cmp dx, 0
	jne L6
	mov [GameBoard+4], ax
	mov [GameBoard+ebx], dx
	jmp L1B3

L6:	cmp dx, ax
	jne L1B3
	add ax, dx
	mov dx, 0
	mov [GameBoard+4], ax
	mov [GameBoard+ebx], dx

;-- Block 3 --

L1B3:cmp di, 0
	jne L1B2
	mov dx, [GameBoard+2]
	mov ax, [GameBoard]
	
	cmp dx, 0
	jne L8
	mov [GameBoard+2], ax
	mov [GameBoard], dx
	jmp L2B1v

L8:	cmp dx, ax
	jne L2B1v
	add ax, dx
	mov dx, 0
	mov [GameBoard+2], ax
	mov [GameBoard], dx

;---- Board Row 2 ----
;-- Block 1 --

L2B1v: mov edi, 4

L2B1:mov dx, [GameBoard+14]
	mov cx, 3
	mov ebx, 14
L9:	sub bx, 2
	mov ax, [GameBoard+ebx]
	cmp ax, 0
	jne L10
	dec cx
	jnz L9

L10:cmp dx, 0
	jne L11
	mov [GameBoard+14], ax
	mov [GameBoard+ebx], dx
	jmp L2B2

L11:cmp dx, ax
	jne L2B2
	add ax, dx
	mov dx, 0
	mov [GameBoard+14], ax
	mov [GameBoard+ebx], dx

;-- Block 2 --

L2B2:dec di
	cmp di, 2
	ja L2B1
	mov dx, [GameBoard+12]
	mov cx, 2
	mov ebx, 12
L12:sub bx, 2
	mov ax, [GameBoard+ebx]
	cmp ax, 0
	jne L13
	dec cx
	jnz L12

L13:cmp dx, 0
	jne L14
	mov [GameBoard+12], ax
	mov [GameBoard+ebx], dx
	jmp L2B3

L14:cmp dx, ax
	jne L2B3
	add ax, dx
	mov dx, 0
	mov [GameBoard+12], ax
	mov [GameBoard+ebx], dx

;-- Block 3 --

L2B3:cmp di, 0
	jne L2B2
	mov dx, [GameBoard+10]
	mov ax, [GameBoard+8]
	cmp dx, 0
	jne L15
	mov [GameBoard+10], ax
	mov [GameBoard+8], dx
	jmp L3B1v

L15:cmp dx, ax
	jne L3B1v
	add ax, dx
	mov dx, 0
	mov [GameBoard+10], ax
	mov [GameBoard+8], dx

;---- Board Row 3 ----
;-- Block 1 --

L3B1v: mov edi, 4

L3B1:mov dx, [GameBoard+22]
	mov cx, 3
	mov ebx, 22
L16:sub bx, 2
	mov ax, [GameBoard+ebx]
	cmp ax, 0
	jne L17
	dec cx
	jnz L16

L17:cmp dx, 0
	jne L18
	mov [GameBoard+22], ax
	mov [GameBoard+ebx], dx
	jmp L3B2

L18:cmp dx, ax
	jne L3B2
	add ax, dx
	mov dx, 0
	mov [GameBoard+22], ax
	mov [GameBoard+ebx], dx

;-- Block 2 --

L3B2:dec di
	cmp di, 2
	ja L3B1
	mov dx, [GameBoard+20]
	mov cx, 2
	mov ebx, 20
L19:sub bx, 2
	mov ax, [GameBoard+ebx]
	cmp ax, 0
	jne L20
	dec cx
	jnz L19

L20:cmp dx, 0
	jne L21
	mov [GameBoard+20], ax
	mov [GameBoard+ebx], dx
	jmp L3B3

L21:cmp dx, ax
	jne L3B3
	add ax, dx
	mov dx, 0
	mov [GameBoard+20], ax
	mov [GameBoard+ebx], dx

;-- Block 3 --

L3B3:cmp di, 0
	jne L3B2
	mov dx, [GameBoard+18]
	mov ax, [GameBoard+16]
	cmp dx, 0
	jne L22
	mov [GameBoard+18], ax
	mov [GameBoard+16], dx
	jmp L4B1v

L22:cmp dx, ax
	jne L4B1v
	add ax, dx
	mov dx, 0
	mov [GameBoard+18], ax
	mov [GameBoard+16], dx

;---- Board Coulum 4 ----
;-- Block 1 --

L4B1v: mov edi, 4

L4B1:mov dx, [GameBoard+30]
	mov cx, 3
	mov ebx, 30
L23:sub bx, 2
	mov ax, [GameBoard+ebx]
	cmp ax, 0
	jne L24
	dec cx
	jnz L23

L24:cmp dx, 0
	jne L25
	mov [GameBoard+30], ax
	mov [GameBoard+ebx], dx
	jmp L4B2

L25:cmp dx, ax
	jne L4B2
	add ax, dx
	mov dx, 0
	mov [GameBoard+30], ax
	mov [GameBoard+ebx], dx

;-- Block 2 --

L4B2:dec di
	cmp di, 2
	ja L4B1
	mov dx, [GameBoard+28]
	mov cx, 2
	mov ebx, 28
L26:sub bx, 2
	mov ax, [GameBoard+ebx]
	cmp ax, 0
	jne L27
	dec cx
	jnz L26

L27:cmp dx, 0
	jne L28
	mov [GameBoard+28], ax
	mov [GameBoard+ebx], dx
	jmp L4B3

L28:cmp dx, ax
	jne L4B3
	add ax, dx
	mov dx, 0
	mov [GameBoard+28], ax
	mov [GameBoard+ebx], dx

;-- Block 3 --

L4B3:cmp di, 0
	jne L4B2
	mov dx, [GameBoard+26]
	mov ax, [GameBoard+24]
	cmp dx, 0
	jne L29
	mov [GameBoard+26], ax
	mov [GameBoard+24], dx
	jmp Rv

L29:cmp dx, ax
	jne Rv
	add ax, dx
	mov dx, 0
	mov [GameBoard+26], ax
	mov [GameBoard+24], dx

Rv:	popa
	ret

;=========================================
;---------- Move Left Procedure ----------
;=========================================

mvL:pusha

;---- Board Row 1 ----
;-- Block 1 --

	mov edi, 4

R1B1:mov dx, [GameBoard]
	mov cx, 3
	mov ebx, 0
R1:	add bx, 2
	mov ax, [GameBoard+ebx]
	cmp ax, 0
	jne R2
	dec cx
	jnz R1

R2:	cmp dx, 0
	jne R3
	mov [GameBoard], ax
	mov [GameBoard+ebx], dx
	jmp R1B2

R3:	cmp dx, ax
	jne R1B2
	add ax, dx
	mov dx, 0
	mov [GameBoard], ax
	mov [GameBoard+ebx], dx

;-- Block 2 --

R1B2:dec di
	cmp di, 2
	ja R1B1
	mov dx, [GameBoard+2]
	mov cx, 2
	mov ebx, 2
R4:	add bx, 2
	mov ax, [GameBoard+ebx]
	cmp ax, 0
	jne R5
	dec cx
	jnz R4

R5:	cmp dx, 0
	jne R6
	mov [GameBoard+2], ax
	mov [GameBoard+ebx], dx
	jmp R1B3

R6:	cmp dx, ax
	jne R1B3
	add ax, dx
	mov dx, 0
	mov [GameBoard+2], ax
	mov [GameBoard+ebx], dx

;-- Block 3 --

R1B3:cmp di, 0
	jne R1B2
	mov dx, [GameBoard+4]
	mov ax, [GameBoard+6]
	cmp dx, 0
	jne R8
	mov [GameBoard+4], ax
	mov [GameBoard+6], dx
	jmp R2B1v

R8:	cmp dx, ax
	jne R2B1v
	add ax, dx
	mov dx, 0
	mov [GameBoard+4], ax
	mov [GameBoard+6], dx

;---- Board Row 2 ----
;-- Block 1 --

R2B1v: mov edi, 4

R2B1:mov dx, [GameBoard+8]
	mov cx, 3
	mov ebx, 8
R9:	add bx, 2
	mov ax, [GameBoard+ebx]
	cmp ax, 0
	jne R10
	dec cx
	jnz R9

R10:cmp dx, 0
	jne R11
	mov [GameBoard+8], ax
	mov [GameBoard+ebx], dx
	jmp R2B2

R11:cmp dx, ax
	jne R2B2
	add ax, dx
	mov dx, 0
	mov [GameBoard+8], ax
	mov [GameBoard+ebx], dx

;-- Block 2 --

R2B2:dec di
	cmp di, 2
	ja R2B1
	mov dx, [GameBoard+10]
	mov cx, 2
	mov ebx, 10
R12:add bx, 2
	mov ax, [GameBoard+ebx]
	cmp ax, 0
	jne R13
	dec cx
	jnz R12

R13:cmp dx, 0
	jne R14
	mov [GameBoard+10], ax
	mov [GameBoard+ebx], dx
	jmp R2B3

R14:cmp dx, ax
	jne R2B3
	add ax, dx
	mov dx, 0
	mov [GameBoard+10], ax
	mov [GameBoard+ebx], dx

;-- Block 3 --

R2B3:cmp di, 0
	jne R2B2
	mov dx, [GameBoard+12]
	mov ax, [GameBoard+14]
	cmp dx, 0
	jne R15
	mov [GameBoard+12], ax
	mov [GameBoard+14], dx
	jmp R3B1v

R15:cmp dx, ax
	jne R3B1v
	add ax, dx
	mov dx, 0
	mov [GameBoard+12], ax
	mov [GameBoard+14], dx

;---- Board Row 3 ----
;-- Block 1 --

R3B1v: mov edi, 4

R3B1:mov dx, [GameBoard+16]
	mov cx, 3
	mov ebx, 16
R16:add bx, 2
	mov ax, [GameBoard+ebx]
	cmp ax, 0
	jne R17
	dec cx
	jnz R16

R17:cmp dx, 0
	jne R18
	mov [GameBoard+16], ax
	mov [GameBoard+ebx], dx
	jmp R3B2

R18:cmp dx, ax
	jne R3B2
	add ax, dx
	mov dx, 0
	mov [GameBoard+16], ax
	mov [GameBoard+ebx], dx

;-- Block 2 --

R3B2:dec di
	cmp di, 2
	ja R3B1
	mov dx, [GameBoard+18]
	mov cx, 2
	mov ebx, 18
R19:add bx, 2
	mov ax, [GameBoard+ebx]
	cmp ax, 0
	jne R20
	dec cx
	jnz R19

R20:cmp dx, 0
	jne R21
	mov [GameBoard+18], ax
	mov [GameBoard+ebx], dx
	jmp R3B3

R21:cmp dx, ax
	jne R3B3
	add ax, dx
	mov dx, 0
	mov [GameBoard+18], ax
	mov [GameBoard+ebx], dx

;-- Block 3 --

R3B3:cmp di, 0
	jne R3B2
	mov dx, [GameBoard+20]
	mov ax, [GameBoard+22]
	cmp dx, 0
	jne R22
	mov [GameBoard+20], ax
	mov [GameBoard+22], dx
	jmp R4B1v

R22:cmp dx, ax
	jne R4B1v
	add ax, dx
	mov dx, 0
	mov [GameBoard+20], ax
	mov [GameBoard+22], dx

;---- Board Coulum 4 ----
;-- Block 1 --

R4B1v: mov edi, 4

R4B1:mov dx, [GameBoard+24]
	mov cx, 3
	mov ebx, 24
R23:add bx, 2
	mov ax, [GameBoard+ebx]
	cmp ax, 0
	jne R24
	dec cx
	jnz R23

R24:cmp dx, 0
	jne R25
	mov [GameBoard+24], ax
	mov [GameBoard+ebx], dx
	jmp R4B2

R25:cmp dx, ax
	jne R4B2
	add ax, dx
	mov dx, 0
	mov [GameBoard+24], ax
	mov [GameBoard+ebx], dx

;-- Block 2 --

R4B2:dec di
	cmp di, 2
	ja R4B1
	mov dx, [GameBoard+26]
	mov cx, 2
	mov ebx, 26
R26:add bx, 2
	mov ax, [GameBoard+ebx]
	cmp ax, 0
	jne R27
	dec cx
	jnz R26

R27:cmp dx, 0
	jne R28
	mov [GameBoard+26], ax
	mov [GameBoard+ebx], dx
	jmp R4B3

R28:cmp dx, ax
	jne R4B3
	add ax, dx
	mov dx, 0
	mov [GameBoard+26], ax
	mov [GameBoard+ebx], dx

;-- Block 3 --

R4B3:cmp di, 0
	jne R4B2
	mov dx, [GameBoard+28]
	mov ax, [GameBoard+30]
	cmp dx, 0
	jne R29
	mov [GameBoard+28], ax
	mov [GameBoard+30], dx
	jmp Lv

R29:cmp dx, ax
	jne Lv
	add ax, dx
	mov dx, 0
	mov [GameBoard+28], ax
	mov [GameBoard+30], dx

Lv:	popa
	ret

;=========================================
;--- Random Number Generator Procedure ---
;=========================================
RanNum:
	pusha
	mov ebx, 0
	mov cx, 16
G1:	mov ax, [GameBoard+ebx]
	cmp ax, 0
	je G2
	add bx, 2
	dec cx
	jnz G1
	jmp G3	
G2:	call Randomize
	mov eax, 16
	call RandomRange
	mov ebx, 2
	mul ebx
	mov ebx, eax
	mov ax, [esi+ebx]
	cmp ax, 0
	jne G2
	mov ax, 2
	mov [esi+ebx], ax
G3:	popa
	ret
;=========================================
;-------- Clear Scream Procedure ---------
;=========================================
WhiteScr:
	pusha
	call Clrscr
	mov eax, (white*16)+ black 
	call SetTextColor
	mov edx, offset background
	call writestring
	popa
	ret
;=========================================
;----------- Board Procedure -------------
;=========================================
Board:
	pusha

;__ 1st Row of the board __

	mov dl, 42
	mov dh, 6
	call GotoXy
	mov edx, offset SC
	call writestring
	mov dl, 42
	mov dh, 6
	call GotoXy
	mov ax, [esi]	
	call writedec

	mov dl, 52
	mov dh, 6
	call GotoXy
	mov edx, offset SC
	call writestring
	mov dl, 52
	mov dh, 6
	call GotoXy
	mov ax, [esi+2]
	call writedec

	mov dl, 62
	mov dh, 6
	call GotoXy
	mov edx, offset SC
	call writestring
	mov dl, 62
	mov dh, 6
	call GotoXy
	mov ax, [esi+4]
	call writedec
	
	mov dl, 72
	mov dh, 6
	call GotoXy
	mov edx, offset SC
	call writestring
	mov dl, 72
	mov dh, 6
	call GotoXy
	mov ax, [esi+6]
	call writedec

;__ 2nd Row of the board __
	
	mov dl, 42
	mov dh, 11
	call GotoXy
	mov edx, offset SC
	call writestring
	mov dl, 42
	mov dh, 11
	call GotoXy
	mov ax, [esi+8]
	call writedec

	mov dl, 52
	mov dh, 11
	call GotoXy
	mov edx, offset SC
	call writestring
	mov dl, 52
	mov dh, 11
	call GotoXy
	mov ax, [esi+10]
	call writedec

	mov dl, 62
	mov dh, 11
	call GotoXy
	mov edx, offset SC
	call writestring
	mov dl, 62
	mov dh, 11
	call GotoXy
	mov ax, [esi+12]
	call writedec
	
	mov dl, 72
	mov dh, 11
	call GotoXy
	mov edx, offset SC
	call writestring
	mov dl, 72
	mov dh, 11
	call GotoXy
	mov ax, [esi+14]
	call writedec

;__ 3rd Row of the board __
	
	mov dl, 42
	mov dh, 16
	call GotoXy
	mov edx, offset SC
	call writestring
	mov dl, 42
	mov dh, 16
	call GotoXy
	mov ax, [esi+16]
	call writedec

	mov dl, 52
	mov dh, 16
	call GotoXy
	mov edx, offset SC
	call writestring
	mov dl, 52
	mov dh, 16
	call GotoXy
	mov ax, [esi+18]
	call writedec

	mov dl, 62
	mov dh, 16
	call GotoXy
	mov edx, offset SC
	call writestring
	mov dl, 62
	mov dh, 16
	call GotoXy
	mov ax, [esi+20]
	call writedec
	
	mov dl, 72
	mov dh, 16
	call GotoXy
	mov edx, offset SC
	call writestring
	mov dl, 72
	mov dh, 16
	call GotoXy
	mov ax, [esi+22]
	call writedec

;__ 4th Row of the board __
	
	mov dl, 42
	mov dh, 21
	call GotoXy
	mov edx, offset SC
	call writestring
	mov dl, 42
	mov dh, 21
	call GotoXy
	mov ax, [esi+24]
	call writedec

	mov dl, 52
	mov dh, 21
	call GotoXy
	mov edx, offset SC
	call writestring
	mov dl, 52
	mov dh, 21
	call GotoXy
	mov ax, [esi+26]
	call writedec

	mov dl, 62
	mov dh, 21
	call GotoXy
	mov edx, offset SC
	call writestring
	mov dl, 62
	mov dh, 21
	call GotoXy
	mov ax, [esi+28]
	call writedec
	
	mov dl, 72
	mov dh, 21
	call GotoXy
	mov edx, offset SC
	call writestring
	mov dl, 72
	mov dh, 21
	call GotoXy
	mov ax, [esi+30]
	call writedec

	popa
	ret
;=========================================
;------------ Score Procedure ------------
;=========================================
DisScore:
	pusha
	mov eax, (white*16)+ blue 
	call SetTextColor
	mov dl, 2
	mov dh, 24
	call GotoXy
	mov edx, offset sDis					;--Display Score string--
	call writestring
	mov edx, offset SC
	call writestring
	mov dl, 2
	mov dh, 25
	call GotoXy
	mov edx, offset B4						;--Display Score string--
	call writestring
	mov dl, 10
	mov dh, 24
	call GotoXy
	mov ebx, 0
	mov cx, 16
	mov ax, 0
s1:	add ax, [GameBoard+ebx]
	add bx, 2
	dec cx
	jnz s1
	sub ax, 2
	call writedec							;--Display total Scores--
	popa
	ret
;=========================================
;------------ Frame Procedure ------------
;=========================================
Frame:
	push eax
	push edx

	mov eax, (white*16)+ black 
	call SetTextColor
	mov dl, 0
	mov dh, 0
	call GotoXy
	mov edx, offset B1						;--upper Boundary of the GameTitle--
	call writestring

	mov eax, (white*16)+ red 
	call SetTextColor
	mov edx, offset B2						;--Left Boundary of the GameTitle--
	call writestring
	mov edx, offset GameTitle				;--String of the GameTitle--
	call writestring
	mov edx, offset B2						;--Right Boundary of the GameTitle--
	call writestring

	mov eax, (white*16)+ black		
	call SetTextColor
	mov edx, offset B1						;--Lower Boundary of the GameTitle-- 
	call writestring

	mov dl, 0
	mov dh, 28
	call GotoXy
	mov eax, (red*16)+ white 
	call SetTextColor
	mov edx, offset controls				;--Displaying the Controls of the Game--
	call writestring

	mov eax, (white*16)+ black
	call SetTextColor
	mov dl, 37
	mov dh, 25
	call GotoXy
	mov edx, offset B3						;--Displaying the line above the goal line--
	call writestring

	mov dl, 37
	mov dh, 26
	call GotoXy
	mov edx, offset Goal					;--Displaying the method of winning the Game--
	call writestring

	call DisScore

	mov eax, (white*16)+ black
	call SetTextColor

	pop edx
	pop eax
	ret
;=========================================
;------------- End Procedure -------------
;=========================================
terminate:		
	call Clrscr
	mov edx, offset ms 
	call writestring
main ENDP
END main