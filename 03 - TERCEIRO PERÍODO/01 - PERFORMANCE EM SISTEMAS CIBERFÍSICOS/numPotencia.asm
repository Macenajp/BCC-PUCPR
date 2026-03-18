inicio:
mov eax, 3    
mov ebx, 5     
mov esi, eax   
mov eax, 1 


laco:
cmp ebx, 0    
jz fim
mul esi      
dec ebx    
jmp laco


fim:
mov edi, eax
