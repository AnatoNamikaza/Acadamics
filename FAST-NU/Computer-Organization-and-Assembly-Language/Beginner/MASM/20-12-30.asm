INCLUDE Irvine32.inc

.data
	msg byte "Enter String: ", 0
	msg2 byte "Original String: ", 0
	msg3 byte "Encryted String: ", 0
	matrix db	'B','I','L','A','H',
				'M','E','D','C','F',
				'G','J','K','N','O',
				'P','Q','R','S','T',
				'U','V','W','X','Y'
	found db 0,0,0
	Tindex1 dw 0
	Tindex2 dw 0
	Sindex1 dw 0
	Sindex2 dw 0
	CSindex dw 0
	cRow1 dw 0
	cRow2 dw 0
	cCol1 dw 0
	cCol2 dw 0
	colDif dw 0
;	teststring1 db 'I','H'	; Correct Answer: 'L','B'
;	teststring2 db 'E','V'	; Correct Answer: 'J','I'
;	teststring3 db 'J','X'	; Correct Answer: 'N','V'
	string db 50 dup('$')

;	Test input: BAOD
;	Correct Answer: IFRF
.code

main PROC
	mov edx, offset msg
	call writestring 
	call crlf
	mov bx, 0
	mov eax, 0
	mov edx, offset string
	mov ecx, 5
	call readstring
	call crlf
	call crlf
	mov edx, offset msg2
	call writestring
	mov edx, offset string
	call writestring

	;Encryption method can be rearranged to meet you needs

	mov ebx, 0		; index1 of string for the pair
	call Encrypt1
	mov ebx, 1		; index2 of string for the pair
	call Encrypt2
	mov ebx, 2		; index3 of string for the pair
	call Encrypt3

	jmp terminate

Encrypt1:
	pusha
	mov edx, 0
	mov dh, [string+ebx]
	mov dl, [string+ebx+1]
	mov [Sindex1], bx
	inc bx
	mov [Sindex2], bx
	dec bx
	mov bx, 0
	mov cx, 0

l1:	mov ah, [matrix+ebx]
	cmp ah, dh
	je s1
	inc bx
	jmp l1

s1: mov [Tindex1], bx
	mov ax, bx
	cmp ax, 5
	jb lr
	mov bl, 5
	div bl
	mov cl, al

lr: mov bx, 0
	mov [cRow1], cx
	mov cx, 0

l2:	mov ah, [matrix+ebx]
	cmp ah, dl
	je s2
	add bx, 1
	jmp l2

s2: mov [Tindex2], bx
	mov ax, bx
	cmp ax, 5
	jb ck1
	mov bl, 5
	div bl
	mov cl, al

ck1:mov ax, [cRow1]
	cmp cx, ax
	je PrE1
	popa
	ret
PrE1:mov ax, [cRow1]
	mov dx, 5
	mul dx
	add ax, 5
	mov dx, ax
	mov ax, [Tindex1]
	inc ax
	cmp ax, dx
	jb RP1
	sub dx, 5 
	mov bx, dx
	jmp RG1
RP1:mov bx, ax
RG1:mov ch, [matrix+ebx]
	mov bx, [Sindex1]
	mov [string+ebx], ch
;-------------------------------
	mov ax, [cRow1]
	mov dx, 5
	mul dx
	add ax, 5
	mov dx, ax
	mov ax, [Tindex2]
	inc ax
	cmp ax, dx
	jb RP2
	sub dx, 5 
	mov bx, dx
	jmp RG2
RP2:mov bx, ax
RG2:mov ch, [matrix+ebx]
	mov bx, [Sindex2]
	mov [string+ebx], ch
	mov [found], 1
	popa
	ret

Encrypt2:
	pusha
	mov edx, 0
	mov dh, [string+ebx]
	mov dl, [string+ebx+1]
	mov [Sindex1], bx
	inc bx
	mov [Sindex2], bx
	dec bx
	mov bx, 0
	mov cx, 0

cl1:	mov ah, [matrix+ebx]
	cmp ah, dh
	je cs1
	inc bx
	jmp cl1

cs1: mov [Tindex1], bx
	mov ax, bx
	cmp ax, 0
	je clr
	mov bl, 5
	div bl
	mov cl, ah

clr: mov bx, 0
	mov [cCol1], cx
	mov cx, 0

cl2:	mov ah, [matrix+ebx]
	cmp ah, dl
	je cs2
	add bx, 1
	jmp cl2

cs2: mov [Tindex2], bx
	mov ax, bx
	cmp ax, 0
	je ck2
	mov bl, 5
	div bl
	mov cl, ah

ck2:mov ax, [cCol1]
	cmp cx, ax
	je PrE2
	popa
	ret
PrE2:mov ax, [Tindex1]
	add ax, 5
	cmp ax, 25
	jb cRP1
	sub ax, 25 
	mov bx, ax
	jmp cRG1
cRP1:mov bx, ax
cRG1:mov ch, [matrix+ebx]
	mov bx, [Sindex1]
	mov [string+ebx], ch
;-------------------------------
	mov ax, [Tindex2]
	add ax, 5
	cmp ax, 25
	jb cRP2
	sub ax, 25 
	mov bx, ax
	jmp cRG2
cRP2:mov bx, ax
cRG2:mov ch, [matrix+ebx]
	mov bx, [Sindex2]
	mov [string+ebx], ch
	popa
	ret

Encrypt3:
	pusha
	mov eax, 0
	mov ecx, 0
	mov edx, 0
	mov dh, [string+ebx]
	mov dl, [string+ebx+1]
	mov [Sindex1], bx
	inc bx
	mov [Sindex2], bx
	dec bx
	mov bx, 0
	mov cx, 0

rl1:	mov ah, [matrix+ebx]
	cmp ah, dh
	je rs1
	inc bx
	jmp rl1

rs1: mov [Tindex1], bx
	mov ax, bx
	cmp ax, 5
	jb rlr
	mov bl, 5
	div bl
	mov cl, al

rlr: mov bx, 0
	mov [cRow1], cx
	mov cl, ah
	mov [cCol1], cx
	mov cx, 0

rl2:	mov ah, [matrix+ebx]
	cmp ah, dl
	je rs2
	add bx, 1
	jmp rl2

rs2: mov [Tindex2], bx
	mov ax, bx
	cmp ax, 5
	jb rck1
	mov bl, 5
	div bl
	mov cl, al

rck1:mov bx, 0
	mov [cRow2], cx
	mov cl, ah
	mov [cCol2], cx
	mov ax, [cCol1]
	cmp ax, cx
	ja sub1
	mov dx, cx
	sub dx, ax
	jmp co1
sub1:mov dx, ax
	sub dx, cx
co1:mov [colDif], dx
	cmp cx, ax
	jne PrE31
	popa
	ret
PrE31:mov ax, [Tindex1]
	mov bx, [colDif]
	add ax, bx
	mov cl, 5
	div cl
	mov dl, ah
	mov si, dx
	mov di, [cCol2]
	cmp si, di
	je correct1
	mov ax, [Tindex1]
	sub ax, bx
	mov cl, 5
	div cl
	mov dl, ah
	mov si, dx
	cmp si, di
	je correct2
	popa
	ret
;::::::::::::::::::::::::::::::
correct1:	
	mov ax, [Tindex1]
	add ax, bx
	mov bx, ax
	mov ch, [matrix+ebx]
	mov bx, [Sindex1]
	mov [string+ebx], ch
	jmp PrE32
correct2:	
	mov ax, [Tindex1]
	sub ax, bx
	mov bx, ax
	mov ch, [matrix+ebx]
	mov bx, [Sindex1]
	mov [string+ebx], ch
	jmp PrE32
;-------------------------------
PrE32:	mov ax, [Tindex2]
	mov bx, [colDif]
	add ax, bx
	mov cl, 5
	div cl
	mov dl, ah
	mov si, dx
	mov di, [cCol1]
	cmp si, di
	je correct3
	mov ax, [Tindex2]
	sub ax, bx
	mov cl, 5
	div cl
	mov dl, ah
	mov si, dx
	cmp si, di
	je correct4
	popa
	ret
;::::::::::::::::::::::::::::::
correct3:	
	mov ax, [Tindex2]
	add ax, bx
	mov bx, ax
	mov ch, [matrix+ebx]
	mov bx, [Sindex2]
	mov [string+ebx], ch
	popa
	ret
correct4:	
	mov ax, [Tindex2]
	sub ax, bx
	mov bx, ax
	mov ch, [matrix+ebx]
	mov bx, [Sindex2]
	mov [string+ebx], ch
	popa
	ret

terminate:	
	call crlf
	call crlf
	mov edx, offset msg3
	call writestring
	mov edx, offset String
	call writestring
	call crlf
	call crlf

	mov ax, 0
main ENDP
END main