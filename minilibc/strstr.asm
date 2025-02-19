BITS 64

section .text
global strstr

strstr:
    ENTER 0, 0

    xor rcx, rcx ;set rcx to 0
    jmp .check_first_string_zero

.check_first_string_zero:
    cmp BYTE [rdi+rcx], 0 ; Check if first string is null
    jz .check_second_string_zero ; If null, return null
    jnz .loop ; If not null, jump to loop

.check_second_string_zero:
    cmp BYTE [rsi], 0 ; Check if second string is null
    jz .setnonnull ; If null, return first string
    jnz .loop ; If not null, jump to loop

.inc:
    inc rcx ;increment rcx

.loop:
    mov al, [rdi+rcx] ; mov car from src to al
    test al, al ; Check if end of string
    jz .return_null

    xor r8, r8 ; reset sub_loop counter
    jmp .second_loop

.second_inc:
    inc r8 ; increment sub_loop counter
    jmp .second_loop

.second_loop:
    mov dl, [rsi+r8] ; load car come after
    test dl, dl ; test if src ends and is found
    jz .setnonnull

    lea r11, [rcx+r8] ; add the two counters
    mov al, [rdi+r11] ; Load character from the two counters
    test al, al ; If end of string, return NULL
    jz .return_null
    cmp al, dl ; Compare characters
    jne .inc ; If not equal, jump loop and next car
    jmp .second_inc ; If equal, increment sub_loop counter

.setnonnull:
    lea rax, [rdi+rcx] ; Set return value to str found
    jmp .end

.return_null:
    xor rax, rax ; set rax to null
    jmp .end

.end:
    LEAVE
    ret
