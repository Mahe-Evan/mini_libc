BITS 64

section .text
global strcspn

strcspn:
    ENTER 0, 0
    xor rcx, rcx ;set rcx to 0
    jmp .loop ;jump to loop

.inc:
    inc rcx ;increment rcx

.loop:
    mov al, [rdi+rcx] ; mov car from src to al
    test al, al ; Check if end of string
    jz .return_not_found

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
    je .return_count ; if equal, set return value
    jmp .second_inc ; if not equal, increment sub_loop counter

.return_not_found:
    mov rax, rcx ; set rax to count
    jmp .end

.return_count:
    mov rax, rcx ; set rax to count
    jmp .end

.end:
    LEAVE
    ret