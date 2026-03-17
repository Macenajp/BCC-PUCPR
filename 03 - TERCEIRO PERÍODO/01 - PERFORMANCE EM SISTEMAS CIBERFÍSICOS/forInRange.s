;  Exercício de exemplo - apresentado em sala:

inicio:
mov eax, 200
mov ebx, 1
mov ecx, 5

laco:
sub eax, ebx
inc ebx
cmp ecx, ebx
jz fim
jmp laco

fim:
