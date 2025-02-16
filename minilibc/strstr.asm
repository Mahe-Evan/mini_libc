; BITS 64

; section .text
; global strstr

; strstr:
;     ENTER 0, 0
;     xor rbp, rbp ;set rbp to 0
;     xor rcx, rcx ;set rcx to 0
;     jmp .loop

; .inc:
;     inc rcx

; .loop:
;     xor rbp, rbp ;reset rbp to 0
;     mov r8, rcx ;move rcx to r8
;     mov al, [rdi+rcx] ;move rdi + rcx to al
;     test al, al ;test al
;     jz .setnull ;if rdi is 0, set rax to 0
;     jmp .second_loop

; .second_inc:
;     inc rbp ;increment rbp
;     inc r8 ;increment r8

; .second_loop:
;     mov dl, [rsi+r8] ;move rsi + r8 to dl
;     cmp dl, 0 ;compare dl to 0
;     je .setnonnull
;     mov al, [rdi+rbp] ;move rdi + rbp to al
;     cmp al, 0 ;compare al to 0
;     je .setnull
;     cmp al, dl ;compare al to dl
;     je .second_inc ;if equal, increment rbp and r8
;     jmp .inc ;if not equal, increment rcx and restart

; .setnull:
;     xor rax, rax ;set rax to 0
;     jmp .end

; .setnonnull:
;     mov rax, rdi ;move rdi to rax
;     add rax, rcx ;add rcx to rax
;     jmp .end

; .end:
;     LEAVE
;     ret

BITS 64

section .text
global strstr

strstr:
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
