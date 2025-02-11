BITS 64

section .text
    global strlen

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
