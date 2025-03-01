BITS 32

section .text
global xmemset

xmemset:
    ENTER 0, 0
    xor ecx, ecx ;set ecx to 0
    jmp .loop ;jump to loop

.inc:
    inc ecx ;inc

.loop:
    cmp ecx, edx ;comp edx and ecx
    je .done ;if eq, done
    mov BYTE [edi+ecx], al ;store al in the BYTE (al is the char to put in)
    jmp .inc ;jump inc

.done:
    mov eax, edi ; move edi to eax
    LEAVE
    ret