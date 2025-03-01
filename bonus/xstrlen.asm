BITS 32

section .text
    global xstrlen

xstrlen:
    ENTER 0, 0  ; enter the function
    xor eax, eax    ; set eax to 0
    jmp .loop   ; go to loop

.inc:
    inc eax ; increment eax

.loop:  ; loop
    movzx edx, byte [edi + eax] ; load the byte from memory into the edx register and zero-extend it to fill the entire 32-bit register
    test edx, edx ; test if edx is zero
    jz .done ; jump to done if zero
    jmp .inc ; jump to inc

.done:
    LEAVE ; leave and return
    ret
