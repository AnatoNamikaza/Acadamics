INCLUDE Irvine32.inc

.data
	msg1 byte "Enter key of encryption: ", 0
	msg2 byte "Enter text to encrypt: ", 0
	msg3 byte "Encryption key: ", 0
	msg4 byte "Original String: ", 0
	msg5 byte "Encryted String: ", 0
	msg6 db 120 dup('='),0
	EnKey db 32 dup(0)
	OrString db 256 dup(0)
	EnString db 256 dup(0)

.code

main PROC
	mov edx, offset msg1
	call writestring 
	mov edx, offset EnKey
	mov ecx, 30
	call readstring
	call crlf

	mov edx, offset msg2
	call writestring 
	mov edx, offset OrString
	mov ecx, 256
	call readstring
	call crlf

	mov edx, offset msg6
	call writestring
	call crlf
	call crlf

	call Encrypt

	mov edx, offset msg3
	call writestring
	mov edx, offset EnKey
	call writestring
	call crlf
	call crlf

	mov edx, offset msg4
	call writestring
	call crlf
	call crlf

	mov edx, offset OrString
	call writestring
	call crlf
	call crlf

	mov edx, offset msg5
	call writestring
	call crlf
	call crlf
	mov edx, offset EnString
	call writestring

	jmp terminate

Encrypt:
	pusha
	mov edx, offset OrString
	call StrLength
	mov ecx, eax
	mov edx, offset EnKey
	call StrLength
	mov ch, al
	mov edi, offset EnString
	mov esi, offset OrString
	mov ebx, offset EnKey
	mov edx, 0

l1: mov ah, [esi]
	mov al, [ebx]
	xor al, ah
	mov [edi], al
	inc esi
	inc edi
	inc ebx
	inc dl
	cmp	ch, dl
	jne skip
	mov ebx, offset EnKey
	mov edx, 0
skip:dec cl
	jnz l1

	popa
	ret

terminate:
	mov ax, 0
main ENDP
END main