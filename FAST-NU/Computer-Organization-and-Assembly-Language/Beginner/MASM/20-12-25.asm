INCLUDE Irvine32.inc
.data

	msg byte "Enter Number#1: ", 0
	msg2 byte "Enter Number#2: ", 0
	msg3 byte "Sum Output:", 0
	Result dd 0,0

.code

main PROC
	mov edx, offset msg
	call writestring
	call crlf
	call readhex
	call crlf
	mov ebx, eax
	mov edx, offset msg2
	call writestring
	call crlf
	call readhex
	call crlf
	mov esi, offset Result
	add [esi], eax	
	add [esi], ebx	
	jc CA
	jmp Ex

CA:	mov eax, 1
	add [esi+4], eax	

Ex:	mov edx, offset msg3
	call crlf
	call writestring
	call crlf
	mov eax, [esi+4]	
	call writehex
	mov eax, [esi]	
	call writehex
	call crlf

main ENDP
END main