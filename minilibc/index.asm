BITS 64

section .text
global index
strchr:
    ENTER 0, 0
    xor rcx, rcx ; set rcx to zero
    jmp .loop ;jump loop

.inc:
    inc rcx ;inc rcx

.loop:
    movzx rdx, BYTE [rdi+rcx]  ; The movzx (move with zero extension) instruction loads the byte from memory into the rdx register and zero-extends it to fill the entire 64-bit register
    cmp rdx, rsi ;compare rdx and rsi
    je .found  ;if equal jump to found
    test rdx, rdx ; test if rdx = 0
    jz .null ; zero jump null
    jmp .inc ;jump inc

.found:
    lea rax, [rdi+rcx] ;loads the effective address of rdi + rcx into rax without performing a memory access.
    LEAVE ;leave and ret
    ret

.null:
    xor eax, eax ;set eax to 0
    LEAVE ;leave and ret
    ret

index:
    ENTER 0, 0

    call strchr

    LEAVE
    RET