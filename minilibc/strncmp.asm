BITS 64

section .text
global strncmp

strncmp:
    ENTER 0, 0 ;enter the function
    mov r8, rdx
    xor rcx, rcx ;set rcx to 0
    jmp .loop ;jump to loop

.inc:
    inc rcx ;inc rcx

.loop:
    cmp rcx, r8 ;comp the counter with the length
    je .zero_done ;if equal, jump to zero_done
    mov al, BYTE [rdi+rcx] ; load byte from rdi+rcx into al
    mov dl, BYTE [rsi+rcx] ; load byte from rsi+rcx into dl
    cmp al, dl ; compare al with dl
    jne .done ; if not equal, jump to done
    test al, al ; check if end of string (null terminator)
    je .zero_done ; if end of string, jump to zero_done
    jmp .inc ; jump to inc

.zero_done:
    xor rax, rax ; set rax to 0
    LEAVE ; leave and return
    ret

.done:
    movzx rax, al ; zero-extend al to rax
    movzx rdx, dl ; zero-extend dl to rdx
    sub rax, rdx ; subtract dl from al to get the result
    LEAVE ; leave and return
    ret
