BITS 32

section .text
global xstrchr

xstrchr:
    ENTER 0, 0
    xor ecx, ecx ; set ecx to zero
    jmp .loop ;jump loop

.inc:
    inc ecx ;inc ecx

.loop:
    movzx edx, BYTE [edi+ecx]  ; The movzx (move with zero extension) instruction loads the byte from memory into the edx register and zero-extends it to fill the entire 64-bit register
    cmp edx, esi ;compare edx and esi
    je .found  ;if equal jump to found
    test edx, edx ; test if edx = 0
    jz .null ; zero jump null
    jmp .inc ;jump inc

.found:
    lea eax, [edi+ecx] ;loads the effective address of edi + ecx into eax without performing a memory access.
    LEAVE ;leave and ret
    ret

.null:
    xor eax, eax ;set eax to 0
    LEAVE ;leave and ret
    ret

