INCLUDE Irvine32.inc

.data
	ms1 byte "Enter Matrix#1: ", 0
	ms2 byte "Enter Matrix#2: ", 0
	ds1 byte "Matrix#1: ", 0
	ds2 byte "Matrix#2: ", 0
	ds3 byte "Result Matrix: ", 0
	matrix1 dw 6 dup(0)
	matrix2 dw 6 dup(0)
	matrix3 dw 4 dup(0)

.code

main PROC
	call InputMatrix
	call MulMatrix
	call DisplayMatrix
	jmp terminate

InputMatrix:
	pusha
	mov edx, offset ms1
	call writestring 
	call crlf
	mov esi, offset matrix1
	mov ebx, 0
	mov eax, 0
l1:	call readint
	mov [esi+ebx], ax
	add bx, 2
	cmp bx, 12
	jb l1
	call crlf
	mov edx, offset ms2
	call writestring 
	call crlf
	mov esi, offset matrix2
	mov ebx, 0
l2:	call readint
	mov [esi+ebx], ax
	add bx, 2
	cmp bx, 12
	jb l2
	call crlf
	popa
	ret

MulMatrix:
	pusha
	mov esi, offset matrix1
	mov edi, offset matrix2
	mov eax, 0
	mov ebx, 0
	mov ecx, 0
	mov edx, 0

	mov ax, [esi]
	mov cx, [edi]
	mul cx
	add bx, ax

	mov ax, [esi+2]
	mov cx, [edi+4]
	mul cx
	add bx, ax
	
	mov ax, [esi+4]
	mov cx, [edi+8]
	mul cx
	add bx, ax
	push ebx				;Element#1 of the Matrix3
	mov bx, 0

	mov ax, [esi]
	mov cx, [edi+2]
	mul cx
	add bx, ax

	mov ax, [esi+2]
	mov cx, [edi+6]
	mul cx
	add bx, ax
	
	mov ax, [esi+4]
	mov cx, [edi+10]
	mul cx
	add bx, ax
	push ebx				;Element#2 of the Matrix3
	mov bx, 0

	mov ax, [esi+6]
	mov cx, [edi]
	mul cx
	add bx, ax

	mov ax, [esi+8]
	mov cx, [edi+4]
	mul cx
	add bx, ax
	
	mov ax, [esi+10]
	mov cx, [edi+8]
	mul cx
	add bx, ax
	push ebx				;Element#3 of the Matrix3
	mov bx, 0

	mov ax, [esi+6]
	mov cx, [edi+2]
	mul cx
	add bx, ax

	mov ax, [esi+8]
	mov cx, [edi+6]
	mul cx
	add bx, ax
	
	mov ax, [esi+10]
	mov cx, [edi+10]
	mul cx
	add bx, ax
	
	mov esi, offset matrix3
	mov [esi+6], bx
	pop ebx
	mov [esi+4], bx
	pop ebx
	mov [esi+2], bx
	pop ebx
	mov [esi], bx

	popa
	ret

DisplayMatrix:
	pusha
	mov edx, offset ds1
	call writestring 
	call crlf
;--------Matrix#1--------
	mov esi, offset matrix1
	mov ebx, 0
d1:	mov eax, 0
	mov al, ' '
	call writechar
	call writechar
	call writechar
	call writechar
	mov ax, [esi+ebx]
	call writeint
	add bx, 2
	cmp bx, 6
	jb d1
	call crlf
d2:	mov eax, 0
	mov al, ' '
	call writechar
	call writechar
	call writechar
	call writechar
	mov ax, [esi+ebx]
	call writeint
	add bx, 2
	cmp bx, 12
	jb d2
	call crlf
	call crlf

	mov edx, offset ds2
	call writestring 
	call crlf
;--------Matrix#2--------
	mov esi, offset matrix2
	mov ebx, 0
d3:	mov eax, 0
	mov al, ' '
	call writechar
	call writechar
	call writechar
	call writechar
	mov ax, [esi+ebx]
	call writeint
	add bx, 2
	cmp bx, 4
	jb d3
	call crlf
d4:	mov eax, 0
	mov al, ' '
	call writechar
	call writechar
	call writechar
	call writechar
	mov ax, [esi+ebx]
	call writeint
	add bx, 2
	cmp bx, 8
	jb d4
	call crlf
d5:	mov eax, 0
	mov al, ' '
	call writechar
	call writechar
	call writechar
	call writechar
	mov ax, [esi+ebx]
	call writeint
	add bx, 2
	cmp bx, 12
	jb d5
	call crlf
	call crlf
;--------Matrix#3--------
	mov edx, offset ds3
	call writestring 
	call crlf
	mov esi, offset matrix3
	mov ebx, 0
d6:	mov eax, 0
	mov al, ' '
	call writechar
	call writechar
	call writechar
	call writechar
	mov ax, [esi+ebx]
	call writeint
	add bx, 2
	cmp bx, 4
	jb d6
	call crlf
d7:	mov eax, 0
	mov al, ' '
	call writechar
	call writechar
	call writechar
	call writechar
	mov ax, [esi+ebx]
	call writeint
	add bx, 2
	cmp bx, 8
	jb d7
	popa
	ret

terminate:	
	call crlf
	call crlf
	mov ax, 0
main ENDP
END main