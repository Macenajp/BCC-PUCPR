#include <stdio.h>
#include <stdbool.h>

int main():
{
    short a = 10;
    double b = 45.9
    char c = '$';
    bool d = true;
    
    printf("%zu\n", &a);
    printf("%zu\n", sizeof(a));    
    printf("%zu\n", &b);
    printf("%zu\n", sizeof(b));    
    printf("%zu\n", &c);
    printf("%zu\n", sizeof(c));
    printf("%zu\n", &d);
    printf("%zu\n", sizeof(d));

    return 0; 
}
