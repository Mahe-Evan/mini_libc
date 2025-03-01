BITS 32

section .text
global xstrpbrk

xstrpbrk:
    ENTER 0, 0
    push ebx
    xor ecx, ecx ;set ecx to 0
    jmp .loop ;jump to loop

.inc:
    inc ecx ;increment ecx

.loop:
    mov al, [edi+ecx] ; mov car from src to al
    test al, al ; Check if end of string
    jz .return_null

    xor ebx, ebx ; reset sub_loop counter
    jmp .second_loop ; jump to second loop

.second_inc:
    inc ebx ; increment sub_loop counter
    jmp .second_loop

.second_loop:
    mov dl, [esi+ebx] ; load character from second string
    test dl, dl ; test if end of second string
    jz .inc ; if end of second string, increment ecx and continue outer loop
    cmp al, dl ; compare characters
    je .setnonnull ; if equal, set return value
    jmp .second_inc ; if not equal, increment sub_loop counter

.setnonnull:
    lea eax, [edi+ecx] ; Set return value to str found
    jmp .end

.return_null:
    xor eax, eax ; set eax to null
    jmp .end

.end:
    pop ebx
    LEAVE
    ret
