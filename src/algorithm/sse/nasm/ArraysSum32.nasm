section .data
    dest equ 0x8
    src equ 0xc
    len equ 0x10

    ITEMS_IN_PARALLEL equ 0x4


section .bss



section .text
    global arraysSum32
    global unlignedArraysSum32


    arraysSum32:
        push ebp
        mov ebp, esp
        push ebx
        push esi
        push edi

        mov esi, [ebp + len]    ;len
        mov eax, [ebp + dest]   ;dest
        mov ebx, [ebp + src]    ;src
        

        .loop:
            cmp esi, ITEMS_IN_PARALLEL
            jl .end
            
            movaps xmm0, [ebx]
            addps xmm0, [eax]
            movaps [eax], xmm0
            
            add eax, 0x10
            add ebx, 0x10

            sub esi, ITEMS_IN_PARALLEL
            jmp .loop

        .end:
            pop edi
            pop esi
            pop ebx
            mov esp, ebp
            pop ebp
            ret

        
    unlignedArraysSum32:
        push ebp
        mov ebp, esp
        push ebx
        push esi
        push edi

        mov esi, [ebp + len]    ;len
        mov eax, [ebp + dest]   ;dest
        mov ebx, [ebp + src]    ;src
        

        .loop:
            cmp esi, ITEMS_IN_PARALLEL
            jl .sloop
            
            movups xmm0, [ebx]
            movups xmm1, [eax]
            addps xmm0, xmm1
            movups [eax], xmm0
            
            add eax, 0x10
            add ebx, 0x10

            sub esi, ITEMS_IN_PARALLEL
            jmp .loop

        .sloop:
            cmp esi, 0x0
            jle .end

            movss xmm0, [ebx]
            movss xmm1, [eax]
            addss xmm0, xmm1
            movss [eax], xmm0
    
            add eax, 0x4
            add ebx, 0x4
    
            dec esi
            jmp .sloop
        
        .end:
            pop edi
            pop esi
            pop ebx
            mov esp, ebp
            pop ebp
            ret
