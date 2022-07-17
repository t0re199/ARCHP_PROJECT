section .data
    xj equ 0x8
    xi equ 0xc
    len equ 0x10
    acc equ 0x14

    ELEMENTS equ 0x4


section .bss


section .text
    global dot32
    global unalignedDot32

    dot32:
        push ebp
        mov ebp, esp
        push ebx
        push esi
        push edi

        mov edi, [ebp + acc]
        mov esi, [ebp + len]
        mov eax,  [ebp + xj]
        mov ebx, [ebp + xi]
        
        xorps xmm0, xmm0

        .loop:
            cmp esi, ELEMENTS
            jl .reduce
            movaps xmm1, [eax]
            mulps xmm1, [ebx]
            addps xmm0, xmm1
            add eax, 0x10
            add ebx, 0x10
            sub esi, ELEMENTS
            jmp .loop

        .reduce:
            haddps xmm0, xmm0
            haddps xmm0, xmm0
    
        movss [edi], xmm0

        pop edi
        pop esi
        pop ebx
        mov esp, ebp
        pop ebp
        ret



    unalignedDot32:
        push ebp
        mov ebp, esp
        push ebx
        push esi
        push edi

        mov edi, [ebp + acc]
        mov esi, [ebp + len]
        mov eax,  [ebp + xj]
        mov ebx, [ebp + xi]
        
        xorps xmm0, xmm0

        .loop:
            cmp esi, ELEMENTS
            jl .sloop
            movups xmm1, [eax]
            movups xmm2, [ebx]
            mulps xmm1, xmm2
            addps xmm0, xmm1
            add eax, 0x10
            add ebx, 0x10
            sub esi, ELEMENTS
            jmp .loop
        
        .sloop:
            cmp esi, 0x0
            jle .reduce
            movss xmm1, [eax]
            mulss xmm1, [ebx]
            addss xmm0, xmm1
            add eax, 0x4
            add ebx, 0x4
            dec esi
            jmp .sloop

        .reduce:
            haddps xmm0, xmm0
            haddps xmm0, xmm0
    
        movss [edi], xmm0

        pop edi
        pop esi
        pop ebx
        mov esp, ebp
        pop ebp
        ret