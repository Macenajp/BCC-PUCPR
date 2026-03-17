; Exercício em Assembly:
; N°: 3 das 8 questões propostas

; Sobre o resultado: Se EDI = 0, então o número é primo, caso contrário, não é primo:

main:
    mov eax, 3

    mov ebx, eax
    mov ecx, eax
    dec ecx



laco_primo:
    cmp ecx, 1
    jz verdadeiro_primo
    cmp ecx, 0
    jz falso_primo

    mov eax, ebx
    mov edx, 0
    div ecx
    
    cmp edx, 0
    jz falso_primo

    dec ecx
    jmp laco_primo



verdadeiro_primo:
    mov edi, 1
    jmp fim

falso_primo:
    mov edi, 0

fim:
