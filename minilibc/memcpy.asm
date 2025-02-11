BITS 64

section .text
global memcpy

memcpy:
    ENTER 0, 0
    mov rcx, rdx ; set counter with rdx arg
    mov rax, rdi ; save the dest in the return arg
    jmp .loop ; jump loop

.ops:
    inc rsi ; Increment source pointer
    inc rdi ; Increment destination pointer
    dec rcx ; Decrement counter

.loop:
    test rcx, rcx ; Check if rcx is 0
    jz .done ; If zero, jump to done
    mov al, [rsi] ;move the char of src in al
    mov [rdi], al ;move the char al in the dest
    jmp .ops ;jump ops

.done:
    mov rax, rdi ; set rdi to rax for return
    LEAVE
    ret