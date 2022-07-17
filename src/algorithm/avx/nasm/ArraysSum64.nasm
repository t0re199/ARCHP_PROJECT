section .data

    ITEMS_IN_PARALLEL equ 0x4


section .bss



section .text
    global arraysSum64


    arraysSum64:
        push rbp
        mov rbp, rsp
        push r10
        push r11
        
        ;   rdi dest
        ;   rsi src
        ;   rdx len

        .loop:
            cmp rdx, ITEMS_IN_PARALLEL
            jl .end
            
            vmovapd ymm0, [rsi]
            vaddpd ymm0, [rdi]
            vmovapd [rdi], ymm0
            
            add rsi, 0x20
            add rdi, 0x20

            sub rdx, ITEMS_IN_PARALLEL
            jmp .loop

        .end:
            pop r11
            pop r10
            mov rsp, rbp
            pop rbp
            ret
