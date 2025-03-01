BITS 32

section .text
global xstrncmp

xstrncmp:
    ENTER 0, 0 ;enter the function
    push ebx ;save ebx
    mov ebx, edx
    xor ecx, ecx ;set ecx to 0
    jmp .loop ;jump to loop

.inc:
    inc ecx ;inc ecx

.loop:
    cmp ecx, ebx ;comp the counter with the length
    je .zero_done ;if equal, jump to zero_done
    mov al, BYTE [edi+ecx] ; load byte from edi+ecx into al
    mov dl, BYTE [esi+ecx] ; load byte from esi+ecx into dl
    cmp al, dl ; compare al with dl
    jne .done ; if not equal, jump to done
    test al, al ; check if end of string (null terminator)
    je .zero_done ; if end of string, jump to zero_done
    jmp .inc ; jump to inc

.zero_done:
    xor eax, eax ; set eax to 0
    LEAVE ; leave and return
    ret

.done:
    movzx eax, al ; zero-extend al to eax
    movzx edx, dl ; zero-extend dl to edx
    sub eax, edx ; subtract dl from al to get the result
    pop ebx ;restore ebx
    LEAVE ; leave and return
    ret
