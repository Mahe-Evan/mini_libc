BITS 64

section .text
    global strrchr

strlen:
    ENTER 0, 0  ;enter the fonction
    xor rax, rax    ;set rax to 0
    jmp .loop   ;got to loop

.inc:
    inc rax ;inc rax 

.loop:  ;loop
    movzx rdx, byte [rdi + rax] ; The movzx (move with zero extension) instruction loads the byte from memory into the rdx register and zero-extends it to fill the entire 64-bit register
    test rdx, rdx ;test if rdx is zero with a end
    jz .done ;jump to done if zero
    jmp .inc ;jump to inc

.done:
    LEAVE ;leave and return
    ret


strrchr:
    ENTER 0, 0
    call strlen ;call strlen
    mov rcx, rax ;move rax in rcx
    lea rdi, [rdi + rcx] ;loads the effective address of rdi + rcx into rdi without performing a memory access.
    xor rax, rax ;set rax to 0

.loop:
    cmp rcx, 0 ;comp rcx and 0
    jl .done ;jump less

    movzx rdx, byte [rdi] ; The movzx (move with zero extension) instruction loads the byte from memory into the rdx register and zero-extends it to fill the entire 64-bit register
    cmp rdx, rsi ;comp rdx and rsi
    je .found ;jump equal

    dec rdi ;sub 1 to rdi and rdx
    dec rcx
    jmp .loop

.found:
    mov rax, rdi ;move rdi in rax

.done:
    LEAVE
    ret
