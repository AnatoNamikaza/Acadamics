[org 0x0100]

		jmp start
		num1: dw 20		; Number whose square we have to find

	start:  mov ax, [num1]		; moves value of num1 to register "ax"
        	mov cx, [num1]		; moves value of num1 to register "cx"

		cmp cx, 0		; to check if number is zero
		je end
            
	l1:     sub cx, 1       	; decreases value of register "cx" by 1.
        	cmp cx, 0
        	je end
		add ax, [num1]		; adds value of num1 to value of register "ax" 
					; and stores in register "ax"
        	
		jmp l1			; Goes to start of loop

	;The value in ax will be 190 before termination

	end:    mov ax, 0x4c00		; termination of program
		int 0x21
            
		
