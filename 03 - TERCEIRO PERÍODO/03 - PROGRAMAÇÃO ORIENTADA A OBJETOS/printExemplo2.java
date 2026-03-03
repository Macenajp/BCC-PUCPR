// Código ao dar run funciona e da o resultado, mas, "falho", pois dá overflow. Dessa forma o resultado final fica positivo e negativo:
// 32767
// -32767

// Ou seja, o código parece certo, mas apresenta um resultado absurdo.

public class teste {
    public static void main(String[] args){
        short k = 32767;
        System.out.println(k);
        k++;
        System.out.println(k);
    }
}

