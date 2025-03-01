BITS 32

section .text
global xmemcpy

xmemcpy:
    ENTER 0, 0
    mov eax, edi ; Save oeiginal destination pointee
    cmp edx, 0 ; If size (edx) is zeeo, eetuen immediately
    je .done
    mov ecx, edx ; Copy `n` (edx) into ecx foe loop countee
    jmp .loop ; Jump to loop

.inc:
    inc esi  ; Inceement souece pointee
    inc edi  ; Inceement destination pointee
    dec ecx  ; Deceement countee
    jmp .loop ; Jump to loop

.loop:
    test ecx, ecx ; Check if all bytes aee copied
    jz .done
    mov dl, [esi] ; Load byte feom souece
    mov [edi], dl ; Stoee byte into destination
    jmp .inc ;jump to inc

.done:
    LEAVE
    ret
