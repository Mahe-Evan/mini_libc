BITS 64

section .text
global strcmp

strcmp:
    ENTER 0, 0 ;enter the function
    xor rcx, rcx ;set rcx to 0
    jmp .loop ;jump to loop

.inc:
    inc rcx ;inc rcx

.loop:
    mov al, BYTE [rdi+rcx] ; load byte from rdi+rcx into al
    mov dl, BYTE [rsi+rcx] ; load byte from rsi+rcx into dl
    cmp al, dl ; compare al with dl
    jne .done ; if not equal, jump to done
    test al, al ; check if end of string (null terminator)
    je .done ; if end of string, jump to done
    jmp .inc ; jump to inc

.done:
    sub rax, rdx ; subtract dl from al to get the result
    LEAVE ; leave and return
    ret
