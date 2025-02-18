BITS 64

section .text
global strpbrk

strpbrk:
    ENTER 0, 0
    xor rcx, rcx ;set rcx to 0
    jmp .loop ;jump to loop

.inc:
    inc rcx ;increment rcx

.loop:
    mov al, [rdi+rcx] ; mov car from src to al
    test al, al ; Check if end of string
    jz .return_null

    xor r8, r8 ; reset sub_loop counter
    jmp .second_loop ; jump to second loop

.second_inc:
    inc r8 ; increment sub_loop counter
    jmp .second_loop

.second_loop:
    mov dl, [rsi+r8] ; load character from second string
    test dl, dl ; test if end of second string
    jz .inc ; if end of second string, increment rcx and continue outer loop
    cmp al, dl ; compare characters
    je .setnonnull ; if equal, set return value
    jmp .second_inc ; if not equal, increment sub_loop counter

.setnonnull:
    lea rax, [rdi+rcx] ; Set return value to str found
    jmp .end

.return_null:
    xor rax, rax ; set rax to null
    jmp .end

.end:
    LEAVE
    ret
