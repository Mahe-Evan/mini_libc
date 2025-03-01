BITS 32

section .text
global xstrcspn

xstrcspn:
    ENTER 0, 0
    push ebx
    xor ecx, ecx ;set ecx to 0
    jmp .loop ;jump to loop

.inc:
    inc ecx ;increment ecx

.loop:
    mov al, [edi+ecx] ; mov car from src to al
    test al, al ; Check if end of string
    jz .return_not_found

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
    je .return_count ; if equal, set return value
    jmp .second_inc ; if not equal, increment sub_loop counter

.return_not_found:
    mov eax, ecx ; set eax to count
    jmp .end

.return_count:
    mov eax, ecx ; set eax to count
    jmp .end

.end:
    pop ebx
    LEAVE
    ret