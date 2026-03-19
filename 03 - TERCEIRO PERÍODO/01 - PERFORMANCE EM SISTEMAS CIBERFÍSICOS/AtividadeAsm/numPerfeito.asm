inicio:
mov eax, 6      
mov ebx, eax    
mov ecx, 1     
mov esi, 0      
mov edi, 0      


laco:
cmp ecx, ebx    
jz fim_laco     
mov eax, ebx    
mov edx, 0      
div ecx    
cmp edx, edi    
jz soma_divisor 
jmp proximo     


soma_divisor:
add esi, ecx   


proximo:
inc ecx        
jmp laco        


fim_laco:
cmp esi, ebx   
jz numero_perfeito
jmp fim         


numero_perfeito:
mov edi, 1


fim:
mov eax, ebx 
