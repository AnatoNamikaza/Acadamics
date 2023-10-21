[org 0x100]
jmp start

;==========clear screen==========
clrscr:		pusha
			mov ax,0x0003	; interrupt to clear screen
			int 10h	
			popa
			ret
;==========slowing speed=========
Delay:		pusha
			mov cx,0xafff
D1:			loop D1			
			popa
			ret			
;==========slowing motion=========
MDelay:		pusha
			mov cx,0xffff
MD1:		loop MD1			
			popa
			ret						
;===========char Mario===========
mario:		push bp 
			mov bp, sp
			pusha
			push es
			push 0xb800
			pop es
			mov di, [bp+4]
			mov bx, 0
			mov ah, 0x67
			mov al, '.'
			;head
			mov [es:di+bx], ax
			add bx, 2
			mov [es:di+bx], ax
			;arms and body
			add di, 156
			mov dl, 2			;layers
b1:			mov bx, 0
			mov word [es:di+bx], 0x6720
			add bx, 2
			mov cl, 4
b2:			mov word [es:di+bx], 0x7020
			add bx, 2
			dec cl
			jnz b2
			mov word [es:di+bx], 0x6720
			add di, 160
			dec dl
			jnz b1
			mov bx, 2
			mov word [es:di+bx], 0x6720
			mov bx, 8
			mov word [es:di+bx], 0x6720
Mexit:		pop es
			popa
			pop bp
			ret
;==========clear Mario===========
Cmario:		push bp 
			mov bp, sp
			pusha
			push es
			push 0xb800
			pop es
			mov di, [bp+4]
			mov bx, 0
			;head
			mov word [es:di+bx], 0x0020
			add bx, 2
			mov word [es:di+bx], 0x0020
			;arms and body
			add di, 156
			mov dl, 2			;layers
cb1:		mov bx, 0
			mov word [es:di+bx], 0x0020
			add bx, 2
			mov cl, 4
cb2:		mov word [es:di+bx], 0x0020
			add bx, 2
			dec cl
			jnz cb2
			mov word [es:di+bx], 0x0020
			add di, 160
			dec dl
			jnz cb1

			mov bx, 2
			mov word [es:di+bx], 0x0020
			mov bx, 8
			mov word [es:di+bx], 0x0020

Cexit:		pop es
			popa
			pop bp
			ret			
;========hurdles and flag========
graphics:	push bp
			mov bp, sp
			pusha
			push es
			push 0xb800
			pop es

			;hurdle#1
			mov di, [bp+4]
			mov ax, 0x4020
			mov bx, 0
			mov cl, 4
uh1:		mov [es:di+bx], ax
			add bx, 2
			dec cl
			jnz uh1
			add di, 162
			mov ch, 0x04
h11:		mov cl, 2
			mov bx, 0
h12:		mov [es:di+bx], ax
			add bx, 2
			dec cl
			jnz h12
			add di, 160
			dec ch
			jnz h11

			;hurdle#2
			mov di, [bp+4]
			add di, 360
			mov bx, 0
			mov cl, 4
uh2:		mov [es:di+bx], ax
			add bx, 2
			dec cl
			jnz uh2
			add di, 162
			mov ch, 0x01
h21:		mov cl, 2
			mov bx, 0
h22:		mov [es:di+bx], ax
			add bx, 2
			dec cl
			jnz h22
			add di, 160
			dec ch
			jnz h21

			;hurdle#3
			mov di, [bp+4]
			sub di, 240
			mov ax, 0x4020
			mov bx, 0
			mov cl, 4
uh3:		mov [es:di+bx], ax
			add bx, 2
			dec cl
			jnz uh3
			add di, 162
			mov ch, 0x06
h31:		mov cl, 2
			mov bx, 0
h32:		mov [es:di+bx], ax
			add bx, 2
			dec cl
			jnz h32
			add di, 160
			dec ch
			jnz h31

			;flag
Flag:		mov di, [bp+6]
			mov ch, 0x05		;length of flag
F1:			mov cl, 15			;width of flag
			mov bx, 0
			mov ax, 0x2020
F2:			mov [es:di+bx], ax
			add bx, 2
			dec cl
			jnz F2
			dec ch
			jz pole
			add di, 160
			jmp F1	

			;pole
pole:		mov di, [bp+6]
			add di, 32
			mov bx, 0
			mov cl, 23	
			mov ax, 0x7020
p1:			mov [es:di+bx], ax
			add bx, 160
			dec cl
			jnz p1

			;moon and stars
Moon:		mov di, [bp+6]
			mov word [es:di+10], 0x202A
			mov word [es:di+16], 0x202A
			mov word [es:di+180], 0x202A
			mov word [es:di+332], 0x202A
			mov word [es:di+342], 0x202A
			mov word [es:di+500], 0x202A
			mov word [es:di+656], 0x202A
			mov word [es:di+650], 0x202A
			mov word [es:di+486], 0x202A

			pop es
			popa
			pop bp
			ret 4
;===========char Mario===========
motion:		push bp 
			mov bp, sp
			pusha
			push es
			push 0xb800
			pop es
			push word [bp+4]
			
Draw:		call mario
			call MDelay
			call MDelay
			pop bx
			push bx
			mov di, bx

Input:		in al, 0x60
			cmp al, 1
			je MvE
			cmp al, 30
			je Left
			cmp al, 32
			je Right
			cmp al, 57
			je Jump
			jmp Gravity

Right:		mov bx, 0
			mov ch, 4
R1:			mov dx, word [es:di+10+bx]
			cmp dx, 0x4020
			je Input
			cmp dx, 0x7020
			je MvE
			add bx, 160
			dec ch
			jnz R1
			call Cmario
			pop bx
			add bx, 2
			push bx
			jmp Gravity

Left:		mov bx, 0
			mov ch, 4
			mov dx, word [es:di-12]
			cmp dx, 0x7020
			je Input
L1:			mov dx, word [es:di-8+bx]
			cmp dx, 0x4020
			je Input
			cmp dx, 0x7020
			je MvE
			add bx, 160
			dec ch
			jnz L1
			call Cmario
			pop bx
			sub bx, 2
			push bx
			jmp Gravity
			
MvE:		jmp Moexit

Jump:		call Cmario
			mov cl, 10
j1:			pop bx
			sub bx, 160
			push bx
			cmp bx, 800
			jb Gravity
			in al, 0x60
			cmp al, 30
			jne nU
			pop bx
			sub bx, 2
			push bx
nU:			cmp al, 32
			jne cU
			pop bx
			add bx, 2
			push bx			 
cU:			call mario
			call MDelay
			call Cmario
			dec cl
			jnz j1
			
Gravity:	mov bx, 0
			mov ch, 6
G1:			mov dx, word [es:di+636+bx]
			cmp dx, 0x4020
			je Draw
			add bx, 2
			dec ch
			jnz G1
			pop bx
			push bx
			cmp bx, 3360
			ja Draw
			call Cmario
			pop bx
			add bx, 160
			push bx
			call mario
			call MDelay
			call Cmario
			jmp Draw

Moexit:		pop bx
			pop es
			popa
			pop bp
			ret 2
;===========Main codes===========
start:		call clrscr			
			push 440		;location of flag
			push 3400		;location of hurdles
			call graphics		
			push 3370
			call motion
exit:		mov ax, 0x4c00
			int 0x21
;================================
