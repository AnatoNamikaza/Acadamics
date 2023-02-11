[org 0x0100]
 		jmp start

Built:	db 	0
VastSecds:	db 	0
tickcount:	dw	0
checkPoint:	dw 	0
msg:	db 'Timer:'
;-----------------------------------------------------
start: 		mov ah,00	
			mov al,03h
			int 10h	

			xor ax, ax
			mov es, ax
			cli 
			push word [es:0x34*4]
			push word [es:0x34*4+2]
			mov word [es:0x34*4], timer
			mov [es:0x34*4+2], cs 
			sti 

ChkS:		mov ah, 0
			int 0x16
			cmp al, 27
			je restore
			cmp al, 'S'
			je interrupt
			jmp ChkS

interrupt:	int 0x34
			
restore:	pop word [es:0x34*4+2]
			pop word [es:0x34*4]
			pop es

exit:		mov ax, 0x4c00
			int 0x21
;-----------------------------------------------------
timer: 		push ax
			mov cx, 0
			mov bx, 0
			push 1998	; corridnates for Char
			push 1990	; corridnates for timer
display:	call DisDecNo
			call incTime
 			mov byte bl, [Built]
 			cmp bl, 1
 			je exittimer
 			
 			
cmplp:		in al, 0x60
			cmp al, 22
			je GoUp
			cmp al, 32
			je GoDown
			cmp al, 38
			je GoLeft
			cmp al, 19
			je GoRight
			cmp al, 1
			je exittimer
			jmp display	

GoUp:		pop bx
			pop dx
			sub dx, 160
			push dx
			push bx
 			call DisChar
ReprU:		in al, 0x60
			cmp al, 22
			je ReprU
			jmp display

GoDown:		pop bx
			pop dx
			add dx, 160
			push dx
			push bx
 			call DisChar
ReprD:		in al, 0x60
			cmp al, 32
			je ReprD
			jmp display

GoLeft:		pop bx
			pop dx
			sub dx, 2
			push dx
			push bx
 			call DisChar
ReprL:		in al, 0x60
			cmp al, 38
			je ReprL
			jmp display

GoRight:	pop bx
			pop dx
			add dx, 2
			push dx
			push bx
 			call DisChar
ReprR:		in al, 0x60
			cmp al, 19
			je ReprR 			
			jmp display

exittimer:	pop ax
			pop ax
			pop ax
 			iret ; return from interrupt
;-----------------------------------------------------
 DisChar:	push bp
			mov bp, sp
			pusha
			push es
	
			mov bx, 0xB800
			mov es, bx
			mov di, [bp+6]

			mov word ax, [es:di]
			cmp al, '.'
			je Check

			mov ah, 0x09
			mov al, '.'
			mov word [es:di], ax
			mov word [checkPoint], di
			jmp exitMove

Check:		mov word bx, [checkPoint]
			cmp bx, di
			je exitMove

terminate:	mov bl, 1
			mov byte [Built], bl

exitMove:	pop es
			popa
			pop bp
			ret	
;-----------------------------------------------------
incTime:	pusha
			push es
			xor ax, ax    
		    mov al, 0    
		    out 0x70, al        			; Load seconds in "al" register
		    jmp s1    
s1:			in al, 0x71
			
			mov byte ah, [VastSecds]
			cmp ah, al
			je EscInc
			mov byte [VastSecds], al
			mov word ax, [tickcount]
			add ax, 1
			mov word [tickcount], ax
			jmp EscInc

EscInc:		pop es
			popa
			ret
;-----------------------------------------------------
DisDecNo:	push bp
			mov bp, sp
			pusha
			push es

			push 0xB800
			pop es

			mov di, [bp+4]
			sub di, 160
			mov si, msg
			mov ah, 0x0c
			
D1:			mov byte al, [si]
			mov [es:di], ax
			add di, 2
			add si, 1
 			cmp al, ':' 
			jne D1
			
			mov dx, 0
			mov cx, 0
			mov word ax, [tickcount]
			mov di, [bp+4]
			mov bx, 3600
			div bx
			mov cx, dx
			mov dx, 0
			mov bx, 10
			div bx

			add al, 0x30					; Display hours of timer
			mov ah, 0x0A
			mov	word [es:di], ax
			mov ax, dx
			add al, 0x30
			mov ah, 0x0A
			add di, 2
			mov	word [es:di], ax
			mov al, ':'
			add di, 2
			mov	word [es:di], ax
			add di, 2
			
			mov dx, 0
			mov ax, cx

			mov bx, 60
			div bx
			mov cx, dx
			mov dx, 0
			mov bx, 10
			div bx

			add al, 0x30					; Display minutes of timer
			mov ah, 0x0A
			mov	word [es:di], ax
			mov ax, dx
			add al, 0x30
			mov ah, 0x0A
			add di, 2
			mov	word [es:di], ax
			mov al, ':'
			add di, 2
			mov	word [es:di], ax
			add di, 2
			
			mov dx, 0
			mov ax, cx

			mov bx, 10
			div bx

			add al, 0x30					; Display seconds of timer
			mov ah, 0x0A
			mov	word [es:di], ax
			mov al, dl
			add al, 0x30
			add di, 2
			mov	word [es:di], ax

exitDec:	pop es
			popa
			pop bp
			ret 
;-----------------------------------------------------
clrs:		pusha
			mov ah,00	
			mov al,03h						; interrupt to clear screen
			int 10h	

			popa	
			ret
;-----------------------------------------------------	