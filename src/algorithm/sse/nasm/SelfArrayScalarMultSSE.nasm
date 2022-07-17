section .data
    dest equ 0x8
    len equ 0xc
    scalar equ 0x10

    ITEMS_IN_PARALLEL equ 0x4


section .bss



section .text
    global selfArrayScalarMult32
    global unalignedselfArrayScalarMult32


    selfArrayScalarMult32:
        push ebp
        mov ebp, esp
        push ebx
        push esi
        push edi

        mov esi, [ebp + len]    ;len
        mov eax, [ebp + dest]   ;dest
        
        movss xmm0, [ebp + scalar]  ;scalar
        shufps xmm0, xmm0, 0x0

        .loop:
            cmp esi, ITEMS_IN_PARALLEL
            jl .end
            
            movaps xmm1, [eax]
            mulps xmm1, xmm0
            movaps [eax], xmm1
            
            add eax, 0x10

            sub esi, ITEMS_IN_PARALLEL
            jmp .loop

        .end:
            pop edi
            pop esi
            pop ebx
            mov esp, ebp
            pop ebp
            ret


    unalignedselfArrayScalarMult32:
        push ebp
        mov ebp, esp
        push ebx
        push esi
        push edi

        mov esi, [ebp + len]    ;len
        mov eax, [ebp + dest]   ;dest
        
        movss xmm0, [ebp + scalar]  ;scalar
        shufps xmm0, xmm0, 0x0

        .loop:
            cmp esi, ITEMS_IN_PARALLEL
            jl .sloop
            
            movups xmm1, [eax]
            mulps xmm1, xmm0
            movups [eax], xmm1
            
            add eax, 0x10

            sub esi, ITEMS_IN_PARALLEL
            jmp .loop

        .sloop:
            cmp esi, 0x0
            jle .end

            movss xmm1, [eax]
            mulss xmm1, xmm0
            movss [eax], xmm1
    
            add eax, 0x4
    
            dec esi
            jmp .sloop

        .end:
            pop edi
            pop esi
            pop ebx
            mov esp, ebp
            pop ebp
            ret
