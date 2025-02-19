BITS 64

section .text
global memcpy

memcpy:
    ENTER 0, 0
    mov rax, rdi ; Save original destination pointer
    cmp rdx, 0 ; If size (rdx) is zero, return immediately
    je .done
    mov rcx, rdx ; Copy `n` (rdx) into rcx for loop counter
    jmp .loop ; Jump to loop

.inc:
    inc rsi  ; Increment source pointer
    inc rdi  ; Increment destination pointer
    dec rcx  ; Decrement counter
    jmp .loop ; Jump to loop

.loop:
    test rcx, rcx ; Check if all bytes are copied
    jz .done
    mov dl, [rsi] ; Load byte from source
    mov [rdi], dl ; Store byte into destination
    jmp .inc ;jump to inc

.done:
    LEAVE
    ret
