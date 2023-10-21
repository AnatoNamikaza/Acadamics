[org 0x0100]

;---------Data for Program--------------------------------

            jmp main

HexNum: dw 0730h	;0    
EmptyMsg: db 'Number is zero!',0

;---------Code Implementation of Program------------------
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

PrintBinary:	push bp
		mov bp, sp
		push es
		push di
		push ax
		push bx
		push dx
		
		mov bx, 0
		mov dx, 0
		mov ax, 0xB800	
		mov es, ax	; location of top-left corner of screen
		mov di, 2000	; location of middle of 12th row of screen
		mov ax, [bp+4]

		call clrs	; To clear the screen

		cmp ax, 0
		je empty

l1:		cmp ax, 0
		je show
	
		shr ax, 1
		jc oneB
		mov dl, 30h	; stores the 0's in the binary of the number 
		push dx		
		mov dx, 0
		 		
		add bx, 1		
		jmp l1		

oneB:		mov dl, 31h	; stores the 1's in the binary of the number
		push dx
		mov dx, 0
		 		
		add bx, 1		
		jmp l1

;---- displays the binary of the number on the screen ----

show:		mov ax, bx	 
		push bx
		mov bx, 2
		div bx		; adjusting position to place binary number
		mul bx		; in the middle position of the middle row
		sub di, ax
		pop bx

showl:		pop ax		 
		mov ah, 02h 
		mov [es:di], ax
		add di, 2		

		sub bx, 1		
		cmp bx, 0
		jne showl

		pop dx
		pop bx
		pop ax
		pop di
		pop es		
		pop bp

		ret 2

;--- displays  Message to show that the number is zero ---

empty:		push si
		mov si, EmptyMsg
		mov dh, 04h 

		mov Byte dl, [si] 

print:		mov [es:di], dx
		add di, 2		
		add si, 1
		mov Byte dl, [si] 
		cmp dl, 0
		jne print

		pop si
		pop dx
		pop bx
		pop ax
		pop di
		pop es		
		pop bp

		ret 2
		
;-----------------Main code-------------------------------

    main:   	push word [HexNum]
		call PrintBinary
	
    end:	mov ax, 0x4c00
		int 0x21


