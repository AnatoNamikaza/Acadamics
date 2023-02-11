INCLUDE Irvine32.inc

.data
	ms1 byte "Enter Numbers for Array: ", 0
	ms2 byte "Array before sorting: ", 0
	ms3 byte "Array after sorting: ", 0
	
	ds1 byte "Enter Number to search in Array: ", 0
	ds2 byte "Number found status: ", 0
;	Array db 2,4,7,1,0,8,3,5   ; For test run
	Array db 8 dup(0)
	ArraySize byte 8
	swap db 0

.code

main PROC
	call InputArray
	mov edx, offset ms2
	call writestring 
	call crlf
	call DisplayArray
	call crlf
	mov edx, offset ms3
	call writestring 
	call crlf
	call BubbleSort
	call DisplayArray
	call crlf
	call BinarySearch
	jmp terminate

InputArray:
	pusha
	mov edx, offset ms1
	call writestring 
	call crlf
	mov esi, offset Array
	mov ebx, 0
	mov eax, 0
l1:	call readint
	mov [esi+ebx], al
	inc bx
	cmp bx, 8
	jb l1
	call crlf
	popa
	ret

DisplayArray:
	pusha
	mov ebx, 0
	mov esi, offset Array
d7:	mov eax, 0
	mov al, ' '
	call writechar
	call writechar
	mov al, [esi+ebx]
	call writeint
	inc bx
	cmp bx, 8
	jb d7
	call crlf
	popa
	ret

BubbleSort:
	pusha
	mov eax, 0
	mov ecx, 0
	mov esi, offset Array
BS:	mov ebx, 0 
	mov [swap], 0 
lp1:mov al, [esi+ebx]
	mov cl, [esi+ebx+1]
	cmp al, cl
	jbe Sop
	mov [esi+ebx+1], al
	mov [esi+ebx], cl
	mov [swap], 1
Sop: inc bx
	cmp bx, 7			;Always compare by n-1, where n is size of array
	jb lp1
	cmp [swap], 1
	je BS 
	popa
	ret

BinarySearch:
	pusha
	mov edx, offset ds1
	call writestring 
	call crlf
	mov eax, 0
	mov ebx, 0
	mov ecx, 0
	mov edx, 0
	mov ebp, 0
	call readint
	mov ch, al
	mov esi, offset ArraySize
	mov cl, [esi]
	mov edi, offset Array
	mov al, [esi]
	cmp al, 0
	je  tx
	mov bl, 2
	div bl
	mov [esi], al
	mov ah, 0
	mov	bp, ax
half:mov ax, bp
	mov bx, 2
	div bx
	mov bp, ax
	mov ebx, 0
	mov bl, [esi]
	mov al, [edi+ebx]
	cmp al, ch
	je Isfound
	cmp ch, al
	ja UpCheck
	jmp LowCheck

UpCheck:
	mov al, [esi]
	add ax, bp
	mov [esi], al
	cmp al, cl
	jbe	half
	jmp Notfound

LowCheck:
	mov al, [esi]
	sub ax, bp
	mov [esi], al
	cmp al, 0
	jae	half
	jmp Notfound

Isfound:
	call crlf
	mov edx, offset ds2
	call writestring 
	mov ax, 1                                       ; 1 is moved to register "ax" is num is found 
	call writeint
	call crlf
	jmp tx

Notfound:
	call crlf
	mov edx, offset ds2
	call writestring 
	mov ax, 0                                       ; 1 is moved to register "ax" is num is found 
	call writeint
	call crlf

tx: popa
	ret

terminate:	
	call crlf
	call crlf
	mov ax, 0
main ENDP
END main