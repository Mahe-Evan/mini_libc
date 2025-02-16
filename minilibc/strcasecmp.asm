BITS 64

section .text
global strcasecmp

strcasecmp:
    ENTER 0, 0 ; Enter the function
    xor rcx, rcx ; Set rcx to 0
    jmp .loop ; Jump to loop

.to_lower_al:
    cmp al, 'A'
    jl .to_lower_dl ; If al < 'A', return
    cmp al, 'Z'
    jg .to_lower_dl ; If al > 'Z', return
    add al, 32 ; Convert to lowercase

.to_lower_dl:
    cmp dl, 'A'
    jl .done ; If dl < 'A', return
    cmp dl, 'Z'
    jg .done ; If dl > 'Z', return
    add dl, 32 ; Convert dl to lowercase
    jmp .compare

.inc:
    inc rcx ; Increment rcx

.loop:
    mov al, BYTE [rdi+rcx]  ; Load byte from rdi+rcx into al
    mov dl, BYTE [rsi+rcx]  ; Load byte from rsi+rcx into dl
    call .to_lower_al ; Convert both to lowercase

.compare:
    cmp al, dl ; Compare characters
    jne .done ; If not equal, jump to done
    test al, al ; Check if end of string (null terminator)
    je .done ; If end of string, jump to done
    jmp .inc ; jump to inc


.done:
    movzx rax, al ; Zero-extend al to rax
    movzx rdx, dl  ; Zero-extend dl to rdx
    sub rax, rdx   ; subtract dl from al to get the result
    LEAVE ; Leave and return
    ret
