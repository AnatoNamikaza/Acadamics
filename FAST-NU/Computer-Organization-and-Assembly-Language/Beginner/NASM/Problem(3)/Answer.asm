[org 0x0100]


            jmp work
            arr1:   dw 11, 23, 15, 9, 2, 3, 1, 6, 8, 10, -1 ; "-1" value will show end of the array

            num:    dw 6                                    ; number to be found in the array
            size:   dw 0       
                        
    work:   mov dx, [arr1 + si]
            add bx, 2
            mov ax, [arr1 + bx]
            mov cx, 0
            jmp sort
            

;code       

    sort:   cmp ax, dx                                      ; swap sorting is being applied
            jl cnd1
            jg cnd2

    cnd1:   cmp ax, -1
            je gan
            mov cx, 1
            mov [arr1 + si], ax
            mov [arr1 + bx], dx
            mov dx, [arr1 + si]
            mov bx, si
            add bx, 2
            mov ax, [arr1 + bx]
            jmp sort

    cnd2:   add bx, 2
            mov ax, [arr1 + bx]
            jmp sort

    gan:    cmp cx, 0
            je chkl
            add si, 2
            mov dx, [arr1 + si]
            mov bx, si
            add bx, 2
            mov ax, [arr1 + bx]
            mov cx, 0
            jmp sort

    chkl:   mov ax, 0
            mov bx, 0
            mov cx, 0
            mov dx, 0
            mov si, 0
            jmp l1
            
    l1:     mov ax, [arr1 + si]                             ; checkerloop to see if the array is sorted
            cmp ax, -1
            je strt2
            add si, 2
            add di, 1
            mov [size], di
            jmp l1
            
    strt2:  mov ax, 0
            mov bx, 0
            mov cx, 0
            mov dx, 0
            mov si, 0
            mov di, 0
            mov bp, 0
            jmp half

            
    half:   mov ax, [size]
            cmp ax, 0
            je  tx
            mov bl, 2
            div bl
            mov [size], al
            mov di, [size]
            mov ax, 0
            add dx, di
            mov bp, dx
            mov si, 0
            jmp Loq
            
    Loq:    cmp bp, 0
            je find
            add si, 2
            sub bp, 1
            jmp Loq
            
    find:   mov ax, [arr1+si]
            mov bx, [num]
            cmp ax, bx
            je found
            jl half
            mov ax, [size]
            cmp ax, 0                                        ; if size becomes zero and num is not found in array then zero is moved in register "ax" 
            je  tx
            mov bl, 2
            div bl
            mov [size], al
            mov di, [size]
            mov ax, 0
            sub dx, di
            mov bp, dx
            mov si, 0
            jmp Loq
            
    found:  mov ax, 1                                       ; 1 is moved to register "ax" is num is found 
            mov bx, 2732                                    ; AAC is displayed in bx is num is found
            mov cx, 0
            mov dx, 0
            mov si, 0
            mov di, 0
            mov bp, 0
            mov ax, 0x4c00                                  ; termination of program
            int 0x21
            
    tx:     mov bx, 0
            mov cx, 0
            mov dx, 0
            mov si, 0
            mov di, 0
            mov bp, 0
            mov ax, 0x4c00                                  ; termination of program
            int 0x21
