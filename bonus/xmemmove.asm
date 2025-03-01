BITS 32

section .text
global xmemmove

xmemmove:
    ENTER 0, 0
    mov eax, edi ; Save original destination pointer
    cmp edi, 0 ; Check if destination is null
    je .return_null ; Return null if destination is null
    cmp esi, 0 ; Check if source is null
    je .done ; return the dest if src is null
    cmp esi, edi ; Compare source and destination pointers
    je .done ; If they are the same, nothing to do
    jae .forward ; If source is after destination, copy forward
    jmp .backward ; Otherwise, copy backward

.forward:
    mov ecx, edx ; Copy `n` (edx) into ecx for loop counter
    jmp .floop

.finc:
    inc esi  ; Increment source pointer
    inc edi  ; Increment destination pointer
    dec ecx  ; Decrement counter
    jmp .floop ; Jump to loop

.floop:
    test ecx, ecx ; Check if all bytes are copied
    jz .done
    mov dl, [esi] ; Load byte from source
    mov [edi], dl ; Store byte into destination
    jmp .finc ; Jump to inc

.backward:
    add esi, edx ; Move source pointer to the end
    add edi, edx ; Move destination pointer to the end
    mov ecx, edx ; Copy `n` (edx) into ecx for loop counter
    dec esi  ; Decrement source pointer
    dec edi  ; Decrement destination pointer
    jmp .bloop

.bdec:
    dec esi  ; Decrement source pointer
    dec edi  ; Decrement destination pointer
    dec ecx  ; Decrement counter
    jmp .bloop ; Jump to loop

.bloop:
    test ecx, ecx ; Check if all bytes are copied
    jz .done
    mov dl, [esi] ; Load byte from source
    mov [edi], dl ; Store byte into destination
    jmp .bdec ; Jump to dec

.return_null:
    xor eax, eax ; Set eax to 0

.done:
    LEAVE
    ret