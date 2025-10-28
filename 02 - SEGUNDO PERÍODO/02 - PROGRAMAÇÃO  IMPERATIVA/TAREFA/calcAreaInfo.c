#include <stdio.h>

int main()
{
    printf("Hello World\n");

    /*
    float: Irá apresentar a quantidade de bits.
    double: Irá dobrar a quantidade de bits.
    long double: Vai dobrar a quantidade de bits (baseando-se no 'double') - pode apresentar erros nas saídas.
    Lf: 'Long float'. Vai funcionar como 'long double', mas vai funcionar corretamente.
    */ 
    
    float PI = 3.14;
    float raio = 10.0;
    float area = PI * raio * raio;

    printf("%f\n", area);
    printf("%zu\n", sizeof(float));
    printf("%zu\n", sizeof(PI));
    printf("Tchau!");

    return 0;
}
