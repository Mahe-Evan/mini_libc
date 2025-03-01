BITS 32

section .text
global xstrstr

xstrstr:
    ENTER 0, 0
    push ebx

    xor ecx, ecx ;set ecx to 0
    jmp .check_first_string_zero

.check_first_string_zero:
    cmp BYTE [edi+ecx], 0 ; Check if first string is null
    jz .check_second_string_zero ; If null, return null
    jnz .loop ; If not null, jump to loop

.check_second_string_zero:
    cmp BYTE [esi], 0 ; Check if second string is null
    jz .setnonnull ; If null, return first string
    jnz .loop ; If not null, jump to loop

.inc:
    inc ecx ;increment ecx

.loop:
    mov al, [edi+ecx] ; mov car from src to al
    test al, al ; Check if end of string
    jz .return_null

    xor ebx, ebx ; reset sub_loop counter
    jmp .second_loop

.second_inc:
    inc ebx ; increment sub_loop counter
    jmp .second_loop

.second_loop:
    mov dl, [esi+ebx] ; load car come after
    test dl, dl ; test if src ends and is found
    jz .setnonnull

    lea ebx, [ecx+ebx] ; add the two counters
    mov al, [edi+ebx] ; Load character from the two counters
    test al, al ; If end of string, return NULL
    jz .return_null
    cmp al, dl ; Compare characters
    jne .inc ; If not equal, jump loop and next car
    jmp .second_inc ; If equal, increment sub_loop counter

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
