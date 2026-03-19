; Questão escolhida: 5 
; Descrição: "Calcula a quantidade de divisores de um número (EAX=número, resultado em EDI)"

inicio:
mov eax, 18 
mov ebx, eax
mov ecx, eax   
mov edi, 0      
mov esi, 0    

laco:
cmp ecx, esi
jz fim
    
mov eax, ebx 
mov edx, 0
div ecx
    
cmp edx, esi
jz num_divisor
jmp proximo

num_divisor:
inc edi 

proximo:
dec ecx     
jmp laco


fim:
mov eax, ebx
