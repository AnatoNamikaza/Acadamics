[org 0x0100]

		jmp work
		num1:       dq 1583325879; in hex:5E5FA2B7
		num2:       dd 2235875568; in hex:8544C0F0
		result:     dq 0h

		work:   mov cx, 32
		mov eax, [num1]         ; moves 1st 32-bit number in eax register
		mov ebx, [num2]         ; moves 2st 32-bit number in ebx register

	chkB:   shr ebx, 1              ; shifts 2st 32-bit number in ebx register to the right by one bit. 
		jnc  skip

		mov eax, [num1]
		add [result], eax
		mov eax, [num1+4]
		adc [result+4], eax

	skip:   shl word [num1], 1
		rcl word [num1+2], 1
		rcl word [num1+4], 1
		rcl word [num1+6], 1

		sub cx, 0
		cmp cx, 0
		jne chkB

	end:	mov ax, 0x4c00
		int 0x21
