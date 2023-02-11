[org 0x0100]

;---------Data for Program--------------------------------

            jmp main
char1: db '>';	'@'
char2: db '<';	'$'
    
;---------Code Implementation of Program------------------

;------------------------------------------------------

slow:		mov bx, 8fffh	
l2:		sub bx, 1	
		cmp bx, 0	 
		jne l2
		ret

;------------------------------------------------------

clrs:		push ax
		push cx
		push di
		mov di, 0
		mov ax, 0720h
		mov cx, 4000

lp1:		mov [es:di],ax
		add di, 2
		loop lp1

		pop di
		pop cx
		pop ax

		ret

;------------------------------------------------------

Print:		push bp
		mov bp, sp
		push es
		push si
		push di
		mov si, 0

		mov ax, 0xB800	
		mov es, ax	; location of top-left corner of screen
		mov di, 1920	; location of starting of 12th row of screen
		mov si, 2078	; location of end point of 12th row of screen
		mov cx, 41	; no of columns of screen that must be covered

		call clrs	; To clear the screen

l1:		mov al, [bp+6]	; loading char1 in al
		mov ah, 04h	; loading attributes of the charactor
 		
		mov [es:di], ax	; displaying char1 on the screen

		mov al, [bp+4]	; loading char1 in al
		mov ah, 02h	; loading attributes of the charactor
 		
		mov [es:si], ax	; displaying char2 on the screen
		
		sub cx, 1

		call slow	; subroutine to slow down the display time
				; to make it visible
		cmp cx, 0
		je exit

		mov ah, 00h	; black background charactor
		mov al, 20h	; ascii value of space in hex

		mov [es:si], ax	; clearing right-side
		mov [es:di], ax	; clearing left-side

		add di, 2	; moving char1 towards rightside of the row 
		sub si, 2	; moving char2 towards leftside of the row

		
		jmp l1
		
exit:		pop di
		pop si
		pop es		
		pop bp

		ret 4
		
;-----------------Main code-------------------------------

    main:   	push ax
		mov al, [char1]
		push ax
		mov al, [char2]
		push ax
		call Print
		pop ax

    end:	mov ax, 0x4c00
		int 0x21


