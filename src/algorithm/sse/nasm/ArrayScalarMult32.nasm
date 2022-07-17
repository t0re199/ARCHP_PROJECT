section .data
    dest equ 0x8
    src equ 0xc
    len equ 0x10
    scalar equ 0x14

    ITEMS_IN_PARALLEL equ 0x4


section .bss



section .text
    global arrayScalarMult32
    global unalignedArrayScalarMult32


    arrayScalarMult32:
        push ebp
        mov ebp, esp
        push ebx
        push esi
        push edi

        mov esi, [ebp + len]    ;len
        mov eax, [ebp + dest]   ;dest
        mov ebx, [ebp + src]    ;src
        
        movss xmm0, [ebp + scalar]  ;scalar
        shufps xmm0, xmm0, 0x0

        .loop:
            cmp esi, ITEMS_IN_PARALLEL
            jl .end
            
            movaps xmm1, [ebx]
            mulps xmm1, xmm0
            movaps [eax], xmm1
            
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


    unalignedArrayScalarMult32:
        push ebp
        mov ebp, esp
        push ebx
        push esi
        push edi

        mov esi, [ebp + len]    ;len
        mov eax, [ebp + dest]   ;dest
        mov ebx, [ebp + src]    ;src
        
        movss xmm0, [ebp + scalar]  ;scalar
        shufps xmm0, xmm0, 0x0

        .loop:
            cmp esi, ITEMS_IN_PARALLEL
            jl .sloop
            
            movaps xmm1, [ebx]
            mulps xmm1, xmm0
            movaps [eax], xmm1
            
            add eax, 0x10
            add ebx, 0x10

            sub esi, ITEMS_IN_PARALLEL
            jmp .loop

        .sloop:
            cmp esi, 0x0
            jle .end

            movss xmm1, [ebx]
            mulss xmm1, xmm0
            movss [eax], xmm1
    
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
