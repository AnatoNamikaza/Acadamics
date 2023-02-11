[org 0x0100]

		jmp start

tickcount:	dw	0
VastSecds:	db 	0
msg:	db 'Graph-Plane#'
;-----------------------------------------------------
start: 		call clrs
			xor ax, ax
			push es
			mov es, ax 						; point es to IVT base

			cli 							; disable interrupts
			push word [es:0x34*4]
			push word [es:0x34*4+2]
			mov word [es:0x34*4], DisTimer	; store offset at n*4
			mov [es:0x34*4+2], cs 			; store segment at n*4+2
			sti 							; enable interrupts

			mov ah, 0
			int 0x16
			cmp al,	'a'
			je interrupt
			cmp al,	'b'
			je interrupt
			cmp al,	'c'
			je interrupt
			cmp al,	'd'
			je interrupt
			cmp al,	27
			je	restore

interrupt:	int 0x34

restore:	pop word [es:0x34*4+2]
			pop word [es:0x34*4]
			pop es

end:		mov ax, 0x4c00
			int 0x21
;-----------------------------------------------------
DisTimer:	pusha
			push es

			mov ax, 0
			jmp cmplp
			
checker:	cmp al,	30
			je reset
			cmp al,	48
			je reset
			cmp al,	46
			je reset
			cmp al,	32
			je reset
			cmp al,	1
			je LevTimer
			jmp resume

reset:		mov bl, al
			mov al, 0x20
			call clrs
			push 0
			pop word [tickcount]

cmplp:		in al, 0x60
			cmp bl, al
			jne checker
resume:		cmp bl,	30
			je DisULP
			cmp bl,	48
			je DisURP
			cmp bl,	46
			je DisLLP
			cmp bl,	32
			je DisLRP
			jmp cmplp

LevTimer:	pop es
			popa
			iret
;-----------------------------------------------------
DisULP:		push 504
			mov ch, 1
			call DisDecNo
			call incTime
			jmp cmplp			
;-----------------------------------------------------
DisURP:		push 598
			mov ch, 2
			call DisDecNo
			call incTime
			jmp cmplp
;-----------------------------------------------------
DisLLP:		push 3544
			mov ch, 3
			call DisDecNo
			call incTime
			jmp cmplp
;-----------------------------------------------------
DisLRP:		push 3638
			mov ch, 4
			call DisDecNo
			call incTime
			jmp cmplp
;-----------------------------------------------------
incTime:	pusha
			push es
			push 0xB800
			pop es
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
			sub di, 166
			mov si, msg
			mov ah, 0x0c
			mov byte al, [si]
			
D1:			cmp al, '#' 
			je N1
			mov byte al, [si]
			mov [es:di], ax
			add di, 2
			add si, 1
 			jmp D1

N1:			mov ah, 0x07
			add ch, 0x30
			mov al, ch
			mov [es:di], ax

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
			ret 2
;-----------------------------------------------------
clrs:		pusha
			mov ah,00	
			mov al,03h						; interrupt to clear screen
			int 10h	

			popa	
			ret
;-----------------------------------------------------			
Slow:		pusha
 			mov cx, 0x8fff
lSlow:		sub cx, 1
 			cmp cx, 0
 			jne lSlow
 			popa
 			ret
;-----------------------------------------------------	