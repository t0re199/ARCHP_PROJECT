section .data

    ITEMS_IN_PARALLEL equ 0x4


section .bss


section .text
    global dot64

    dot64:
        push rbp
        mov rbp, rsp
        push r10
        push r11

        ;   rdi xj
        ;   rsi xi
        ;   rdx len
        ;   rcx acc
        
        vxorpd ymm0, ymm0

        .loop:
            cmp rdx, ITEMS_IN_PARALLEL
            jl .reduce
            vmovapd ymm1, [rdi]
            vmulpd ymm1, [rsi]
            vaddpd ymm0, ymm1
            add rdi, 0x20
            add rsi, 0x20
            sub rdx, ITEMS_IN_PARALLEL
            jmp .loop

        .reduce:
            vhaddpd ymm0, ymm0
            vextractf128 xmm1, ymm0, 0x1
            addpd xmm0, xmm1
    
        movsd [rcx], xmm0

        pop r11
        pop r10
        mov rsp, rbp
        pop rbp
        ret

