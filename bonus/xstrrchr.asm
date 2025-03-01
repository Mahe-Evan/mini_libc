BITS 32

section .text
    global xstrrchr

strlen:
    ENTER 0, 0  ;enter the fonction
    xor eax, eax    ;set eax to 0
    jmp .loop   ;got to loop

.inc:
    inc eax ;inc eax 

.loop:  ;loop
    movzx edx, byte [edi + eax] ; The movzx (move with zero extension) instruction loads the byte from memory into the edx register and zero-extends it to fill the entire 64-bit register
    test edx, edx ;test if edx is zero with a end
    jz .done ;jump to done if zero
    jmp .inc ;jump to inc

.done:
    LEAVE ;leave and return
    ret


xstrrchr:
    ENTER 0, 0
    call strlen ;call strlen
    mov ecx, eax ;move eax in ecx
    lea edi, [edi + ecx] ;loads the effective address of edi + ecx into edi without performing a memory access.
    xor eax, eax ;set eax to 0

.loop:
    cmp ecx, 0 ;comp ecx and 0
    jl .done ;jump less

    movzx edx, byte [edi] ; The movzx (move with zero extension) instruction loads the byte from memory into the edx register and zero-extends it to fill the entire 64-bit register
    cmp edx, esi ;comp edx and esi
    je .found ;jump equal

    dec edi ;sub 1 to edi and edx
    dec ecx
    jmp .loop

.found:
    mov eax, edi ;move edi in eax

.done:
    LEAVE
    ret
