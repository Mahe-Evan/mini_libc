BITS 64

section .text
global memmove

memmove:
    ENTER 0, 0
    cmp rdx, 0 ; check if rdx is 0
    jz .done ; if zero, jump to done
    mov rcx, rdx ; set counter with rdx arg
    mov rax, rdi ; save the dest in the return arg
    cmp rsi, rdi ; compare src and dest
    jae .forward ; if src is greater or equal to dest, jump to forward
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

.fops:
    dec rsi ; Decrement source pointer
    dec rdi ; Decrement destination pointer
    dec rcx ; Decrement counter

.floop:
    test rcx, rcx ; Check if rcx is 0
    jz .done ; If zero, jump to done
    mov al, [rsi] ;move the char of src in al
    mov [rdi], al ;move the char al in the dest
    jmp .fops ;jump fops

.forward:
    add rsi, rcx ; Move source pointer to the end
    add rdi, rcx ; Move destination pointer to the end
    jmp .floop ; Jump to loop


.done:
    mov rax, rdi ; set rdi to rax for return
    LEAVE
    ret