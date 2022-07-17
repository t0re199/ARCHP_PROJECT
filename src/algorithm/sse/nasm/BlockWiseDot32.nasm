section .data
    data equ 0x8
    xi equ 0xc
    len equ 0x10
    acc equ 0x14

    ITEMS_IN_PARALLEL equ 0x4

    ONE dd 1.0


section .bss



section .text
    global blockWiseDot32
    global unalignedBlockWiseDot32
    
    blockWiseDot32:
        push ebp
        mov ebp, esp
        push ebx
        push esi
        push edi

        mov esi, [ebp + len]
        mov eax, [ebp + data]  ;xj
        lea ebx, [eax + esi * 0x4] ;xj+1
        lea ecx, [ebx + esi * 0x4]  ;xj+2
        lea edx, [ecx + esi * 0x4] ;xj+3
        mov edi, [ebp + xi] ;xi

        xorps xmm0, xmm0
        xorps xmm1, xmm1
        xorps xmm2, xmm2
        xorps xmm3, xmm3

        .loop:
            cmp esi, ITEMS_IN_PARALLEL
            jl .reduce
            
            movaps xmm4, [eax]
            movaps xmm5, [ebx]
            movaps xmm6, [ecx]

            movaps xmm7, [edi]
            
            mulps xmm4, xmm7
            mulps xmm5, xmm7
            mulps xmm6, xmm7

            addps xmm0, xmm4
            addps xmm1, xmm5
            addps xmm2, xmm6
            
            movaps xmm4, [edx]
            mulps xmm4, xmm7
            addps xmm3, xmm4
            
            add eax, 0x10
            add ebx, 0x10
            add ecx, 0x10
            add edx, 0x10

            add edi, 0x10

            sub esi, ITEMS_IN_PARALLEL
            jmp .loop

        .reduce:
            haddps xmm0, xmm1
            haddps xmm2, xmm3

            haddps xmm0, xmm2
        
        movss xmm1, [ONE]
        shufps xmm1, xmm1, 0x0
        addps xmm0, xmm1

        
        mov edi, [ebp + acc]    
        movaps [edi], xmm0
        
        pop edi
        pop esi
        pop ebx
        mov esp, ebp
        pop ebp
        ret

        

    unalignedBlockWiseDot32:
        push ebp
        mov ebp, esp
        push ebx
        push esi
        push edi

        mov esi, [ebp + len]
        mov eax, [ebp + data]  ;xj
        lea ebx, [eax + esi * 0x4] ;xj+1
        lea ecx, [eax + esi * 0x8]  ;xj+2

        mov edi, [ebp + xi] ;xi

        xorps xmm0, xmm0
        xorps xmm1, xmm1
        xorps xmm2, xmm2


        .loop:
            cmp esi, ITEMS_IN_PARALLEL
            jl .reduce

            movups xmm3, [edi]

            movups xmm4, [eax]
            movups xmm5, [ebx]
            movups xmm6, [ecx]
            
            mulps xmm4, xmm3
            mulps xmm5, xmm3
            mulps xmm6, xmm3

            addps xmm0, xmm4
            addps xmm1, xmm5
            addps xmm2, xmm6

            add eax, 0x10
            add ebx, 0x10
            add ecx, 0x10

            add edi, 0x10

            sub esi, ITEMS_IN_PARALLEL
            jmp .loop

        .reduce:
            haddps xmm0, xmm1
            haddps xmm2, xmm3

            haddps xmm5, xmm6
        
        movss xmm1, [ONE]
        shufps xmm1, xmm1, 0x0
        addps xmm0, xmm1

        addps xmm2, xmm1

        mov edi, [ebp + acc]
        movups [edi], xmm0
        movss [edi + 0x10], xmm1


        pop edi
        pop esi
        pop ebx
        mov esp, ebp
        pop ebp
        ret