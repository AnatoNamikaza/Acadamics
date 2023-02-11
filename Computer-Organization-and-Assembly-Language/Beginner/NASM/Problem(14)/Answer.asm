[org 0x100]
jmp start

array1:		dw 1,2,3,4,5,6,7,8
lenArray1:	dw 8

FindMedian_Mean_SD:
	push bp
	mov bp, sp

Median:
	mov bx, 2
	mov ax, [bp+4]
	div bx
	mul bx
	mov bx, ax
	mov si, [bp+6]
	mov cx, [si+bx]
	mov [bp+12], cx

Mean:
	mov cx, [bp+4]
	mov ax, 0
	mov bx, 0

l1:	add ax, [si+bx]
	add bx, 2
	dec cx
	cmp cx, 0
	jne l1

	mov bx, [bp+4]
	div bx
	mov [bp+10], ax

Standard_dev:
	mov cx, [bp+4]
	mov ax, 0
	mov bx, 0
	mov di, 0

l2:	mov ax, [si+bx]
	sub ax, [bp+10]
	mov dx, ax
	mul dx
	add di, ax
	add bx, 2
	dec cx
	cmp cx, 0
	jne l2

	mov cx, [bp+4]
	dec cx
	mov ax, di
	div cx

	mov cx, 0
	mov bx, 0xFFFF
l3:	add bx, 2
	inc cx
	sub ax,	bx
	cmp ax, 0
	jnle l3

	mov [bp+8], cx


Ed:	pop bp
	ret 4

start:
	push ax
	push bx
	push cx
	push array1
	push word [lenArray1]
	;call bubblesort here
	call FindMedian_Mean_SD
	mov ax, 0
	mov bx, 0
	mov cx, 0
	mov dx, 0
	pop cx
	pop bx
	pop ax
	mov ax, 0x4c00 
	int 0x21
	