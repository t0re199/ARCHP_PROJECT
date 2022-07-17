section .data
    ONE dq 1.0

    ITEMS_IN_PARALLEL equ 0x4


section .bss



section .text
    global blockWiseDot64
    global simdReduction64
    

    blockWiseDot64:
        push rbp
        mov rbp, rsp
        push r10
        push r11

        ;   rdi data aka xj
        ;   rsi xi
        ;   rdx len
        ;   rcx acc

        lea r8, [rdi + rdx * 0x8]   ;xj+1
        lea r9, [r8 + rdx * 0x8]    ;xj+2
        lea r10, [r9 + rdx * 0x8]   ;xj+3
        lea r11, [r10 + rdx * 0x8]   ;xj+4
        lea r12, [r11 + rdx * 0x8]   ;xj+5
        lea r13, [r12 + rdx * 0x8]   ;xj+6
        lea r14, [r13 + rdx * 0x8]   ;xj+7

        vxorpd ymm0, ymm0
        vxorpd ymm1, ymm1
        vxorpd ymm2, ymm2
        vxorpd ymm3, ymm3
        vxorpd ymm4, ymm4
        vxorpd ymm5, ymm5
        vxorpd ymm6, ymm6
        vxorpd ymm7, ymm7

        .loop:
            cmp rdx, ITEMS_IN_PARALLEL
            jl .reduce

            vmovapd ymm8, [rdi]
            vmovapd ymm9, [r8]
            vmovapd ymm10, [r9]
            vmovapd ymm11, [r10]
            vmovapd ymm12, [r11]
            vmovapd ymm13, [r12]
            vmovapd ymm14, [r13]
            
            vmovapd ymm15, [rsi]

            vmulpd ymm8, ymm15
            vmulpd ymm9, ymm15
            vmulpd ymm10, ymm15
            vmulpd ymm11, ymm15
            vmulpd ymm12, ymm15
            vmulpd ymm13, ymm15
            vmulpd ymm14, ymm15
            
            vaddpd ymm0, ymm8
            vaddpd ymm1, ymm9
            vaddpd ymm2, ymm10
            vaddpd ymm3, ymm11
            vaddpd ymm4, ymm12
            vaddpd ymm5, ymm13
            vaddpd ymm6, ymm14

            vmovapd ymm8, [r14]
            vmulpd ymm8, ymm15
            vaddpd ymm7, ymm8

            add rdi, 0x20
            add r8, 0x20
            add r9, 0x20
            add r10, 0x20
            add r11, 0x20
            add r12, 0x20
            add r13, 0x20
            add r14, 0x20

            add rsi, 0x20

            sub rdx, ITEMS_IN_PARALLEL
            jmp .loop

        .reduce:
            vhaddpd ymm0, ymm0, ymm1
            vhaddpd ymm1, ymm2, ymm3
            vhaddpd ymm2, ymm4, ymm5
            vhaddpd ymm3, ymm6, ymm7
        
        vextractf128 xmm4, ymm0, 0x1
        vextractf128 xmm5, ymm1, 0x1
        vextractf128 xmm6, ymm2, 0x1
        vextractf128 xmm7, ymm3, 0x1

        addpd xmm0, xmm4
        addpd xmm1, xmm5
        addpd xmm2, xmm6
        addpd xmm3, xmm7

        vinsertf128 ymm0, ymm0, xmm1, 0x1
        vinsertf128 ymm2, ymm2, xmm3, 0x1

        vbroadcastsd ymm3, [ONE]
        
        vaddpd ymm0, ymm3
        vaddpd ymm2, ymm3

        vmovapd [rcx], ymm0
        vmovapd [rcx + 0x20], ymm2
        
        pop r11
        pop r10
        mov rsp, rbp
        pop rbp
        ret


    simdReduction64:
        push rbp
        mov rbp, rsp
        push r10
        push r11

        ;   rdi kerAccArray
        ;   rsi tmpAlphaPtr
        ;   rdx kerAcc
        
        vxorpd ymm0, ymm0

        vmovapd ymm1, [rdi]
        vmulpd ymm1, [rsi]
        vaddpd ymm0, ymm1
        
        vmovapd ymm1, [rdi + 0x20]
        vmulpd ymm1, [rsi + 0x20]
        vaddpd ymm0, ymm1

        vhaddpd ymm0, ymm0
        vextractf128 xmm1, ymm0, 0x1
        addpd xmm0, xmm1

        movsd [rdx], xmm0

        pop r11
        pop r10
        mov rsp, rbp
        pop rbp
        ret
