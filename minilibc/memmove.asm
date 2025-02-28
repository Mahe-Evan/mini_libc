BITS 64

section .text
global memmove

memmove:
    ENTER 0, 0
    mov rax, rdi ; Save original destination pointer
    cmp rdi, 0 ; Check if destination is null
    je .return_null ; Return null if destination is null
    cmp rsi, 0 ; Check if source is null
    je .done ; return the dest if src is null
    cmp rsi, rdi ; Compare source and destination pointers
    je .done ; If they are the same, nothing to do
    jae .forward ; If source is after destination, copy forward
    jmp .backward ; Otherwise, copy backward

.forward:
    mov rcx, rdx ; Copy `n` (rdx) into rcx for loop counter
    jmp .floop

.finc:
    inc rsi  ; Increment source pointer
    inc rdi  ; Increment destination pointer
    dec rcx  ; Decrement counter
    jmp .floop ; Jump to loop

.floop:
    test rcx, rcx ; Check if all bytes are copied
    jz .done
    mov dl, [rsi] ; Load byte from source
    mov [rdi], dl ; Store byte into destination
    jmp .finc ; Jump to inc

.backward:
    add rsi, rdx ; Move source pointer to the end
    add rdi, rdx ; Move destination pointer to the end
    mov rcx, rdx ; Copy `n` (rdx) into rcx for loop counter
    dec rsi  ; Decrement source pointer
    dec rdi  ; Decrement destination pointer
    jmp .bloop

.bdec:
    dec rsi  ; Decrement source pointer
    dec rdi  ; Decrement destination pointer
    dec rcx  ; Decrement counter
    jmp .bloop ; Jump to loop

.bloop:
    test rcx, rcx ; Check if all bytes are copied
    jz .done
    mov dl, [rsi] ; Load byte from source
    mov [rdi], dl ; Store byte into destination
    jmp .bdec ; Jump to dec

.return_null:
    xor rax, rax ; Set rax to 0

.done:
    LEAVE
    ret