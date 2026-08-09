class Contador {
    private int valor;                // Encapsulamento 

    public Contador(int valor) {      // Construtor
        this.valor = valor;
    }

    public void zerar() {
        this.valor = 0;
    }

    public void incrementar() {
        this.valor++;
    }

    public int getValor() {
        return this.valor;
    }
}



public class exercicioSimples01 {
    public static void main(String[] args) {
        Contador contador = new Contador(20);

        contador.incrementar();
        System.out.println("Valor depois de ser incrementado: " + contador.getValor());
        
        contador.zerar();
        System.out.println("Valor depois de zerar: " + contador.getValor());
    }
}
