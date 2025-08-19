    #include <stdio.h>

    int main()
    {
        int a = 10;
        printf("Endereço de a: %p\n", &a);
        printf("Tamanho de a: %zu\n", sizeof(a));

        int* p = &a;
        printf("Valor de p: %p\n", p);
        printf("Valor do apontado por p: %d\n", *p);
        printf("Endereço de p: %p\n", &p);
        printf("Tamanho de p: %zu\n", sizeof(p));
    }
