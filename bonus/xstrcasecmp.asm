BITS 32

section .text
global xstrcasecmp

xstrcasecmp:
    ENTER 0, 0 ; Enter the function
    xor ecx, ecx ; Set ecx to 0
    jmp .loop ; Jump to loop

.to_lower_al:
    cmp al, 'A'
    jl .to_lower_dl ; If al < 'A', return
    cmp al, 'Z'
    jg .to_lower_dl ; If al > 'Z', return
    add al, 32 ; Convert to lowercase

.to_lower_dl:
    cmp dl, 'A'
    jl .compare ; If dl < 'A', compare
    cmp dl, 'Z'
    jg .compare ; If dl > 'Z', compare
    add dl, 32 ; Convert dl to lowercase
    jmp .compare

.inc:
    inc ecx ; Increment ecx

.loop:
    mov al, BYTE [edi+ecx]  ; Load byte from edi+ecx into al
    mov dl, BYTE [esi+ecx]  ; Load byte from esi+ecx into dl
    call .to_lower_al ; Convert both to lowercase

.compare:
    cmp al, dl ; Compare characters
    jne .done ; If not equal, jump to done
    test al, al ; Check if end of string (null terminator)
    je .done ; If end of string, jump to done
    jmp .inc ; jump to inc


.done:
    movzx eax, al ; Zero-extend al to eax
    movzx edx, dl  ; Zero-extend dl to edx
    sub eax, edx   ; subtract dl from al to get the result
    LEAVE ; Leave and return
    ret
