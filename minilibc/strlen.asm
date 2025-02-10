BITS 64

section .text
global strlen

strlen:
    push rbp
    mov rbp, rsp
    mov QWORD [rbp-0x18], rdi
    mov DWORD [rbp-0x4], 0x0
    jmp .loop
.inc:
    add DWORD [rbp-0x4], 0x1
.loop:
    mov eax, DWORD [rbp-0x4]
    movsxd rdx, eax
    mov rax, QWORD [rbp-0x18]
    add rax, rdx
    movzx eax, BYTE [rax]
    test al, al
    jnz .inc
    mov eax, DWORD [rbp-0x4]
    cdqe
    pop rbp
    ret
