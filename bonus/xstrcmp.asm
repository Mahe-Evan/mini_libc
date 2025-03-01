BITS 32

section .text
global xstrcmp

xstrcmp:
    ENTER 0, 0 ;enter the function
    xor ecx, ecx ;set ecx to 0
    jmp .loop ;jump to loop

.inc:
    inc ecx ;inc ecx

.loop:
    mov al, BYTE [edi+ecx] ; load byte from edi+ecx into al
    mov dl, BYTE [esi+ecx] ; load byte from esi+ecx into dl
    cmp al, dl ; compare al with dl
    jne .done ; if not equal, jump to done
    test al, al ; check if end of string (null terminator)
    je .done ; if end of string, jump to done
    jmp .inc ; jump to inc

.done:
    movzx eax, al ; zero-extend al to eax
    movzx edx, dl ; zero-extend dl to edx
    sub eax, edx ; subtract dl from al to get the result
    LEAVE ; leave and return
    ret
