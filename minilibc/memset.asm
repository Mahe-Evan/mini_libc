BITS 64

section .text
global memset

memset:
    ENTER 0, 0
    xor rcx, rcx ;set rcx to 0
    jmp .loop ;jump to loop

.inc:
    inc rcx ;inc

.loop:
    cmp rcx, rdx ;comp rdx and rcx
    je .done ;if eq, done
    mov BYTE [rdi+rcx], sil ;store sil in the BYTE (sil is the char to put in) (sil is the low part of rsi)
    jmp .inc ;jump inc

.done:
    mov rax, rdi ; move rdi to rax
    LEAVE
    ret