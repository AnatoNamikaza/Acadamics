[org 0x0100]
jmp start;;;;;;;;;;;;;;;;;;;;;;To print names

n1: db 'Farwa Batool 19L-1168'
n2: db 'Hamna Arifeen 19L-1161'
n3: db 'Shehmeer Abid 19L-1115'
n4: db 'Haidar Ali 19L-1XXX'
n5: db 'Chalo NIkalo!'	
n6: db 'Press Enter to Start'

P_names:
		mov ah,00
		mov al,03
		int 10h

		mov ah, 0x13
		mov al, 1
		mov bh, 0
		mov bl, 7
		mov dx, 0x0000
		mov cx, 22
		push cs
		pop es
		mov bp, n3
		int 0x10
		
		mov ah, 0x13
		mov al, 1
		mov bh, 0
		mov bl, 7
		mov dx, 0x0100
		mov cx, 21
		push cs
		pop es
		mov bp, n1
		int 0x10
		
		mov ah, 0x13
		mov al, 1
		mov bh, 0
		mov bl, 7
		mov dx, 0x0200
		mov cx, 22
		push cs
		pop es
		mov bp, n2
		int 0x10
		
		mov ah, 0x13
		mov al, 1
		mov bh, 0
		mov bl, 7
		mov dx, 0x0300
		mov cx, 19
		push cs
		pop es
		mov bp, n4
		int 0x10
		
		mov ah, 0x13
		mov al, 1
		mov bh, 0
		mov bl, 7
		mov dx, 0x0B1A
		mov cx, 20
		push cs
		pop es
		mov bp, n6
		int 0x10
		
		mov ah, 0x13
		mov al, 1
		mov bh, 0
		mov bl, 7
		mov dx, 0x1643
		mov cx, 13
		push cs
		pop es
		mov bp, n5
		int 0x10
		
		ret
	;;;;;;;;;;;;
cls:	
		push es
		push ax
		push cx
		push di
		
		mov ax,0xb800
		mov es,ax
		mov di,0
		mov ax,0x0720
		mov cx,4000
		
		cld
		rep stosw
		
		pop di
		pop cx
		pop ax
		pop es
		ret
graphics:

		mov ah,0
		mov al,13h
		int 10h
background:
		mov ah,0Ch
		mov al,0001b
		mov cx,0
		mov dx,0
		int 10h
		loop1:
		inc cx
		cmp cx,320
		int 10h
		jne loop1
		inc dx
		mov cx,0
		cmp dx,200
		int 10h
		jne loop1
gameground:
		mov ah,0Ch
		mov al,0100b
		mov cx,60	
		mov dx,48
		int 10h
	loop2:
		inc cx
		cmp cx,250
		int 10h
		jne loop2
		inc dx
		mov cx,60
		cmp dx,144
		int 10h
		jne loop2
	

Line1:				;upper border line
	mov ah,0Ch
	mov al,1101b
	mov cx,60
	mov dx,48
	int 10h
l1:
	inc cx
	cmp cx,250
	int 10h
	jne l1
Line2:				;left borderline
	mov ah,0Ch
	mov al,1101b
	mov cx,60
	mov dx,48
	int 10h
l2:
	inc dx
	cmp dx,144
	int 10h
	jne l2
	
Line3:				;lower Borderline
	mov ah,0Ch
	mov al,1101b
	mov cx,60
	mov dx,144
	int 10h
l3:
	inc cx
	cmp cx,250
	int 10h
	jne l3
	
Line4:				;right borderline
	mov ah,0Ch
	mov al,1101b
	mov cx,250
	mov dx,48
	int 10h
l4:
	inc dx
	cmp dx,144
	int 10h
	jne l4
	
line5:	
	mov ah,0Ch
	mov al,1101b
	mov cx,120
	mov dx,48
	int 10h
l5:
	inc dx
	cmp dx,144
	int 10h
	jne l5
	
line6:	
	mov ah,0Ch
	mov al,1101b
	mov cx,190
	mov dx,48
	int 10h
l6:
	inc dx
	cmp dx,144
	int 10h
	jne l6
	
Line7:		
	mov ah,0Ch
	mov al,1101b
	mov cx,60
	mov dx,80
	int 10h
l7:
	inc cx
	cmp cx,250
	int 10h
	jne l7
Line8:		
	mov ah,0Ch
	mov al,1101b
	mov cx,60
	mov dx,115
	int 10h
l8:
	inc cx
	cmp cx,250
	int 10h
	jne l8
		
	ret
cross:	
	mov ah,0Ch
	mov al,1111b
	mov cx,5
	mov dx,5
	int 10h
	

l:
	inc dx
	inc cx
	cmp dx,12
	int 10h
	jne l

	mov ah,0Ch
	mov al,1111b
	mov cx,12
	mov dx,5
	int 10h
	
	l_1:
	inc cx
	dec dx
	cmp dx,12
	int 10h
	jne l_1
	call slow
	
	ret

tick:
	mov ah,0Ch
	mov al,1111b
	mov cx,20
	mov dx,12
	int 10h
l_2:
	inc dx
	dec cx
	cmp dx ,17
	int 10h
	jne l_2
	mov ah,0Ch
	mov al,1111b
	int 10h
l_3:
	dec cx
	dec dx
	cmp dx,15
	int 10h
	jne l_3	

	ret		
mouse_settings:
	mov ax,1
	int 33h
	mov ax,7
	mov cx,0
	mov dx,620
	int 33h
	mov ax,8
	mov cx,0
	mov dx,185
	int 33h
	ret 


slow:
	push ax
	push bx
	mov ax,0x00FF
	
sl_1:
	mov bx,0xFFFF

sl_2:
	dec bx
	jnz sl_2
	dec ax
	jnz sl_1
	pop bx
	pop ax
	ret

start:
		call cls
		call P_names
		

Enter_Key_Press:
		mov ah,00h
		int 16h
		cmp ah,28	
		jne Enter_Key_Press
		
		call graphics
		
		call mouse_settings
mouse:
		mov ax,3
		int 33h
		cmp bx,1
		jne mouse
		call cross


		

mov ax,0x4c00
int 21h